#include "runtime/PyFrame.h"

#include "bytecode/ByteCode.h"
#include "collections/Integer.h"
#include "collections/String.h"
#include "collections/common.h"
#include "object/PyFloat.h"
#include "object/PyInteger.h"
#include "object/PyString.h"
#include "object/common.h"

#include <array>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <memory>
#include <string>
#include <utility>

namespace torchlight::runtime {

FrameKlass::FrameKlass() : object::Klass(collections::String("frame")) {}

object::KlassPtr FrameKlass::Self() {
  static object::KlassPtr instance = std::make_shared<FrameKlass>();
  return instance;
}

PyFrame::PyFrame(PyCodePtr code)
  : object::PyObject(FrameKlass::Self()), code(std::move(code)) {}

size_t PyFrame::ReadSize(
  collections::List<collections::Byte>::Iterator& byteIter
) {
  size_t result = 0;
  for (size_t i = 0; i < sizeof(size_t); ++i) {
    result |= byteIter.Get() << (i * 8);
    byteIter.Next();
  }
  return result;
}

collections::String PyFrame::ReadString(
  collections::List<collections::Byte>::Iterator& byteIter
) {
  size_t size = ReadSize(byteIter);
  std::string result;
  for (size_t i = 0; i < size; ++i) {
    result.push_back(static_cast<char>(byteIter.Get()));
    byteIter.Next();
  }
  return collections::String(result.c_str());
}

collections::Integer PyFrame::ReadInt(
  collections::List<collections::Byte>::Iterator& byteIter
) {
  collections::String str = ReadString(byteIter);
  return collections::Integer(str);
}

double PyFrame::ReadDouble(
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

void PyFrame::Run() {
  collections::List<collections::Byte>::Iterator iter(
    collections::List<collections::Byte>::Iterator::Begin(
      this->code->ByteCodes()->Value().Value()
    )
  );
  while (!iter.End()) {
    auto byte = iter.Get();
    iter.Next();
    switch (static_cast<bytecode::ByteCode>(byte)) {
      case bytecode::ByteCode::StoreInt: {
        collections::Integer value = ReadInt(iter);
        stack.Push(std::make_shared<object::PyInteger>(value));
        break;
      }
      case bytecode::ByteCode::StoreDouble: {
        double value = ReadDouble(iter);
        stack.Push(std::make_shared<object::PyFloat>(value));
        break;
      }
      case bytecode::ByteCode::OperatorAdd: {
        auto left = stack.Pop();
        auto right = stack.Pop();
        stack.Push(left->add(right));
        break;
      }
      case bytecode::ByteCode::OperatorSub: {
        auto left = stack.Pop();
        auto right = stack.Pop();
        stack.Push(left->sub(right));
        break;
      }
      case bytecode::ByteCode::OperatorMul: {
        auto left = stack.Pop();
        auto right = stack.Pop();
        stack.Push(left->mul(right));
        break;
      }
      case bytecode::ByteCode::OperatorDiv: {
        auto left = stack.Pop();
        auto right = stack.Pop();
        stack.Push(left->div(right));
        break;
      }
      case bytecode::ByteCode::Print: {
        auto obj = stack.Pop();
        auto result = obj->repr();
        object::PyStrPtr string =
          std::dynamic_pointer_cast<object::PyString>(result);
        if (string == nullptr) {
          throw std::runtime_error("Cannot print object");
        }
        std::cout << string->Value().ToUTF8() << std::endl;
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

}  // namespace torchlight::runtime
