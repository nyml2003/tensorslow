#include "ByteCode/ByteCode.h"
#include "ByteCode/PyCode.h"
#include "Collections/IntegerHelper.h"
#include "Collections/List.h"
#include "Function/PyFunction.h"
#include "Function/PyMethod.h"
#include "Function/PyNativeFunction.h"
#include "Object/MixinCollections.h"
#include "Object/PyBoolean.h"
#include "Object/PyDictionary.h"
#include "Object/PyInteger.h"
#include "Object/PyNone.h"
#include "Object/PyObject.h"
#include "Object/PyString.h"
#include "Runtime/Genesis.h"
#include "Runtime/Interpreter.h"
#include "Runtime/PyFrame.h"

#include <memory>
#include <stdexcept>
namespace torchlight::Runtime {

Interpreter::Interpreter() {
  frame = Object::PyNone::Instance();
  builtins = std::dynamic_pointer_cast<Object::PyDictionary>(Genesis());
}

void Interpreter::Run(const Object::PyCodePtr& code) {
  frame = CreateFrameWithCode(code);
  EvalFrame();
  DestroyFrame();
}

void Interpreter::BuildFrameWithFunction(
  const Object::PyObjPtr& func,
  const Object::PyObjPtr& _arguments
) {
  if (_arguments->Klass() != Object::ListKlass::Self()) {
    throw std::runtime_error("Cannot build frame with non-list arguments");
  }
  auto arguments = std::dynamic_pointer_cast<Object::PyList>(_arguments);
  if (func->Klass() == Object::FunctionKlass::Self()) {
    PyFramePtr new_frame = CreateFrameWithFunction(func, arguments, frame);
    frame = new_frame;
    return;
  }
  if (func->Klass() == Object::NativeFunctionKlass::Self()) {
    auto nativeFunction =
      std::dynamic_pointer_cast<Object::PyNativeFunction>(func);
    auto result = nativeFunction->Call(arguments);
    auto frameObject = std::dynamic_pointer_cast<PyFrame>(frame);
    frameObject->Stack().Push(result);
    return;
  }
  if (func->Klass() == Object::MethodKlass::Self()) {
    auto method = std::dynamic_pointer_cast<Object::PyMethod>(func);
    auto owner = method->Owner();
    auto function = method->Method();
    Object::PyObjPtr new_arguments =
      Object::CreatePyList({owner})->add(arguments);
    BuildFrameWithFunction(function, new_arguments);
    return;
  }
  throw std::runtime_error(
    "Unknown function type" + Collections::ToCppString(func->Klass()->Name())
  );
}

void Interpreter::EvalFrame() {
  if (frame->Klass() != FrameKlass::Self()) {
    throw std::runtime_error("Cannot evaluate non-frame object");
  }
  while (!std::dynamic_pointer_cast<PyFrame>(frame)->Finished()) {
    auto frameObject = std::dynamic_pointer_cast<PyFrame>(frame);
    const auto& inst = frameObject->Instruction();
    // Object::DebugPrint(Object::CreatePyString("-------------------"));
    // Object::DebugPrint(frameObject);
    switch (inst->Code()) {
      case Object::ByteCode::LOAD_CONST: {
        auto key = std::get<Index>(inst->Operand());
        auto value =
          frameObject->Code()->Consts()->getitem(Object::CreatePyInteger(key));
        frameObject->Stack().Push(value);
        frameObject->NextProgramCounter();
        break;
      }
      case Object::ByteCode::STORE_FAST: {
        auto index = std::get<Index>(inst->Operand());
        auto value = frameObject->Stack().Pop();
        frameObject->FastLocals()->setitem(
          Object::CreatePyInteger(index), value
        );
        frameObject->NextProgramCounter();
        break;
      }
      case Object::ByteCode::COMPARE_OP: {
        auto op = std::get<Object::CompareOp>(inst->Operand());
        auto right = frameObject->Stack().Pop();
        auto left = frameObject->Stack().Pop();
        switch (op) {
          case Object::CompareOp::EQUAL: {
            frameObject->Stack().Push(left->eq(right));
            auto result = left->eq(right);
            break;
          }
          case Object::CompareOp::NOT_EQUAL: {
            frameObject->Stack().Push(left->ne(right));
            auto result = left->ne(right);
            break;
          }
          case Object::CompareOp::LESS_THAN: {
            frameObject->Stack().Push(left->lt(right));
            auto result = left->lt(right);
            break;
          }
          case Object::CompareOp::LESS_THAN_EQUAL: {
            frameObject->Stack().Push(left->le(right));
            auto result = left->le(right);
            break;
          }
          case Object::CompareOp::GREATER_THAN: {
            frameObject->Stack().Push(left->gt(right));
            auto result = left->gt(right);
            break;
          }
          case Object::CompareOp::GREATER_THAN_EQUAL: {
            frameObject->Stack().Push(left->ge(right));
            auto result = left->ge(right);
            break;
          }
          default:
            throw std::runtime_error("Unknown compare operation");
        }
        frameObject->NextProgramCounter();
        break;
      }
      case Object::ByteCode::POP_JUMP_IF_FALSE: {
        auto needJump = frameObject->Stack().Pop();
        if (!(needJump->Klass() == Object::BooleanKlass::Self())) {
          throw std::runtime_error("Cannot jump if not boolean");
        }
        auto bool_needJump =
          std::dynamic_pointer_cast<Object::PyBoolean>(needJump);
        if (bool_needJump == nullptr) {
          throw std::runtime_error("Cannot jump if not boolean");
        }
        if (bool_needJump->Value()) {
          frameObject->NextProgramCounter();
        } else {
          frameObject->SetProgramCounter(Collections::safe_add(
            frameObject->ProgramCounter(), std::get<int64_t>(inst->Operand())
          ));
        }
        break;
      }
      case Object::ByteCode::POP_JUMP_IF_TRUE: {
        auto needJump = frameObject->Stack().Pop();
        if (!(needJump->Klass() == Object::BooleanKlass::Self())) {
          throw std::runtime_error("Cannot jump if not boolean");
        }
        auto bool_needJump =
          std::dynamic_pointer_cast<Object::PyBoolean>(needJump);
        if (bool_needJump == nullptr) {
          throw std::runtime_error("Cannot jump if not boolean");
        }
        if (bool_needJump->Value()) {
          frameObject->SetProgramCounter(Collections::safe_add(
            frameObject->ProgramCounter(), std::get<int64_t>(inst->Operand())
          ));

        } else {
          frameObject->NextProgramCounter();
        }
        break;
      }
      case Object::ByteCode::BINARY_ADD: {
        auto right = frameObject->Stack().Pop();
        auto left = frameObject->Stack().Pop();
        frameObject->Stack().Push(left->add(right));
        frameObject->NextProgramCounter();
        break;
      }
      case Object::ByteCode::BINARY_SUBTRACT: {
        auto right = frameObject->Stack().Pop();
        auto left = frameObject->Stack().Pop();
        frameObject->Stack().Push(left->sub(right));
        frameObject->NextProgramCounter();
        break;
      }
      case Object::ByteCode::BINARY_MULTIPLY: {
        auto right = frameObject->Stack().Pop();
        auto left = frameObject->Stack().Pop();
        frameObject->Stack().Push(left->mul(right));
        frameObject->NextProgramCounter();
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
      case Object::ByteCode::RETURN_VALUE: {
        returnValue = frameObject->Stack().Pop();
        if (frameObject->HasCaller()) {
          LeaveFrame();
        }
        break;
      }
      case Object::ByteCode::MAKE_FUNCTION: {
        auto name = frameObject->Stack().Pop();
        if (name->Klass() != Object::StringKlass::Self()) {
          throw std::runtime_error("Function name must be string");
        }
        auto code = frameObject->Stack().Pop();
        if (code->Klass() != Object::CodeKlass::Self()) {
          throw std::runtime_error("Function code must be code object");
        }

        auto func = Object::CreatePyFunction(code, frameObject->Globals());
        frameObject->Stack().Push(func);
        frameObject->NextProgramCounter();
        break;
      }
      case Object::ByteCode::LOAD_FAST: {
        auto index = std::get<Index>(inst->Operand());
        auto value = frameObject->FastLocals()->Value().Get(index);
        frameObject->Stack().Push(value);
        frameObject->NextProgramCounter();
        break;
      }
      case Object::ByteCode::CALL_FUNCTION: {
        auto argumentCount = std::get<Index>(inst->Operand());
        Collections::List<Object::PyObjPtr> arguments(argumentCount);
        for (Index i = 0; i < argumentCount; i++) {
          arguments.Push(frameObject->Stack().Pop());
        }
        BuildFrameWithFunction(
          frameObject->Stack().Pop(), CreatePyList(arguments)
        );
        frameObject->NextProgramCounter();
        break;
      }
      case Object::ByteCode::LOAD_GLOBAL: {
        auto index = std::get<Index>(inst->Operand());
        auto key = frameObject->Code()->Names()->Value().Get(index);
        auto value = frameObject->Globals()->getitem(key);
        frameObject->Stack().Push(value);
        frameObject->NextProgramCounter();
        break;
      }
      case Object::ByteCode::STORE_NAME: {
        auto index = std::get<Index>(inst->Operand());
        auto key = frameObject->Code()->Names()->Value().Get(index);
        auto value = frameObject->Stack().Pop();
        frameObject->Globals()->setitem(key, value);
        frameObject->NextProgramCounter();
        break;
      }
      case Object::ByteCode::LOAD_NAME: {
        auto index = std::get<Index>(inst->Operand());
        auto key = frameObject->Code()->Names()->Value().Get(index);
        // LEGB rule
        // local -> enclosing -> global -> built-in
        bool found = false;
        Object::PyObjPtr value = Object::CreatePyNone();
        if (Object::IsTrue(frameObject->Locals()->contains(key))) {
          found = true;
          value = frameObject->Locals()->getitem(key);
        }
        if (!found && Object::IsTrue(frameObject->Globals()->contains(key))) {
          found = true;
          value = frameObject->Globals()->getitem(key);
        }
        if (!found && Object::IsTrue(builtins->contains(key))) {
          found = true;
          value = builtins->getitem(key);
        }
        if (!found) {
          Object::DebugPrint(key);
          throw std::runtime_error("NameError: name is not defined");
        }
        frameObject->Stack().Push(value);
        frameObject->NextProgramCounter();
        break;
      }
      case Object::ByteCode::POP_TOP: {
        frameObject->Stack().Pop();
        frameObject->NextProgramCounter();
        break;
      }
      case Object::ByteCode::LOAD_ATTR: {
        auto index = std::get<Index>(inst->Operand());
        auto key = frameObject->Code()->Names()->Value().Get(index);
        auto obj = frameObject->Stack().Pop();
        auto value = obj->getattr(key);
        frameObject->Stack().Push(value);
        frameObject->NextProgramCounter();
        break;
      }
      case Object::ByteCode::ERROR: {
        throw std::runtime_error("Unknown byte code");
        break;
      }
        throw std::runtime_error("Unknown byte code");
    }
  }
}

void Interpreter::DestroyFrame() {
  if (frame->Klass() != FrameKlass::Self()) {
    throw std::runtime_error("Cannot destroy non-frame object");
  }
  frame = std::dynamic_pointer_cast<PyFrame>(frame)->Caller();
}

void Interpreter::LeaveFrame() {
  DestroyFrame();
  auto frameObject = std::dynamic_pointer_cast<PyFrame>(frame);
  frameObject->Stack().Push(returnValue);
}

}  // namespace torchlight::Runtime