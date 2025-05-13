#include "Object/Runtime/PyFrame.h"
#include "ByteCode/ByteCode.h"
#include "Collections/Stack.h"
#include "Collections/String/BytesHelper.h"
#include "Function/BuiltinFunction.h"
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
#include "Tools/Config/Config.h"
#include "Tools/Logger/BytecodeLogger.h"
#include "Tools/Logger/ConsoleLogger.h"
#include "Tools/Logger/ErrorLogger.h"
#include "Tools/Logger/VerboseLogger.h"

namespace tensorslow::Object {

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
  if (code->ByteCode() == nullptr) {
    //    ErrorLogger::getInstance().log(
    //      "bytecode passing in memory or something wrong"
    //    );
    return;
  }
  auto bytes = code->ByteCode()->Value().CopyCodeUnits();
  Index iter = 0;
  if (static_cast<Literal>(bytes[iter]) != Literal::LIST) {
    throw std::runtime_error("Invalid insts");
  }
  iter++;
  Index size = Collections::DeserializeU64(bytes, iter);
  auto insts = Collections::List<PyObjPtr>(size);
  while ((size--) != 0U) {
    auto byte = bytes[iter++];
    switch (static_cast<ByteCode>(byte)) {
      case ByteCode::LOAD_CONST: {
        insts.Push(CreateLoadConst(Collections::DeserializeU64(bytes, iter)));
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
        insts.Push(CreateStoreFast(Collections::DeserializeU64(bytes, iter)));
        break;
      }
      case ByteCode::LOAD_FAST: {
        insts.Push(CreateLoadFast(Collections::DeserializeU64(bytes, iter)));
        break;
      }
      case ByteCode::COMPARE_OP: {
        auto compareOp = bytes[iter++];
        insts.Push(CreateCompareOp(static_cast<CompareOp>(compareOp)));
        break;
      }
      case ByteCode::POP_JUMP_IF_FALSE: {
        insts.Push(CreatePopJumpIfFalse(Collections::DeserializeI64(bytes, iter)
        ));
        break;
      }
      case ByteCode::POP_JUMP_IF_TRUE: {
        insts.Push(CreatePopJumpIfTrue(Collections::DeserializeI64(bytes, iter))
        );
        break;
      }
      case ByteCode::MAKE_FUNCTION: {
        insts.Push(CreateMakeFunction());
        break;
      }
      case ByteCode::CALL_FUNCTION: {
        insts.Push(CreateCallFunction(Collections::DeserializeU64(bytes, iter))
        );
        break;
      }
      case ByteCode::RETURN_VALUE: {
        insts.Push(CreateReturnValue());
        break;
      }
      case ByteCode::LOAD_NAME: {
        insts.Push(CreateLoadName(Collections::DeserializeU64(bytes, iter)));
        break;
      }
      case ByteCode::STORE_NAME: {
        insts.Push(CreateStoreName(Collections::DeserializeU64(bytes, iter)));
        break;
      }
      case ByteCode::LOAD_GLOBAL: {
        insts.Push(CreateLoadGlobal(Collections::DeserializeU64(bytes, iter)));
        break;
      }
      case ByteCode::POP_TOP: {
        insts.Push(CreatePopTop());
        break;
      }
      case ByteCode::LOAD_ATTR: {
        insts.Push(CreateLoadAttr(Collections::DeserializeU64(bytes, iter)));
        break;
      }
      case ByteCode::BUILD_LIST: {
        insts.Push(CreateBuildList(Collections::DeserializeU64(bytes, iter)));
        break;
      }
      case ByteCode::BUILD_SLICE: {
        insts.Push(CreateBuildSlice());
        break;
      }
      case ByteCode::BUILD_MAP: {
        insts.Push(CreateBuildMap(Collections::DeserializeU64(bytes, iter)));
        break;
      }
      case ByteCode::BINARY_MATRIX_MULTIPLY: {
        insts.Push(CreateBinaryMatrixMultiply());
        break;
      }
      case ByteCode::JUMP_ABSOLUTE: {
        insts.Push(CreateJumpAbsolute(Collections::DeserializeU64(bytes, iter))
        );
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
        insts.Push(CreateForIter(Collections::DeserializeI64(bytes, iter)));
        break;
      }
      case ByteCode::LOAD_BUILD_CLASS: {
        insts.Push(CreateLoadBuildClass());
        break;
      }
      case ByteCode::STORE_ATTR: {
        insts.Push(CreateStoreAttr(Collections::DeserializeU64(bytes, iter)));
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
        insts.Push(CreateJumpForward(Collections::DeserializeU64(bytes, iter)));
        break;
      }
      default:
        throw std::runtime_error(
          "Unknown byte code:" + std::to_string(static_cast<int>(bytes[iter]))
        );
    }
  }
  code->SetInstructions(std::make_shared<PyList>(insts));
}

