
#include "runtime/Interpreter.h"
#include "collections/impl/Bytes.h"
#include "object/ByteCode.h"
#include "object/PyBoolean.h"
#include "object/PyList.h"
#include "object/PyString.h"

#include <iostream>
#include <stdexcept>
namespace torchlight::runtime {

using collections::ToBytes;
using collections::ToCString;
using object::BooleanKlass;
using object::ByteCode;
using object::CompareOp;

Interpreter::Interpreter(PyFramePtr frame) : frame(std::move(frame)) {}

void Interpreter::Run() {
  while (!frame->Finished()) {
    const auto& inst = frame->Instruction();
    switch (inst->Code()) {
      case ByteCode::LOAD_CONST: {
        auto key = std::get<Index>(inst->Operand());
        auto consts = frame->Code()->Consts();
        auto const_list =
          std::dynamic_pointer_cast<object::PyList>(consts)->Value();
        auto value = const_list.Get(key);
        frame->Stack().Push(value);
        frame->NextProgramCounter();
        break;
      }
      case ByteCode::COMPARE_OP: {
        auto op = std::get<CompareOp>(inst->Operand());
        auto right = frame->Stack().Pop();
        auto left = frame->Stack().Pop();
        switch (op) {
          case CompareOp::EQUAL:
            frame->Stack().Push(left->eq(right));
            break;
          case CompareOp::NOT_EQUAL:
            frame->Stack().Push(left->ne(right));
            break;
          case CompareOp::LESS_THAN:
            frame->Stack().Push(left->lt(right));
            break;
          case CompareOp::LESS_THAN_EQUAL:
            frame->Stack().Push(left->le(right));
            break;
          case CompareOp::GREATER_THAN:
            frame->Stack().Push(left->gt(right));
            break;
          case CompareOp::GREATER_THAN_EQUAL:
            frame->Stack().Push(left->ge(right));
            break;
          default:
            throw std::runtime_error("Unknown compare operation");
        }
        frame->NextProgramCounter();
        break;
      }
      case ByteCode::POP_JUMP_IF_FALSE: {
        auto needJump = frame->Stack().Pop();
        if (!(needJump->Klass() == BooleanKlass::Self())) {
          throw std::runtime_error("Cannot jump if not boolean");
        }
        auto bool_needJump =
          std::dynamic_pointer_cast<object::PyBoolean>(needJump);
        if (bool_needJump == nullptr) {
          throw std::runtime_error("Cannot jump if not boolean");
        }
        if (bool_needJump->Value()) {
          frame->SetProgramCounter(
            frame->ProgramCounter() + std::get<Index>(inst->Operand()) + 1
          );
        } else {
          frame->NextProgramCounter();
        }
        break;
      }
      case ByteCode::BINARY_ADD: {
        auto right = frame->Stack().Pop();
        auto left = frame->Stack().Pop();
        frame->Stack().Push(left->add(right));
        frame->NextProgramCounter();
        break;
      }
      case ByteCode::BINARY_SUBTRACT:
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
      case ByteCode::PRINT: {
        auto obj = frame->Stack().Pop();
        auto result = obj->repr();
        object::PyStrPtr string =
          std::dynamic_pointer_cast<object::PyString>(result);
        if (string == nullptr) {
          throw std::runtime_error("Cannot print object");
        }
        std::cout << ToCString(ToBytes(string->Value())).get() << std::endl;
        frame->NextProgramCounter();
        break;
      }
      case ByteCode::RETURN_VALUE: {
      }
      case ByteCode::ERROR: {
        throw std::runtime_error("Unknown byte code");
        break;
      }
    }
  }
}
}  // namespace torchlight::runtime