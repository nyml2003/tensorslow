#include "Runtime/PyFrame.h"
#include "ByteCode/ByteCode.h"
#include "ByteCode/PyCode.h"
#include "ByteCode/PyInst.h"
#include "Collections/IntegerHelper.h"
#include "Collections/Stack.h"
#include "Collections/StringHelper.h"
#include "Function/PyFunction.h"
#include "Object/Iterator.h"
#include "Object/MixinCollections.h"
#include "Object/ObjectHelper.h"
#include "Object/PyBoolean.h"
#include "Object/PyDictionary.h"
#include "Object/PyInteger.h"
#include "Object/PyList.h"
#include "Object/PyNone.h"
#include "Object/PyObject.h"
#include "Object/PyString.h"
#include "Object/PyType.h"
#include "Runtime/Interpreter.h"
#include "Runtime/Serialize.h"
#include "Tools/Tools.h"

#include <cstring>
#include <memory>
#include <stdexcept>
#include <utility>

namespace torchlight::Runtime {

FrameKlass::FrameKlass() = default;

void FrameKlass::Initialize() {
  SetType(Object::CreatePyType(Self()));
  SetName(Object::CreatePyString("frame"));
  SetAttributes(Object::CreatePyDict());
}

Object::KlassPtr FrameKlass::Self() {
  static Object::KlassPtr instance = std::make_shared<FrameKlass>();
  return instance;
}

PyFrame::PyFrame(
  Object::PyCodePtr code,
  const Object::PyObjPtr& _locals,      // 传入的是 PyObjPtr
  const Object::PyObjPtr& _globals,     // 传入的是 PyObjPtr
  const Object::PyObjPtr& _fastLocals,  // 传入的是 PyObjPtr
  PyFramePtr caller
)
  : Object::PyObject(FrameKlass::Self()),
    stack(),
    programCounter(0),
    code(std::move(code)),
    locals(std::dynamic_pointer_cast<Object::PyDictionary>(_locals)
    ),  // 转换为 PyDictPtr
    globals(std::dynamic_pointer_cast<Object::PyDictionary>(_globals)
    ),  // 转换为 PyDictPtr
    fastLocals(std::dynamic_pointer_cast<Object::PyList>(_fastLocals)
    ),  // 转换为 PyListPtr
    caller(std::move(caller)) {}

PyFramePtr CreateModuleEntryFrame(const Object::PyCodePtr& code) {
  auto locals =
    std::dynamic_pointer_cast<Object::PyDictionary>(Object::CreatePyDict());
  auto globals = locals;
  locals->Put(
    Object::CreatePyString("__name__"), Object::CreatePyString("__main__")
  );
  auto fastLocals = Object::CreatePyList(code->NLocals());
  auto caller = nullptr;
  auto frame =
    std::make_shared<PyFrame>(code, locals, globals, fastLocals, caller);
  Interpreter::Instance().SetFrame(frame);
  return frame;
}

PyFramePtr CreateFrameWithPyFunction(
  const Object::PyFunctionPtr& function,
  const Object::PyListPtr& arguments
) {
  auto code = function->Code();
  auto globals = function->Globals();
  auto locals = Object::CreatePyDict();
  Index nLocals = code->NLocals();
  for (Index i = arguments->Length(); i < nLocals; i++) {
    arguments->Append(Object::PyNone::Instance());
  }
  auto caller = Interpreter::Instance().CurrentFrame();
  auto frame =
    std::make_shared<PyFrame>(code, locals, globals, arguments, caller);
  Interpreter::Instance().SetFrame(frame);
  return frame;
}

void PyFrame::SetProgramCounter(Index _pc) {
  programCounter = _pc;
}

Object::PyCodePtr PyFrame::Code() const {
  return code;
}

Index PyFrame::ProgramCounter() const {
  return programCounter;
}

Object::PyDictPtr PyFrame::CurrentLocals() const {
  return locals;
}

Object::PyDictPtr PyFrame::CurrentGlobals() const {
  return globals;
}

Object::PyListPtr PyFrame::CurrentFastLocals() const {
  return fastLocals;
}

Object::PyListPtr PyFrame::CurrentStack() const {
  return std::dynamic_pointer_cast<Object::PyList>(
    Object::CreatePyList(stack.GetContent())
  );
}

Object::PyInstPtr PyFrame::Instruction() const {
  if (!isParsed) {
    ParseByteCode(code);
  }
  auto insts = std::dynamic_pointer_cast<Object::PyList>(code->Instructions());
  return std::dynamic_pointer_cast<Object::PyInst>(insts->GetItem(programCounter
  ));
}

bool PyFrame::Finished() const {
  if (!isParsed) {
    ParseByteCode(code);
  }
  auto size = code->Instructions()->Length();
  return programCounter >= size;
}

void PyFrame::NextProgramCounter() {
  programCounter++;
}

void ParseByteCode(const Object::PyCodePtr& code) {
  auto bytes = code->ByteCode()->Value().Value();
  auto iter = Collections::Iterator<Byte>::Begin(bytes);
  if (static_cast<Object::Literal>(iter.Get()) != Object::Literal::LIST) {
    throw std::runtime_error("Invalid insts");
  }
  iter.Next();
  Index size = ReadU64(iter);
  auto insts = Collections::List<Object::PyObjPtr>(size);
  while ((size--) != 0U) {
    auto byte = iter.Get();
    iter.Next();
    switch (static_cast<Object::ByteCode>(byte)) {
      case Object::ByteCode::LOAD_CONST: {
        insts.Push(Object::CreateLoadConst(ReadU64(iter)));
        break;
      }
      case Object::ByteCode::BINARY_ADD: {
        insts.Push(Object::CreateBinaryAdd());
        break;
      }
      case Object::ByteCode::BINARY_MULTIPLY: {
        insts.Push(Object::CreateBinaryMultiply());
        break;
      }
      case Object::ByteCode::BINARY_SUBTRACT: {
        insts.Push(Object::CreateBinarySubtract());
        break;
      }
      case Object::ByteCode::STORE_FAST: {
        insts.Push(Object::CreateStoreFast(ReadU64(iter)));
        break;
      }
      case Object::ByteCode::LOAD_FAST: {
        insts.Push(Object::CreateLoadFast(ReadU64(iter)));
        break;
      }
      case Object::ByteCode::COMPARE_OP: {
        insts.Push(
          Object::CreateCompareOp(static_cast<Object::CompareOp>(ReadU8(iter)))
        );
        break;
      }
      case Object::ByteCode::POP_JUMP_IF_FALSE: {
        insts.Push(Object::CreatePopJumpIfFalse(ReadI64(iter)));
        break;
      }
      case Object::ByteCode::POP_JUMP_IF_TRUE: {
        insts.Push(Object::CreatePopJumpIfTrue(ReadI64(iter)));
        break;
      }
      case Object::ByteCode::MAKE_FUNCTION: {
        insts.Push(Object::CreateMakeFunction());
        break;
      }
      case Object::ByteCode::CALL_FUNCTION: {
        insts.Push(Object::CreateCallFunction(ReadU64(iter)));
        break;
      }
      case Object::ByteCode::RETURN_VALUE: {
        insts.Push(Object::CreateReturnValue());
        break;
      }
      case Object::ByteCode::LOAD_NAME: {
        insts.Push(Object::CreateLoadName(ReadU64(iter)));
        break;
      }
      case Object::ByteCode::STORE_NAME: {
        insts.Push(Object::CreateStoreName(ReadU64(iter)));
        break;
      }
      case Object::ByteCode::LOAD_GLOBAL: {
        insts.Push(Object::CreateLoadGlobal(ReadU64(iter)));
        break;
      }
      case Object::ByteCode::POP_TOP: {
        insts.Push(Object::CreatePopTop());
        break;
      }
      case Object::ByteCode::LOAD_ATTR: {
        insts.Push(Object::CreateLoadAttr(ReadU64(iter)));
        break;
      }
      case Object::ByteCode::BUILD_LIST: {
        insts.Push(Object::CreateBuildList(ReadU64(iter)));
        break;
      }
      case Object::ByteCode::BINARY_MATRIX_MULTIPLY: {
        insts.Push(Object::CreateBinaryMatrixMultiply());
        break;
      }
      case Object::ByteCode::JUMP_ABSOLUTE: {
        insts.Push(Object::CreateJumpAbsolute(ReadU64(iter)));
        break;
      }
      case Object::ByteCode::BINARY_SUBSCR: {
        insts.Push(Object::CreateBinarySubscr());
        break;
      }
      case Object::ByteCode::STORE_SUBSCR: {
        insts.Push(Object::CreateStoreSubscr());
        break;
      }
      case Object::ByteCode::GET_ITER: {
        insts.Push(Object::CreateGetIter());
        break;
      }
      case Object::ByteCode::FOR_ITER: {
        insts.Push(Object::CreateForIter(ReadI64(iter)));
        break;
      }
      case Object::ByteCode::LOAD_BUILD_CLASS: {
        insts.Push(Object::CreateLoadBuildClass());
        break;
      }
      case Object::ByteCode::STORE_ATTR: {
        insts.Push(Object::CreateStoreAttr(ReadU64(iter)));
        break;
      }
      default:
        throw std::runtime_error(
          "Unknown byte code:" + std::to_string(static_cast<int>(iter.Get()))
        );
        break;
    }
  }
  code->SetInstructions(std::make_shared<Object::PyList>(insts));
}

Object::PyObjPtr FrameKlass::repr(const Object::PyObjPtr& obj) {
  if (obj->Klass() != FrameKlass::Self()) {
    throw std::runtime_error("Cannot repr non-frame object");
  }
  auto frame = std::dynamic_pointer_cast<PyFrame>(obj);
  auto code = frame->Code();
  auto name = code->Name();
  Object::PyObjPtr repr =
    Object::CreatePyString(Collections::CreateStringWithCString("<frame>"));
  repr = repr->add(Object::CreatePyString(
    Collections::CreateStringWithCString("\nprogramCounter: ")
  ));
  repr = repr->add(Object::CreatePyInteger(
                     Collections::CreateIntegerWithU64(frame->ProgramCounter())
  )
                     ->repr());
  repr = repr->add(Object::CreatePyString(
    Collections::CreateStringWithCString("\n\ninstruction:\n")
  ));
  repr = repr->add(frame->Instruction()->repr());
  repr = repr->add(
    Object::CreatePyString(Collections::CreateStringWithCString("\n\nstack:\n"))
  );
  repr = repr->add(frame->CurrentStack()->Join(Object::CreatePyString("\n")));
  repr = repr->add(
    Object::CreatePyString(Collections::CreateStringWithCString("\nlocals:\n"))
  );
  repr = repr->add(frame->CurrentLocals()->repr());
  repr = repr->add(Object::CreatePyString(
    Collections::CreateStringWithCString("\n\nglobals:\n")
  ));
  repr = repr->add(frame->CurrentGlobals()->repr());

  repr = repr->add(Object::CreatePyString(
    Collections::CreateStringWithCString("\n\nfastLocals:\n")
  ));
  repr = repr->add(frame->CurrentFastLocals()->repr());
  repr = repr->add(Object::CreatePyString(
    Collections::CreateStringWithCString("\n\ncaller:\n")
  ));
  repr = repr->add(frame->Caller()->repr());
  repr = repr->add(
    Object::CreatePyString(Collections::CreateStringWithCString("\n\ncode:\n"))
  );
  repr = repr->add(code->str());
  repr = repr->add(
    Object::CreatePyString(Collections::CreateStringWithCString("</frame>\n"))
  );
  return repr;
}

PyFramePtr PyFrame::Caller() const {
  return caller;
}

bool PyFrame::HasCaller() const {
  return caller != nullptr;
}

Object::PyObjPtr PyFrame::Eval() {
  while (!Finished()) {
    const auto& inst = Instruction();
    if (ArgsHelper::Instance().Has("debug")) {
      Object::DebugPrint(Object::CreatePyString("-------------------"));
      Object::DebugPrint(shared_from_this());
    }
    switch (inst->Code()) {
      case Object::ByteCode::LOAD_CONST: {
        auto key = std::get<Index>(inst->Operand());
        auto value = Code()->Consts()->getitem(Object::CreatePyInteger(key));
        stack.Push(value);
        NextProgramCounter();
        break;
      }
      case Object::ByteCode::STORE_FAST: {
        auto index = std::get<Index>(inst->Operand());
        auto value = stack.Pop();
        fastLocals->setitem(Object::CreatePyInteger(index), value);
        NextProgramCounter();
        break;
      }
      case Object::ByteCode::COMPARE_OP: {
        auto oprt = std::get<Object::CompareOp>(inst->Operand());
        auto right = stack.Pop();
        auto left = stack.Pop();
        switch (oprt) {
          case Object::CompareOp::EQUAL: {
            stack.Push(left->eq(right));
            auto result = left->eq(right);
            break;
          }
          case Object::CompareOp::NOT_EQUAL: {
            stack.Push(left->ne(right));
            auto result = left->ne(right);
            break;
          }
          case Object::CompareOp::LESS_THAN: {
            stack.Push(left->lt(right));
            auto result = left->lt(right);
            break;
          }
          case Object::CompareOp::LESS_THAN_EQUAL: {
            stack.Push(left->le(right));
            auto result = left->le(right);
            break;
          }
          case Object::CompareOp::GREATER_THAN: {
            stack.Push(left->gt(right));
            auto result = left->gt(right);
            break;
          }
          case Object::CompareOp::GREATER_THAN_EQUAL: {
            stack.Push(left->ge(right));
            auto result = left->ge(right);
            break;
          }
          case Object::CompareOp::IN: {
            stack.Push(right->contains(left));
            auto result = right->contains(left);
            break;
          }
          case Object::CompareOp::NOT_IN: {
            stack.Push(Not(right->contains(left)));
            auto result = Not(right->contains(left));
            break;
          }
          case Object::CompareOp::IS: {
            stack.Push(Object::CreatePyBoolean(left.get() == right.get()));
            auto result = Object::CreatePyBoolean(left.get() == right.get());
            break;
          }
          case Object::CompareOp::IS_NOT: {
            stack.Push(Not(Object::CreatePyBoolean(left.get() == right.get())));
            auto result = Object::CreatePyBoolean(left.get() != right.get());
            break;
          }
          default:
            throw std::runtime_error("Unknown compare operation");
        }
        NextProgramCounter();
        break;
      }
      case Object::ByteCode::POP_JUMP_IF_FALSE: {
        auto needJump = stack.Pop();
        if (!(needJump->Klass() == Object::BooleanKlass::Self())) {
          throw std::runtime_error("Cannot jump if not boolean");
        }
        auto bool_needJump =
          std::dynamic_pointer_cast<Object::PyBoolean>(needJump);
        if (bool_needJump == nullptr) {
          throw std::runtime_error("Cannot jump if not boolean");
        }
        NextProgramCounter();
        if (!bool_needJump->Value()) {
          SetProgramCounter(Collections::safe_add(
            ProgramCounter(), std::get<int64_t>(inst->Operand())
          ));
        }
        break;
      }
      case Object::ByteCode::POP_JUMP_IF_TRUE: {
        auto needJump = stack.Pop();
        if (!(needJump->Klass() == Object::BooleanKlass::Self())) {
          throw std::runtime_error("Cannot jump if not boolean");
        }
        auto bool_needJump =
          std::dynamic_pointer_cast<Object::PyBoolean>(needJump);
        if (bool_needJump == nullptr) {
          throw std::runtime_error("Cannot jump if not boolean");
        }
        NextProgramCounter();
        if (bool_needJump->Value()) {
          SetProgramCounter(Collections::safe_add(
            ProgramCounter(), std::get<int64_t>(inst->Operand())
          ));
        }
        break;
      }
      case Object::ByteCode::BINARY_ADD: {
        auto right = stack.Pop();
        auto left = stack.Pop();
        stack.Push(left->add(right));
        NextProgramCounter();
        break;
      }
      case Object::ByteCode::BINARY_SUBTRACT: {
        auto right = stack.Pop();
        auto left = stack.Pop();
        stack.Push(left->sub(right));
        NextProgramCounter();
        break;
      }
      case Object::ByteCode::BINARY_MULTIPLY: {
        auto right = stack.Pop();
        auto left = stack.Pop();
        stack.Push(left->mul(right));
        NextProgramCounter();
        break;
      }
      case Object::ByteCode::BINARY_MATRIX_MULTIPLY: {
        auto right = stack.Pop();
        auto left = stack.Pop();
        stack.Push(left->matmul(right));
        NextProgramCounter();
        break;
      }
      case Object::ByteCode::BINARY_TRUE_DIVIDE:
      case Object::ByteCode::BINARY_FLOOR_DIVIDE:
      case Object::ByteCode::BINARY_XOR:
      case Object::ByteCode::BINARY_AND:
      case Object::ByteCode::BINARY_OR:
      case Object::ByteCode::BINARY_POWER:
      case Object::ByteCode::BINARY_MODULO:
      case Object::ByteCode::BINARY_LSHIFT:
      case Object::ByteCode::BINARY_RSHIFT:
        break;
      case Object::ByteCode::BINARY_SUBSCR: {
        auto index = stack.Pop();
        auto obj = stack.Pop();
        stack.Push(obj->getitem(index));
        NextProgramCounter();
        break;
      }
      case Object::ByteCode::RETURN_VALUE: {
        auto value = stack.Pop();
        return value;
        break;
      }
      case Object::ByteCode::MAKE_FUNCTION: {
        auto name = stack.Pop();
        if (name->Klass() != Object::StringKlass::Self()) {
          throw std::runtime_error("Function name must be string");
        }
        auto code = stack.Pop();
        if (code->Klass() != Object::CodeKlass::Self()) {
          throw std::runtime_error("Function code must be code object");
        }

        auto func = Object::CreatePyFunction(code, globals);
        stack.Push(func);
        NextProgramCounter();
        break;
      }
      case Object::ByteCode::LOAD_FAST: {
        auto index = std::get<Index>(inst->Operand());
        auto value = fastLocals->GetItem(index);
        stack.Push(value);
        NextProgramCounter();
        break;
      }
      case Object::ByteCode::CALL_FUNCTION: {
        auto argumentCount = std::get<Index>(inst->Operand());
        Collections::List<Object::PyObjPtr> arguments(argumentCount);
        for (Index i = 0; i < argumentCount; i++) {
          arguments.Push(stack.Pop());
        }
        arguments.Reverse();
        auto func = stack.Pop();
        auto result = Interpreter::Instance().Eval(
          func, std::dynamic_pointer_cast<Object::PyList>(
                  Object::CreatePyList(arguments)
                )
        );
        stack.Push(result);
        NextProgramCounter();
        break;
      }
      case Object::ByteCode::LOAD_GLOBAL: {
        auto index = std::get<Index>(inst->Operand());
        auto key = Code()->Names()->GetItem(index);
        bool found = false;
        Object::PyObjPtr value = Object::CreatePyNone();
        if (Object::IsTrue(globals->contains(key))) {
          found = true;
          value = globals->getitem(key);
        }
        if (!found &&
            Object::IsTrue(Interpreter::Instance().Builtins()->contains(key))) {
          found = true;
          value = Interpreter::Instance().Builtins()->getitem(key);
        }
        if (!found) {
          throw std::runtime_error(
            "NameError: " + Collections::ToCppString(key) + " not found"
          );
        }
        stack.Push(value);
        NextProgramCounter();
        break;
      }
      case Object::ByteCode::STORE_NAME: {
        auto index = std::get<Index>(inst->Operand());
        auto key = Code()->Names()->GetItem(index);
        auto value = stack.Pop();
        locals->setitem(key, value);
        NextProgramCounter();
        break;
      }
      case Object::ByteCode::LOAD_NAME: {
        auto index = std::get<Index>(inst->Operand());
        auto key = Code()->Names()->GetItem(index);
        // LEGB rule
        // local -> enclosing -> global -> built-in
        bool found = false;
        Object::PyObjPtr value = Object::CreatePyNone();
        if (Object::IsTrue(locals->contains(key))) {
          found = true;
          value = locals->getitem(key);
        }
        if (!found && Object::IsTrue(globals->contains(key))) {
          found = true;
          value = globals->getitem(key);
        }
        if (!found &&
            Object::IsTrue(Interpreter::Instance().Builtins()->contains(key))) {
          found = true;
          value = Interpreter::Instance().Builtins()->getitem(key);
        }
        if (!found) {
          throw std::runtime_error(
            "NameError: " + Collections::ToCppString(key) + " not found"
          );
        }
        stack.Push(value);
        NextProgramCounter();
        break;
      }
      case Object::ByteCode::POP_TOP: {
        stack.Pop();
        NextProgramCounter();
        break;
      }
      case Object::ByteCode::LOAD_ATTR: {
        auto index = std::get<Index>(inst->Operand());
        auto key = Code()->Names()->GetItem(index);
        auto obj = stack.Pop();

        auto value = obj->getattr(key);
        stack.Push(value);
        NextProgramCounter();
        break;
      }
      case Object::ByteCode::BUILD_LIST: {
        auto size = std::get<Index>(inst->Operand());
        Collections::List<Object::PyObjPtr> elements(size);
        for (Index i = 0; i < size; i++) {
          elements.Push(stack.Pop());
        }
        elements.Reverse();
        auto list = Object::CreatePyList(elements);
        stack.Push(list);
        NextProgramCounter();
        break;
      }
      case Object::ByteCode::JUMP_ABSOLUTE: {
        SetProgramCounter(std::get<Index>(inst->Operand()));
        break;
      }
      case Object::ByteCode::STORE_SUBSCR: {
        auto index = stack.Pop();
        auto obj = stack.Pop();
        auto value = stack.Pop();
        obj->setitem(index, value);
        NextProgramCounter();
        break;
      }
      case Object::ByteCode::GET_ITER: {
        auto obj = stack.Pop();
        auto iter = obj->iter();
        stack.Push(iter);
        NextProgramCounter();
        break;
      }
      case Object::ByteCode::FOR_ITER: {
        auto iter = stack.Pop();
        auto value = iter->next();
        if (Object::IsType(value, Object::IterDoneKlass::Self())) {
          SetProgramCounter(Collections::safe_add(
            ProgramCounter(), std::get<int64_t>(inst->Operand())
          ));
        } else {
          stack.Push(iter);
          stack.Push(value);
          NextProgramCounter();
        }
        break;
      }
      case Object::ByteCode::LOAD_BUILD_CLASS: {
        stack.Push(Interpreter::Instance().Builtins()->getitem(
          Object::CreatePyString("__build_class__")
        ));
        NextProgramCounter();
        break;
      }
      case Object::ByteCode::STORE_ATTR: {
        auto index = std::get<Index>(inst->Operand());
        auto key = Code()->Names()->GetItem(index);
        auto obj = stack.Pop();
        auto value = stack.Pop();
        obj->setattr(key, value);
        NextProgramCounter();
        break;
      }
      case Object::ByteCode::ERROR: {
        throw std::runtime_error("Unknown byte code");
        break;
      }
        throw std::runtime_error("Unknown byte code");
    }
  }
  throw std::runtime_error("Module code did not return None");
}

Object::PyObjPtr PyFrame::EvalWithDestory() {
  auto result = Eval();
  Interpreter::Instance().BackToParentFrame();
  return result;
}

}  // namespace torchlight::Runtime
