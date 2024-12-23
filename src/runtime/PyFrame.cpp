#include "runtime/PyFrame.h"

#include "bytecode/ByteCode.h"
#include "collections/Bytes.h"
#include "collections/Integer.h"
#include "collections/String.h"
#include "object/PyBoolean.h"
#include "object/PyInteger.h"
#include "object/PyString.h"

#include <cstring>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <utility>

namespace torchlight::runtime {

using collections::Bytes;
using collections::Integer;
using object::BooleanKlass;

FrameKlass::FrameKlass() : object::Klass(collections::String("frame")) {}

object::KlassPtr FrameKlass::Self() {
  static object::KlassPtr instance = std::make_shared<FrameKlass>();
  return instance;
}

PyFrame::PyFrame(PyCodePtr code)
  : object::PyObject(FrameKlass::Self()), code(std::move(code)) {}

void PyFrame::Run() {
  auto& instructions = code->Instructions();
  programCounter = 0;
  while (programCounter < instructions.Size()) {
    const auto& inst = instructions.Get(programCounter);
    switch (inst->code) {
      case bytecode::ByteCode::LOAD_CONST: {
        Bytes value = std::get<Bytes>(inst->operand);
        stack.Push(std::make_shared<object::PyInteger>(Integer(value)));
        programCounter++;
        break;
      }
      case bytecode::ByteCode::COMPARE_OP: {
        auto op = std::get<bytecode::CompareOp>(inst->operand);
        auto right = stack.Pop();
        auto left = stack.Pop();
        switch (op) {
          case bytecode::CompareOp::EQUAL:
            stack.Push(left->eq(right));
            break;
          case bytecode::CompareOp::NOT_EQUAL:
            stack.Push(left->ne(right));
            break;
          case bytecode::CompareOp::LESS_THAN:
            stack.Push(left->lt(right));
            break;
          case bytecode::CompareOp::LESS_THAN_EQUAL:
            stack.Push(left->le(right));
            break;
          case bytecode::CompareOp::GREATER_THAN:
            stack.Push(left->gt(right));
            break;
          case bytecode::CompareOp::GREATER_THAN_EQUAL:
            stack.Push(left->ge(right));
            break;
          default:
            throw std::runtime_error("Unknown compare operation");
        }
        programCounter++;
        break;
      }
      case bytecode::ByteCode::POP_JUMP_IF_FALSE: {
        auto needJump = stack.Pop();
        if (!(needJump->Klass() == BooleanKlass::Self())) {
          throw std::runtime_error("Cannot jump if not boolean");
        }
        auto bool_needJump =
          std::dynamic_pointer_cast<object::PyBoolean>(needJump);
        if (bool_needJump == nullptr) {
          throw std::runtime_error("Cannot jump if not boolean");
        }
        if (bool_needJump->Value()) {
          programCounter += std::get<uint32_t>(inst->operand) + 1;
        } else {
          programCounter++;
        }
        break;
      }
      case bytecode::ByteCode::BINARY_ADD: {
        auto right = stack.Pop();
        auto left = stack.Pop();
        stack.Push(left->add(right));
        programCounter++;
        break;
      }
      case bytecode::ByteCode::BINARY_SUBTRACT:
      case bytecode::ByteCode::BINARY_MULTIPLY:
      case bytecode::ByteCode::BINARY_TRUE_DIVIDE:
      case bytecode::ByteCode::BINARY_FLOOR_DIVIDE:
      case bytecode::ByteCode::BINARY_XOR:
      case bytecode::ByteCode::BINARY_AND:
      case bytecode::ByteCode::BINARY_OR:
      case bytecode::ByteCode::BINARY_POWER:
      case bytecode::ByteCode::BINARY_MODULO:
      case bytecode::ByteCode::BINARY_LSHIFT:
      case bytecode::ByteCode::BINARY_RSHIFT:
      case bytecode::ByteCode::PRINT: {
        auto obj = stack.Pop();
        auto result = obj->repr();
        object::PyStrPtr string =
          std::dynamic_pointer_cast<object::PyString>(result);
        if (string == nullptr) {
          throw std::runtime_error("Cannot print object");
        }
        std::cout << string->Value().ToUTF8() << std::endl;
        programCounter++;
        break;
      }
      case bytecode::ByteCode::ERROR: {
        throw std::runtime_error("Unknown byte code");
        break;
      }
    }
  }
}

}  // namespace torchlight::runtime
