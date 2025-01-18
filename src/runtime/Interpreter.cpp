#include "Collections/IntegerHelper.h"
#include "Collections/StringHelper.h"
#include "Object/ByteCode.h"
#include "Object/PyBoolean.h"
#include "Runtime/Interpreter.h"

#include "Object/PyCode.h"
#include "Object/PyInteger.h"
#include "Object/PyList.h"
#include "Object/PyNone.h"
#include "Object/PyString.h"
#include "Runtime/PyFrame.h"
#include "Runtime/PyFunction.h"

#include <iostream>
#include <memory>
#include <stdexcept>
namespace torchlight::Runtime {

Interpreter::Interpreter() {
  frame = Object::PyNone::Instance();
}

void Interpreter::Run(const Object::PyCodePtr& code) {
  frame = CreateFrameWithCode(code);
  EvalFrame();
  DestroyFrame();
}

void Interpreter::BuildFrameWithFunction(
  const Object::PyObjPtr& func,
  const Collections::List<Object::PyObjPtr>& arguments
) {
  auto function = std::dynamic_pointer_cast<PyFunction>(func);
  if (function == nullptr) {
    throw std::runtime_error("Cannot build frame with non-function object");
  }
  PyFramePtr new_frame = CreateFrameWithFunction(function, arguments, frame);
  frame = new_frame;
}

void Interpreter::EvalFrame() {
  if (frame->Klass() != FrameKlass::Self()) {
    throw std::runtime_error("Cannot evaluate non-frame object");
  }
  while (!std::dynamic_pointer_cast<PyFrame>(frame)->Finished()) {
    auto frameObject = std::dynamic_pointer_cast<PyFrame>(frame);
    const auto& inst = frameObject->Instruction();
    // std::cout << "-------------------" << std::endl;
    // print(frameObject);
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
            //std::cout << "COMPARE_OP: EQUAL";
            auto result = left->eq(right);
            //print(result);
            break;
          }
          case Object::CompareOp::NOT_EQUAL: {
            frameObject->Stack().Push(left->ne(right));
            //std::cout << "COMPARE_OP: NOT_EQUAL";
            auto result = left->ne(right);
            //print(result);
            break;
          }
          case Object::CompareOp::LESS_THAN: {
            frameObject->Stack().Push(left->lt(right));
            //std::cout << "COMPARE_OP: LESS_THAN";
            auto result = left->lt(right);
            //print(result);
            break;
          }
          case Object::CompareOp::LESS_THAN_EQUAL: {
            frameObject->Stack().Push(left->le(right));
            //std::cout << "COMPARE_OP: LESS_THAN_EQUAL";
            auto result = left->le(right);
            //print(result);
            break;
          }
          case Object::CompareOp::GREATER_THAN: {
            frameObject->Stack().Push(left->gt(right));
            //std::cout << "COMPARE_OP: GREATER_THAN";
            auto result = left->gt(right);
            //print(result);
            break;
          }
          case Object::CompareOp::GREATER_THAN_EQUAL: {
            frameObject->Stack().Push(left->ge(right));
            //std::cout << "COMPARE_OP: GREATER_THAN_EQUAL";
            auto result = left->ge(right);
            //print(result);
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
          //std::cout << "POP_JUMP_IF_FALSE: true, jump next to "
                  //  << frameObject->ProgramCounter() << std::endl;
        } else {
          frameObject->SetProgramCounter(Collections::safe_add(
            frameObject->ProgramCounter(), std::get<int64_t>(inst->Operand())
          ));
          // std::cout << "POP_JUMP_IF_FALSE: false, jump to "
          //           << frameObject->ProgramCounter() << std::endl;
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
          // std::cout << "POP_JUMP_IF_TRUE: true, jump to "
          //           << frameObject->ProgramCounter() << std::endl;

        } else {
          frameObject->NextProgramCounter();
          // std::cout << "POP_JUMP_IF_TRUE: false, jump next to "
          //           << frameObject->ProgramCounter() << std::endl;
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
      case Object::ByteCode::BINARY_MULTIPLY:
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
      case Object::ByteCode::PRINT: {
        auto obj = frameObject->Stack().Pop();
        auto result = obj->repr();
        Object::PyStrPtr string =
          std::dynamic_pointer_cast<Object::PyString>(result);
        if (string == nullptr) {
          throw std::runtime_error("Cannot print object");
        }
        std::cout << Collections::ToCppString(string->Value()) << std::endl;
        frameObject->NextProgramCounter();
        break;
      }
      case Object::ByteCode::RETURN_VALUE: {
        returnValue = frameObject->Stack().Pop();
        if (frameObject->HasCaller()) {
          LeaveFrame();
        }
        break;
      }
      case Object::ByteCode::MAKE_FUNCTION: {
        auto top = frameObject->Stack().Pop();
        if (top->Klass() != Object::CodeKlass::Self()) {
          print(top);
          throw std::runtime_error("Cannot make function with non-code object");
        }
        auto code = std::dynamic_pointer_cast<Object::PyCode>(top);
        auto func = std::make_shared<PyFunction>(code, frameObject->Globals());
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
        BuildFrameWithFunction(frameObject->Stack().Pop(), arguments);
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
        auto value = frameObject->Locals()->getitem(key);
        if (value->Klass() != Object::NoneKlass::Self()) {
          found = true;
        }
        if (!found) {
          value = frameObject->Globals()->getitem(key);
          if (value->Klass() != Object::NoneKlass::Self()) {
            found = true;
          }
        }
        if (!found) {
          print(key);
          throw std::runtime_error("NameError: name is not defined");
        }
        std::cout << "LOAD_NAME: ";
        print(value);
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