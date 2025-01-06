
#include "runtime/Interpreter.h"
#include "collections/impl/Bytes.h"
#include "collections/impl/Integer.h"
#include "object/ByteCode.h"
#include "object/PyBoolean.h"

#include "object/PyCode.h"
#include "object/PyList.h"
#include "object/PyNone.h"
#include "object/PyString.h"
#include "runtime/PyFrame.h"
#include "runtime/PyFunction.h"

#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
namespace torchlight::runtime {

using collections::Index;
using collections::List;
using collections::ToBytes;
using collections::ToCString;
using object::BooleanKlass;
using object::ByteCode;
using object::CompareOp;
using object::PyList;
using object::PyListPtr;
using object::PyObjPtr;
using object::PyString;
using object::PyStrPtr;

Interpreter::Interpreter() {
  frame = object::PyNone::Instance();
}

void Interpreter::Run(const object::PyCodePtr& code) {
  frame = CreateFrameWithCode(code);
  EvalFrame();
  DestroyFrame();
}

void Interpreter::BuildFrameWithFunction(
  const PyObjPtr& func,
  const List<PyObjPtr>& arguments
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
    switch (inst->Code()) {
      case ByteCode::LOAD_CONST: {
        auto key = std::get<Index>(inst->Operand());
        auto consts = frameObject->Code()->Consts();
        auto const_list =
          std::dynamic_pointer_cast<object::PyList>(consts)->Value();
        auto value = const_list.Get(key);
        std::cout << "LOAD_CONST ";
        print(value);
        frameObject->Stack().Push(value);
        frameObject->NextProgramCounter();
        break;
      }
      case ByteCode::STORE_FAST: {
        auto index = std::get<Index>(inst->Operand());
        auto value = frameObject->Stack().Pop();
        frameObject->FastLocals()->Value().Set(index, value);
        frameObject->NextProgramCounter();
        break;
      }
      case ByteCode::COMPARE_OP: {
        auto op = std::get<CompareOp>(inst->Operand());
        auto right = frameObject->Stack().Pop();
        auto left = frameObject->Stack().Pop();
        switch (op) {
          case CompareOp::EQUAL: {
            frameObject->Stack().Push(left->eq(right));
            std::cout << "COMPARE_OP: EQUAL";
            auto result = left->eq(right);
            print(result);
            break;
          }
          case CompareOp::NOT_EQUAL: {
            frameObject->Stack().Push(left->ne(right));
            std::cout << "COMPARE_OP: NOT_EQUAL";
            auto result = left->ne(right);
            print(result);
            break;
          }
          case CompareOp::LESS_THAN: {
            frameObject->Stack().Push(left->lt(right));
            std::cout << "COMPARE_OP: LESS_THAN";
            auto result = left->lt(right);
            print(result);
            break;
          }
          case CompareOp::LESS_THAN_EQUAL: {
            frameObject->Stack().Push(left->le(right));
            std::cout << "COMPARE_OP: LESS_THAN_EQUAL";
            auto result = left->le(right);
            print(result);
            break;
          }
          case CompareOp::GREATER_THAN: {
            frameObject->Stack().Push(left->gt(right));
            std::cout << "COMPARE_OP: GREATER_THAN";
            auto result = left->gt(right);
            print(result);
            break;
          }
          case CompareOp::GREATER_THAN_EQUAL: {
            frameObject->Stack().Push(left->ge(right));
            std::cout << "COMPARE_OP: GREATER_THAN_EQUAL";
            auto result = left->ge(right);
            print(result);
            break;
          }
          default:
            throw std::runtime_error("Unknown compare operation");
        }
        frameObject->NextProgramCounter();
        break;
      }
      case ByteCode::POP_JUMP_IF_FALSE: {
        auto needJump = frameObject->Stack().Pop();
        if (!(needJump->Klass() == BooleanKlass::Self())) {
          throw std::runtime_error("Cannot jump if not boolean");
        }
        auto bool_needJump =
          std::dynamic_pointer_cast<object::PyBoolean>(needJump);
        if (bool_needJump == nullptr) {
          throw std::runtime_error("Cannot jump if not boolean");
        }
        if (bool_needJump->Value()) {
          frameObject->NextProgramCounter();
          std::cout << "POP_JUMP_IF_FALSE: true, jump next to "
                    << frameObject->ProgramCounter() << std::endl;
        } else {
          frameObject->SetProgramCounter(collections::safe_add(
            frameObject->ProgramCounter(), std::get<int64_t>(inst->Operand())
          ));
          std::cout << "POP_JUMP_IF_FALSE: false, jump to "
                    << frameObject->ProgramCounter() << std::endl;
        }

        break;
      }
      case ByteCode::POP_JUMP_IF_TRUE: {
        auto needJump = frameObject->Stack().Pop();
        if (!(needJump->Klass() == BooleanKlass::Self())) {
          throw std::runtime_error("Cannot jump if not boolean");
        }
        auto bool_needJump =
          std::dynamic_pointer_cast<object::PyBoolean>(needJump);
        if (bool_needJump == nullptr) {
          throw std::runtime_error("Cannot jump if not boolean");
        }
        if (bool_needJump->Value()) {
          frameObject->SetProgramCounter(collections::safe_add(
            frameObject->ProgramCounter(), std::get<int64_t>(inst->Operand())
          ));
          std::cout << "POP_JUMP_IF_TRUE: true, jump to "
                    << frameObject->ProgramCounter() << std::endl;

        } else {
          frameObject->NextProgramCounter();
          std::cout << "POP_JUMP_IF_TRUE: false, jump next to "
                    << frameObject->ProgramCounter() << std::endl;
        }
        break;
      }
      case ByteCode::BINARY_ADD: {
        auto right = frameObject->Stack().Pop();
        auto left = frameObject->Stack().Pop();
        frameObject->Stack().Push(left->add(right));
        frameObject->NextProgramCounter();
        break;
      }
      case ByteCode::BINARY_SUBTRACT: {
        auto right = frameObject->Stack().Pop();
        auto left = frameObject->Stack().Pop();
        frameObject->Stack().Push(left->sub(right));
        frameObject->NextProgramCounter();
        break;
      }
      case ByteCode::BINARY_MULTIPLY:
      case ByteCode::BINARY_TRUE_DIVIDE:
      case ByteCode::BINARY_FLOOR_DIVIDE:
      case ByteCode::BINARY_XOR:
      case ByteCode::BINARY_AND:
      case ByteCode::BINARY_OR:
      case ByteCode::BINARY_POWER:
      case ByteCode::BINARY_MODULO:
      case ByteCode::BINARY_LSHIFT:
      case ByteCode::BINARY_RSHIFT:
        break;
      case ByteCode::PRINT: {
        auto obj = frameObject->Stack().Pop();
        auto result = obj->repr();
        object::PyStrPtr string =
          std::dynamic_pointer_cast<object::PyString>(result);
        if (string == nullptr) {
          throw std::runtime_error("Cannot print object");
        }
        std::cout << ToCString(ToBytes(string->Value())).get() << std::endl;
        frameObject->NextProgramCounter();
        break;
      }
      case ByteCode::RETURN_VALUE: {
        returnValue = frameObject->Stack().Pop();
        if (frameObject->HasCaller()) {
          LeaveFrame();
        }
        break;
      }
      case ByteCode::MAKE_FUNCTION: {
        auto top = frameObject->Stack().Pop();
        if (top->Klass() != object::CodeKlass::Self()) {
          print(top);
          throw std::runtime_error("Cannot make function with non-code object");
        }
        auto code = std::dynamic_pointer_cast<object::PyCode>(top);
        auto func = std::make_shared<PyFunction>(code, frameObject->Globals());
        frameObject->Stack().Push(func);
        frameObject->NextProgramCounter();
        break;
      }
      case ByteCode::LOAD_FAST: {
        auto index = std::get<Index>(inst->Operand());
        auto value = frameObject->FastLocals()->Value().Get(index);
        frameObject->Stack().Push(value);
        frameObject->NextProgramCounter();
        break;
      }
      case ByteCode::CALL_FUNCTION: {
        auto argumentCount = std::get<Index>(inst->Operand());
        List<PyObjPtr> arguments(argumentCount);
        for (Index i = 0; i < argumentCount; i++) {
          arguments.Add(frameObject->Stack().Pop());
        }
        BuildFrameWithFunction(frameObject->Stack().Pop(), arguments);
        frameObject->NextProgramCounter();
        break;
      }
      case ByteCode::LOAD_GLOBAL: {
        auto index = std::get<Index>(inst->Operand());
        auto key = frameObject->Code()->Names()->Value().Get(index);
        auto value = frameObject->Globals()->getitem(key);
        frameObject->Stack().Push(value);
        frameObject->NextProgramCounter();
        break;
      }
      case ByteCode::STORE_NAME: {
        auto index = std::get<Index>(inst->Operand());
        auto key = frameObject->Code()->Names()->Value().Get(index);
        auto value = frameObject->Stack().Pop();
        frameObject->Globals()->setitem(key, value);
        frameObject->NextProgramCounter();
        break;
      }
      case ByteCode::LOAD_NAME: {
        auto index = std::get<Index>(inst->Operand());
        auto key = frameObject->Code()->Names()->Value().Get(index);
        // LEGB rule
        // local -> enclosing -> global -> built-in
        bool found = false;
        auto value = frameObject->Locals()->getitem(key);
        if (value->Klass() != object::NoneKlass::Self()) {
          found = true;
        }
        if (!found) {
          value = frameObject->Globals()->getitem(key);
          if (value->Klass() != object::NoneKlass::Self()) {
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
      case ByteCode::ERROR: {
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

}  // namespace torchlight::runtime