PyObjPtr FrameKlass::repr(const PyObjPtr& obj) {
  if (!obj->is(FrameKlass::Self())) {
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
  // Frame representation
  VerboseLogger::getInstance().log(frame->repr()->as<PyString>()->ToCppString()
  );
  VerboseLogger::getInstance().log("\n");

  // Program Counter
  VerboseLogger::getInstance().log("Program Counter: ");
  auto pc_repr = CreatePyInteger(frame->ProgramCounter())
                   ->repr()
                   ->as<PyString>()
                   ->ToCppString();
  VerboseLogger::getInstance().log(pc_repr);

  // Current Instruction
  VerboseLogger::getInstance().log("\nCurrent Instruction: ");
  auto instr_repr = frame->Instruction()->repr()->as<PyString>()->ToCppString();
  VerboseLogger::getInstance().log(instr_repr);

  // Code
  VerboseLogger::getInstance().log("\nCode:\n");
  VerboseLogger::IncreaseIndent();
  PrintCode(frame->Code());
  VerboseLogger::DecreaseIndent();

  // Stack
  VerboseLogger::getInstance().log("\nStack(*ptr):\n");
  auto stack = frame->CurrentStack();
  for (Index i = 0; i < stack->Length(); i++) {
    auto index_repr = CreatePyInteger(i)->repr()->as<PyString>()->ToCppString();
    VerboseLogger::getInstance().log(index_repr);
    VerboseLogger::getInstance().log("  ");
    auto item = stack->GetItem(i);
    auto item_repr = item->repr()->as<PyString>()->ToCppString();
    VerboseLogger::getInstance().log(item_repr);
    auto ptr = reinterpret_cast<uint64_t>(item.get());
    std::string ptr_str = " ( " + std::to_string(ptr) + " ) ";
    VerboseLogger::getInstance().log(ptr_str);
  }

  // Locals
  VerboseLogger::getInstance().log("\nLocals:\n");
  auto locals_repr =
    frame->CurrentLocals()->repr()->as<PyString>()->ToCppString();
  VerboseLogger::getInstance().log(locals_repr + "\n");

  // Globals
  VerboseLogger::getInstance().log("Globals:\n");
  auto globals_repr =
    frame->CurrentGlobals()->repr()->as<PyString>()->ToCppString();
  VerboseLogger::getInstance().log(globals_repr + "\n");

  // FastLocals
  VerboseLogger::getInstance().log("FastLocals:\n");
  auto fast_locals_repr =
    frame->CurrentFastLocals()->repr()->as<PyString>()->ToCppString();
  VerboseLogger::getInstance().log(fast_locals_repr + "\n");

  // Caller
  VerboseLogger::getInstance().log("Caller: ");
  if (frame->HasCaller()) {
    VerboseLogger::IncreaseIndent();
    PrintFrame(frame->Caller());
    VerboseLogger::DecreaseIndent();
  } else {
    VerboseLogger::getInstance().log("This is the top frame\n");
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
    if (Config::Has("verbose")) {
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
      }
      case ByteCode::MAKE_FUNCTION: {
        auto name = stack.Pop();
        if (!name->is(StringKlass::Self())) {
          throw std::runtime_error("Function name must be string");
        }
        auto code = stack.Pop();
        if (!code->is(CodeKlass::Self())) {
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
        auto value = obj->getattr(key);
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
        if (value->is(Object::IterDoneKlass::Self())) {
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

}  // namespace tensorslow::Object
