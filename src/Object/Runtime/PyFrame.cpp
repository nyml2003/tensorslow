#include "Object/Runtime/PyFrame.h"
#include "ByteCode/ByteCode.h"
#include "Collections/Integer/IntegerHelper.h"
#include "Collections/Stack.h"
#include "Function/ObjectHelper.h"
#include "Object/Container/PyDictionary.h"
#include "Object/Container/PyList.h"
#include "Object/Core/PyBoolean.h"
#include "Object/Core/PyNone.h"
#include "Object/Core/PyObject.h"
#include "Object/Core/PyType.h"
#include "Object/Function/PyFunction.h"
#include "Object/Iterator/Iterator.h"
#include "Object/Iterator/PyGenerator.h"
#include "Object/Number/PyInteger.h"
#include "Object/PySlice.h"
#include "Object/Runtime/PyCode.h"
#include "Object/Runtime/PyInst.h"
#include "Object/String/PyString.h"
#include "Runtime/Interpreter.h"
#include "Runtime/Serialize.h"
#include "Tools/Tools.h"

namespace torchlight::Object {

PyFrame::PyFrame(
  PyCodePtr code,
  PyDictPtr locals,
  PyDictPtr globals,
  PyListPtr fastLocals,
  PyFramePtr caller
)
  : PyObject(FrameKlass::Self()),
    stack(),
    programCounter(0),
    code(std::move(code)),
    locals(std::move(locals)),
    globals(std::move(globals)),
    fastLocals(std::move(fastLocals)),
    caller(std::move(caller)) {}

PyFramePtr CreateModuleEntryFrame(const PyCodePtr& code) {
  auto locals = CreatePyDict()->as<PyDictionary>();
  auto globals = locals;
  locals->Put(CreatePyString("__name__"), CreatePyString("__main__"));
  auto fastLocals = CreatePyList(code->NLocals())->as<PyList>();
  auto caller = nullptr;
  auto frame =
    std::make_shared<PyFrame>(code, locals, globals, fastLocals, caller);
  Runtime::Interpreter::Instance().SetFrame(frame);
  return frame;
}

PyFramePtr CreateFrameWithPyFunction(
  const PyFunctionPtr& function,
  const PyListPtr& arguments
) {
  auto code = function->Code();
  auto globals = function->Globals();
  auto locals = CreatePyDict()->as<PyDictionary>();
  Index nLocals = code->NLocals();
  for (Index i = arguments->Length(); i < nLocals; i++) {
    arguments->Append(PyNone::Instance());
  }
  auto caller = Runtime::Interpreter::Instance().CurrentFrame();
  auto frame =
    std::make_shared<PyFrame>(code, locals, globals, arguments, caller);
  Runtime::Interpreter::Instance().SetFrame(frame);
  return frame;
}

void PyFrame::SetProgramCounter(Index _pc) {
  programCounter = _pc;
}

PyCodePtr PyFrame::Code() const {
  return code;
}

Index PyFrame::ProgramCounter() const {
  return programCounter;
}

PyDictPtr PyFrame::CurrentLocals() const {
  return locals;
}

PyDictPtr PyFrame::CurrentGlobals() const {
  return globals;
}

PyListPtr PyFrame::CurrentFastLocals() const {
  return fastLocals;
}

PyListPtr PyFrame::CurrentStack() const {
  return CreatePyList(stack.GetContent())->as<PyList>();
}

PyInstPtr PyFrame::Instruction() const {
  if (!isParsed) {
    ParseByteCode(code);
  }
  auto insts = code->Instructions()->as<PyList>();
  return insts->GetItem(programCounter)->as<PyInst>();
}

bool PyFrame::Finished() {
  if (!isParsed) {
    ParseByteCode(code);
  }
  this->isParsed = true;
  auto size = code->Instructions()->Length();
  return programCounter >= size;
}

void PyFrame::NextProgramCounter() {
  programCounter++;
}

void ParseByteCode(const PyCodePtr& code) {
  auto bytes = code->ByteCode()->Value().Value();
  auto iter = Collections::Iterator<Byte>::Begin(bytes);
  if (static_cast<Literal>(iter.Get()) != Literal::LIST) {
    throw std::runtime_error("Invalid insts");
  }
  iter.Next();
  Index size = Runtime::ReadU64(iter);
  auto insts = Collections::List<PyObjPtr>(size);
  while ((size--) != 0U) {
    auto byte = iter.Get();
    iter.Next();
    switch (static_cast<ByteCode>(byte)) {
      case ByteCode::LOAD_CONST: {
        insts.Push(CreateLoadConst(Runtime::ReadU64(iter)));
        break;
      }
      case ByteCode::BINARY_ADD: {
        insts.Push(CreateBinaryAdd());
        break;
      }
      case ByteCode::BINARY_MULTIPLY: {
        insts.Push(CreateBinaryMultiply());
        break;
      }
      case ByteCode::BINARY_SUBTRACT: {
        insts.Push(CreateBinarySubtract());
        break;
      }
      case ByteCode::STORE_FAST: {
        insts.Push(CreateStoreFast(Runtime::ReadU64(iter)));
        break;
      }
      case ByteCode::LOAD_FAST: {
        insts.Push(CreateLoadFast(Runtime::ReadU64(iter)));
        break;
      }
      case ByteCode::COMPARE_OP: {
        insts.Push(CreateCompareOp(static_cast<CompareOp>(Runtime::ReadU8(iter))
        ));
        break;
      }
      case ByteCode::POP_JUMP_IF_FALSE: {
        insts.Push(CreatePopJumpIfFalse(Runtime::ReadI64(iter)));
        break;
      }
      case ByteCode::POP_JUMP_IF_TRUE: {
        insts.Push(CreatePopJumpIfTrue(Runtime::ReadI64(iter)));
        break;
      }
      case ByteCode::MAKE_FUNCTION: {
        insts.Push(CreateMakeFunction());
        break;
      }
      case ByteCode::CALL_FUNCTION: {
        insts.Push(CreateCallFunction(Runtime::ReadU64(iter)));
        break;
      }
      case ByteCode::RETURN_VALUE: {
        insts.Push(CreateReturnValue());
        break;
      }
      case ByteCode::LOAD_NAME: {
        insts.Push(CreateLoadName(Runtime::ReadU64(iter)));
        break;
      }
      case ByteCode::STORE_NAME: {
        insts.Push(CreateStoreName(Runtime::ReadU64(iter)));
        break;
      }
      case ByteCode::LOAD_GLOBAL: {
        insts.Push(CreateLoadGlobal(Runtime::ReadU64(iter)));
        break;
      }
      case ByteCode::POP_TOP: {
        insts.Push(CreatePopTop());
        break;
      }
      case ByteCode::LOAD_ATTR: {
        insts.Push(CreateLoadAttr(Runtime::ReadU64(iter)));
        break;
      }
      case ByteCode::BUILD_LIST: {
        insts.Push(CreateBuildList(Runtime::ReadU64(iter)));
        break;
      }
      case ByteCode::BUILD_SLICE: {
        insts.Push(CreateBuildSlice());
        break;
      }
      case ByteCode::BUILD_MAP: {
        insts.Push(CreateBuildMap(Runtime::ReadU64(iter)));
        break;
      }
      case ByteCode::BINARY_MATRIX_MULTIPLY: {
        insts.Push(CreateBinaryMatrixMultiply());
        break;
      }
      case ByteCode::JUMP_ABSOLUTE: {
        insts.Push(CreateJumpAbsolute(Runtime::ReadU64(iter)));
        break;
      }
      case ByteCode::BINARY_SUBSCR: {
        insts.Push(CreateBinarySubscr());
        break;
      }
      case ByteCode::STORE_SUBSCR: {
        insts.Push(CreateStoreSubscr());
        break;
      }
      case ByteCode::GET_ITER: {
        insts.Push(CreateGetIter());
        break;
      }
      case ByteCode::FOR_ITER: {
        insts.Push(CreateForIter(Runtime::ReadI64(iter)));
        break;
      }
      case ByteCode::LOAD_BUILD_CLASS: {
        insts.Push(CreateLoadBuildClass());
        break;
      }
      case ByteCode::STORE_ATTR: {
        insts.Push(CreateStoreAttr(Runtime::ReadU64(iter)));
        break;
      }
      case ByteCode::NOP: {
        insts.Push(CreateNop());
        break;
      }
      case ByteCode::UNARY_POSITIVE: {
        insts.Push(CreateUnaryPositive());
        break;
      }
      case ByteCode::UNARY_NEGATIVE: {
        insts.Push(CreateUnaryNegative());
        break;
      }
      case ByteCode::UNARY_NOT: {
        insts.Push(CreateUnaryNot());
        break;
      }
      case ByteCode::UNARY_INVERT: {
        insts.Push(CreateUnaryInvert());
        break;
      }
      case ByteCode::BINARY_POWER: {
        insts.Push(CreateBinaryPower());
        break;
      }
      case ByteCode::BINARY_MODULO: {
        insts.Push(CreateBinaryModulo());
        break;
      }
      case ByteCode::BINARY_FLOOR_DIVIDE: {
        insts.Push(CreateBinaryFloorDivide());
        break;
      }
      case ByteCode::BINARY_TRUE_DIVIDE: {
        insts.Push(CreateBinaryTrueDivide());
        break;
      }
      case ByteCode::BINARY_LSHIFT: {
        insts.Push(CreateBinaryLShift());
        break;
      }
      case ByteCode::BINARY_RSHIFT: {
        insts.Push(CreateBinaryRShift());
        break;
      }
      case ByteCode::BINARY_AND: {
        insts.Push(CreateBinaryAnd());
        break;
      }
      case ByteCode::BINARY_XOR: {
        insts.Push(CreateBinaryXor());
        break;
      }
      case ByteCode::BINARY_OR: {
        insts.Push(CreateBinaryOr());
        break;
      }
      case ByteCode::YIELD_VALUE: {
        insts.Push(CreateYieldValue());
        break;
      }
      case ByteCode::JUMP_FORWARD: {
        insts.Push(CreateJumpForward(Runtime::ReadU64(iter)));
        break;
      }
      default:
        throw std::runtime_error(
          "Unknown byte code:" + std::to_string(static_cast<int>(iter.Get()))
        );
        break;
    }
  }
  code->SetInstructions(std::make_shared<PyList>(insts));
}

PyObjPtr FrameKlass::repr(const PyObjPtr& obj) {
  if (!obj->is<PyFrame>()) {
    throw std::runtime_error("repr(): klass is not a frame");
  }
  auto frame = obj->as<PyFrame>();
  return StringConcat(CreatePyList(
    {CreatePyString("<frame at ")->as<PyString>(),
     Function::Identity(CreatePyList({obj}))->as<PyString>(),
     CreatePyString(">")->as<PyString>()}
  ));
}

void PrintFrame(const PyFramePtr& frame) {
  frame->repr()->as<PyString>()->PrintLine();
  CreatePyString("Program Counter: ")->as<PyString>()->Print();
  CreatePyInteger(frame->ProgramCounter())
    ->repr()
    ->as<PyString>()
    ->PrintLine(false);
  CreatePyString("Current Instruction: ")->as<PyString>()->Print();
  frame->Instruction()->repr()->as<PyString>()->PrintLine(false);
  CreatePyString("Code: ")->as<PyString>()->PrintLine();
  PyString::IncreaseIndent();
  PrintCode(frame->Code());
  PyString::DecreaseIndent();
  CreatePyString("Stack(*ptr): ")->as<PyString>()->PrintLine();
  auto stack = frame->CurrentStack();
  for (Index i = 0; i < stack->Length(); i++) {
    CreatePyInteger(i)->repr()->as<PyString>()->Print();
    CreatePyString("  ")->as<PyString>()->Print();
    stack->GetItem(i)->repr()->as<PyString>()->Print();
    std::cout << " ( " << stack->GetItem(i).get() << " ) " << std::endl;
  }
  CreatePyString("Locals: ")->as<PyString>()->PrintLine();
  frame->CurrentLocals()->str()->as<PyString>()->PrintLine();
  CreatePyString("Globals: ")->as<PyString>()->PrintLine();
  frame->CurrentGlobals()->str()->as<PyString>()->PrintLine();
  CreatePyString("FastLocals: ")->as<PyString>()->PrintLine();
  frame->CurrentFastLocals()->str()->as<PyString>()->PrintLine();
  // 调用栈
  CreatePyString("Caller: ")->as<PyString>()->Print();
  if (frame->HasCaller()) {
    PyString::IncreaseIndent();
    PrintFrame(frame->Caller());
    PyString::DecreaseIndent();
  } else {
    CreatePyString("This is the top frame")->as<PyString>()->PrintLine();
  }
}

PyFramePtr PyFrame::Caller() const {
  return caller;
}

bool PyFrame::HasCaller() const {
  return caller != nullptr;
}

PyObjPtr PyFrame::Eval() {
  while (!Finished()) {
    const auto& inst = Instruction();
    if (ArgsHelper::Instance().Has("debug")) {
      CreatePyString("-------------------")->as<PyString>()->PrintLine();
      PrintFrame(shared_from_this()->as<PyFrame>());
    }
    switch (inst->Code()) {
      case ByteCode::LOAD_CONST: {
        auto key = std::get<Index>(inst->Operand());
        auto value = Code()->Consts()->getitem(CreatePyInteger(key));
        stack.Push(value);
        NextProgramCounter();
        break;
      }
      case ByteCode::STORE_GLOBAL: {
        auto key = std::get<Index>(inst->Operand());
        auto value = stack.Pop();
        globals->setitem(CreatePyInteger(key), value);
        NextProgramCounter();
        break;
      }
      case ByteCode::STORE_FAST: {
        auto index = std::get<Index>(inst->Operand());
        auto value = stack.Pop();
        fastLocals->setitem(CreatePyInteger(index), value);
        NextProgramCounter();
        break;
      }
      case ByteCode::COMPARE_OP: {
        auto oprt = std::get<CompareOp>(inst->Operand());
        auto right = stack.Pop();
        auto left = stack.Pop();
        switch (oprt) {
          case CompareOp::EQUAL: {
            stack.Push(left->eq(right));
            break;
          }
          case CompareOp::NOT_EQUAL: {
            stack.Push(left->ne(right));
            break;
          }
          case CompareOp::LESS_THAN: {
            stack.Push(left->lt(right));
            break;
          }
          case CompareOp::LESS_THAN_EQUAL: {
            stack.Push(left->le(right));
            break;
          }
          case CompareOp::GREATER_THAN: {
            auto result = left->gt(right);
            stack.Push(left->gt(right));
            break;
          }
          case CompareOp::GREATER_THAN_EQUAL: {
            stack.Push(left->ge(right));
            break;
          }
          case CompareOp::IN: {
            stack.Push(right->contains(left));
            break;
          }
          case CompareOp::NOT_IN: {
            stack.Push(Not(right->contains(left)));
            break;
          }
          case CompareOp::IS: {
            stack.Push(CreatePyBoolean(left.get() == right.get()));
            break;
          }
          case CompareOp::IS_NOT: {
            stack.Push(CreatePyBoolean(left.get() != right.get()));
            break;
          }
          default:
            throw std::runtime_error("Unknown compare operation");
        }
        NextProgramCounter();
        break;
      }
      case ByteCode::POP_JUMP_IF_FALSE: {
        auto needJump = stack.Pop();
        if (!IsTrue(needJump)) {
          SetProgramCounter(static_cast<Index>(
            static_cast<int64_t>(ProgramCounter()) +
            std::get<int64_t>(inst->Operand())
          ));
        } else {
          NextProgramCounter();
        }
        break;
      }
      case ByteCode::POP_JUMP_IF_TRUE: {
        auto needJump = stack.Pop();
        if (IsTrue(needJump)) {
          SetProgramCounter(static_cast<Index>(
            static_cast<int64_t>(ProgramCounter()) +
            std::get<int64_t>(inst->Operand())
          ));
        } else {
          NextProgramCounter();
        }
        break;
      }
      case ByteCode::BINARY_ADD: {
        auto right = stack.Pop();
        auto left = stack.Pop();
        stack.Push(left->add(right));
        NextProgramCounter();
        break;
      }
      case ByteCode::BINARY_SUBTRACT: {
        auto right = stack.Pop();
        auto left = stack.Pop();
        stack.Push(left->sub(right));
        NextProgramCounter();
        break;
      }
      case ByteCode::BINARY_MULTIPLY: {
        auto right = stack.Pop();
        auto left = stack.Pop();
        stack.Push(left->mul(right));
        NextProgramCounter();
        break;
      }
      case ByteCode::BINARY_MATRIX_MULTIPLY: {
        auto right = stack.Pop();
        auto left = stack.Pop();
        stack.Push(left->matmul(right));
        NextProgramCounter();
        break;
      }
      case ByteCode::BINARY_TRUE_DIVIDE: {
        auto right = stack.Pop();
        auto left = stack.Pop();
        stack.Push(left->truediv(right));
        NextProgramCounter();
        break;
      }
      case ByteCode::BINARY_FLOOR_DIVIDE: {
        auto right = stack.Pop();
        auto left = stack.Pop();
        stack.Push(left->floordiv(right));
        NextProgramCounter();
        break;
      }
      case ByteCode::BINARY_XOR: {
        auto right = stack.Pop();
        auto left = stack.Pop();
        stack.Push(left->_xor_(right));
        NextProgramCounter();
        break;
      }
      case ByteCode::BINARY_AND: {
        auto right = stack.Pop();
        auto left = stack.Pop();
        stack.Push(left->_and_(right));
        NextProgramCounter();
        break;
      }
      case ByteCode::BINARY_OR: {
        auto right = stack.Pop();
        auto left = stack.Pop();
        stack.Push(left->_or_(right));
        NextProgramCounter();
        break;
      }
      case ByteCode::BINARY_POWER: {
        auto right = stack.Pop();
        auto left = stack.Pop();
        stack.Push(left->pow(right));
        NextProgramCounter();
        break;
      }
      case ByteCode::BINARY_MODULO: {
        auto right = stack.Pop();
        auto left = stack.Pop();
        stack.Push(left->mod(right));
        NextProgramCounter();
        break;
      }
      case ByteCode::BINARY_LSHIFT: {
        auto right = stack.Pop();
        auto left = stack.Pop();
        stack.Push(left->lshift(right));
        NextProgramCounter();
        break;
      }
      case ByteCode::BINARY_RSHIFT: {
        auto right = stack.Pop();
        auto left = stack.Pop();
        stack.Push(left->rshift(right));
        NextProgramCounter();
        break;
      }
      case ByteCode::UNARY_POSITIVE: {
        auto operand = stack.Pop();
        stack.Push(operand->pos());
        NextProgramCounter();
        break;
      }
      case ByteCode::UNARY_NEGATIVE: {
        auto operand = stack.Pop();
        stack.Push(operand->neg());
        NextProgramCounter();
        break;
      }
      case ByteCode::UNARY_NOT: {
        auto operand = stack.Pop();
        stack.Push(Not(operand->boolean()));
        NextProgramCounter();
        break;
      }
      case ByteCode::UNARY_INVERT: {
        auto operand = stack.Pop();
        stack.Push(operand->invert());
        NextProgramCounter();
        break;
      }
      case ByteCode::BINARY_SUBSCR: {
        auto index = stack.Pop();
        auto obj = stack.Pop();
        stack.Push(obj->getitem(index));
        NextProgramCounter();
        break;
      }
      case ByteCode::RETURN_VALUE: {
        auto value = stack.Pop();
        return value;
        break;
      }
      case ByteCode::MAKE_FUNCTION: {
        auto name = stack.Pop();
        if (!name->is<PyString>()) {
          throw std::runtime_error("Function name must be string");
        }
        auto code = stack.Pop();
        if (!code->is<PyCode>()) {
          throw std::runtime_error("Function code must be code object");
        }
        auto func = CreatePyFunction(code, globals);
        stack.Push(func);
        NextProgramCounter();
        break;
      }
      case ByteCode::LOAD_FAST: {
        auto index = std::get<Index>(inst->Operand());
        auto value = fastLocals->GetItem(index);
        stack.Push(value);
        NextProgramCounter();
        break;
      }
      case ByteCode::CALL_FUNCTION: {
        auto argumentCount = std::get<Index>(inst->Operand());
        auto argList = CreatePyList(stack.Top(argumentCount))->as<PyList>();
        auto func = stack.Pop();
        auto result = Runtime::Interpreter::Eval(func, argList);
        stack.Push(result);
        NextProgramCounter();
        break;
      }
      case ByteCode::LOAD_GLOBAL: {
        auto index = std::get<Index>(inst->Operand());
        auto key = Code()->Names()->GetItem(index);
        bool found = false;
        PyObjPtr value = CreatePyNone();
        if (IsTrue(globals->contains(key))) {
          found = true;
          value = globals->getitem(key);
        }
        if (!found && IsTrue(Runtime::Interpreter::Instance().Builtins()->contains(key))) {
          found = true;
          value = Runtime::Interpreter::Instance().Builtins()->getitem(key);
        }
        if (!found) {
          auto errorMessage = StringConcat(CreatePyList(
            {CreatePyString("NameError: name '"), key,
             CreatePyString("' is not defined")}
          ));
          throw std::runtime_error(errorMessage->as<PyString>()->ToCppString());
        }
        stack.Push(value);
        NextProgramCounter();
        break;
      }
      case ByteCode::STORE_NAME: {
        auto index = std::get<Index>(inst->Operand());
        auto key = Code()->Names()->GetItem(index);
        auto value = stack.Pop();
        locals->setitem(key, value);
        NextProgramCounter();
        break;
      }
      case ByteCode::LOAD_NAME: {
        auto index = std::get<Index>(inst->Operand());
        auto key = Code()->Names()->GetItem(index);
        // LEGB rule
        // local -> enclosing -> global -> built-in
        bool found = false;
        PyObjPtr value = CreatePyNone();
        if (IsTrue(locals->contains(key))) {
          found = true;
          value = locals->getitem(key);
        }
        if (!found && IsTrue(globals->contains(key))) {
          found = true;
          value = globals->getitem(key);
        }
        if (!found && IsTrue(Runtime::Interpreter::Instance().Builtins()->contains(key))) {
          found = true;
          value = Runtime::Interpreter::Instance().Builtins()->getitem(key);
        }
        if (!found) {
          throw std::runtime_error(
            "NameError: name '" + key->as<PyString>()->ToCppString() +
            "' is not defined"
          );
          auto errorMessage = StringConcat(CreatePyList(
            {CreatePyString("NameError: name '"), key,
             CreatePyString("' is not defined")}
          ));
          throw std::runtime_error(errorMessage->as<PyString>()->ToCppString());
        }
        stack.Push(value);
        NextProgramCounter();
        break;
      }
      case ByteCode::POP_TOP: {
        stack.Pop();
        NextProgramCounter();
        break;
      }
      case ByteCode::LOAD_ATTR: {
        auto index = std::get<Index>(inst->Operand());
        auto key = Code()->Names()->GetItem(index);
        auto obj = stack.Pop();
        auto value = obj->is<PyType>()
                       ? obj->as<PyType>()->Owner()->Attributes()->getitem(key)
                       : obj->getattr(key);
        if (value == nullptr) {
          std::cout << "object attributes: " << std::endl;
          obj->Attributes()->str()->as<PyString>()->PrintLine();
          std::cout << "class attributes: " << std::endl;
          obj->Klass()->Attributes()->str()->as<PyString>()->PrintLine();
          std::cout << "mro: " << std::endl;
          obj->Klass()->Mro()->str()->as<PyString>()->PrintLine();
          for (Index i = 0; i < obj->Klass()->Mro()->Length(); i++) {
            auto mro = obj->Klass()->Mro()->GetItem(i)->as<PyType>();
            mro->Owner()->Name()->str()->as<PyString>()->PrintLine();
            mro->str()->as<PyString>()->PrintLine();
          }
          throw std::runtime_error(
            "AttributeError: '" +
            obj->Klass()->Name()->as<PyString>()->ToCppString() +
            "' object has no attribute '" + key->as<PyString>()->ToCppString() +
            "'"
          );
        }
        stack.Push(value);
        NextProgramCounter();
        break;
      }
      case ByteCode::BUILD_LIST: {
        auto size = std::get<Index>(inst->Operand());
        Collections::List<PyObjPtr> elements(size);
        for (Index i = 0; i < size; i++) {
          elements.Push(stack.Pop());
        }
        auto list = CreatePyList(elements);
        stack.Push(list);
        NextProgramCounter();
        break;
      }
      case ByteCode::BUILD_SLICE: {
        auto step = stack.Pop();
        auto end = stack.Pop();
        auto start = stack.Pop();
        auto slice = CreatePySlice(start, end, step);
        stack.Push(slice);
        NextProgramCounter();
        break;
      }
      case ByteCode::JUMP_ABSOLUTE: {
        SetProgramCounter(std::get<Index>(inst->Operand()));
        break;
      }
      case ByteCode::STORE_SUBSCR: {
        auto index = stack.Pop();
        auto obj = stack.Pop();
        auto value = stack.Pop();
        obj->setitem(index, value);
        NextProgramCounter();
        break;
      }
      case ByteCode::GET_ITER: {
        auto obj = stack.Pop();
        auto iter = obj->iter();
        stack.Push(iter);
        NextProgramCounter();
        break;
      }
      case ByteCode::FOR_ITER: {
        auto iter = stack.Pop();
        auto value = iter->next();
        if (value->is<IterDone>()) {
          SetProgramCounter(static_cast<Index>(
            static_cast<int64_t>(ProgramCounter()) +
            std::get<int64_t>(inst->Operand())
          ));
        } else {
          stack.Push(iter);
          stack.Push(value);
          NextProgramCounter();
        }
        break;
      }
      case ByteCode::LOAD_BUILD_CLASS: {
        stack.Push(Runtime::Interpreter::Instance().Builtins()->getitem(
          CreatePyString("__build_class__")
        ));
        NextProgramCounter();
        break;
      }
      case ByteCode::STORE_ATTR: {
        auto index = std::get<Index>(inst->Operand());
        auto key = Code()->Names()->GetItem(index);
        auto obj = stack.Pop();
        auto value = stack.Pop();
        obj->setattr(key, value);
        NextProgramCounter();
        break;
      }
      case ByteCode::NOP: {
        NextProgramCounter();
        break;
      }
      case ByteCode::YIELD_VALUE: {
        NextProgramCounter();
        return CreatePyGenerator(shared_from_this()->as<PyFrame>());
        break;
      }
      case ByteCode::JUMP_FORWARD: {
        SetProgramCounter(programCounter + std::get<Index>(inst->Operand()));
        break;
      }
      case ByteCode::BUILD_MAP: {
        auto size = std::get<Index>(inst->Operand());
        auto map = CreatePyDict();
        for (Index i = 0; i < size; i++) {
          auto value = stack.Pop();
          auto key = stack.Pop();
          map->setitem(key, value);
        }
        stack.Push(map);
        NextProgramCounter();
        break;
      }
    }
  }
  return CreatePyNone();
}

PyObjPtr PyFrame::EvalWithDestory() {
  auto result = Eval();
  Runtime::Interpreter::Instance().BackToParentFrame();
  return result;
}

}  // namespace torchlight::Object
