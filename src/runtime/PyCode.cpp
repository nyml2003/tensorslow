#include "bytecode/ByteCode.h"
#include "collections/List.h"
#include "collections/String.h"
#include "object/Klass.h"
#include "object/PyBytes.h"
#include "runtime/PyCode.h"

#include <cstring>
#include <stdexcept>
#include <string>
#include <utility>

namespace torchlight::runtime {

using collections::Byte;
using collections::List;

PyCode::PyCode(object::PyBytesPtr byteCodes)
  : object::PyObject(CodeKlass::Self()) {
  ReadCode(std::move(byteCodes));
}

void PyCode::ReadCode(object::PyBytesPtr byteCodes) {
  auto iter = collections::List<collections::Byte>::Iterator::Begin(
    byteCodes->Value().Value()
  );
  while (!iter.End()) {
    auto byte = iter.Get();
    iter.Next();
    switch (static_cast<bytecode::ByteCode>(byte)) {
      case bytecode::ByteCode::LOAD_CONST: {
        instructions.Add(bytecode::CreateLoadConst(ReadString(iter)));
        break;
      }
      case bytecode::ByteCode::BINARY_ADD: {
        instructions.Add(bytecode::CreateBinaryAdd());
        break;
      }
      case bytecode::ByteCode::BINARY_SUBTRACT: {
        instructions.Add(bytecode::CreateBinarySubtract());
        break;
      }
      case bytecode::ByteCode::BINARY_MULTIPLY: {
        instructions.Add(bytecode::CreateBinaryMultiply());
        break;
      }
      case bytecode::ByteCode::BINARY_TRUE_DIVIDE: {
        instructions.Add(bytecode::CreateBinaryTrueDivide());
        break;
      }
      case bytecode::ByteCode::PRINT: {
        instructions.Add(bytecode::CreatePrint());
        break;
      }
      case bytecode::ByteCode::COMPARE_OP: {
        instructions.Add(bytecode::CreateCompareOp(
          static_cast<bytecode::CompareOp>(ReadU8(iter))
        ));
        break;
      }
      case bytecode::ByteCode::POP_JUMP_IF_FALSE: {
        instructions.Add(bytecode::CreatePopJumpIfFalse(ReadU32(iter)));
        break;
      }
      default:
        throw std::runtime_error(
          "Unknown byte code:" + std::to_string(static_cast<int>(iter.Get()))
        );
        break;
    }
  }
}

size_t PyCode::ReadSize(collections::List<collections::Byte>::Iterator& byteIter
) {
  size_t result = 0;
  for (size_t i = 0; i < sizeof(size_t); ++i) {
    result |= byteIter.Get() << (i * 8);
    byteIter.Next();
  }
  return result;
}

Bytes PyCode::ReadString(
  collections::List<collections::Byte>::Iterator& byteIter
) {
  size_t size = ReadSize(byteIter);
  List<Byte> result;
  for (size_t i = 0; i < size; ++i) {
    result.Add(static_cast<char>(byteIter.Get()));
    byteIter.Next();
  }
  return Bytes(result);
}

double PyCode::ReadDouble(
  collections::List<collections::Byte>::Iterator& byteIter
) {
  std::array<char, sizeof(double)> sizeBuffer{};
  for (std::size_t i = 0; i < sizeof(double); ++i) {
    sizeBuffer[i] = static_cast<char>(byteIter.Get());
    byteIter.Next();
  }
  double result = 0;
  std::memcpy(&result, sizeBuffer.data(), sizeof(double));
  return result;
}

uint32_t PyCode::ReadU32(
  collections::List<collections::Byte>::Iterator& byteIter
) {
  uint32_t result = 0;
  for (size_t i = 0; i < sizeof(uint32_t); ++i) {
    result |= byteIter.Get() << (i * 8);
    byteIter.Next();
  }
  return result;
}

uint8_t PyCode::ReadU8(collections::List<collections::Byte>::Iterator& byteIter
) {
  uint8_t result = byteIter.Get();
  byteIter.Next();
  return result;
}

bytecode::InstStream& PyCode::Instructions() {
  return instructions;
}

CodeKlass::CodeKlass() : object::Klass(collections::String("code")) {}

object::KlassPtr CodeKlass::Self() {
  static object::KlassPtr instance = std::make_shared<CodeKlass>();
  return instance;
}

}  // namespace torchlight::runtime