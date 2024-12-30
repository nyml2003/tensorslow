#include "runtime/PyFrame.h"
#include "collections/common.h"
#include "collections/impl/String.h"
#include "object/ByteCode.h"
#include "object/PyCode.h"
#include "object/PyInst.h"
#include "object/PyList.h"
#include "runtime/Serialize.h"

#include <cstring>
#include <memory>
#include <stdexcept>
#include <utility>

namespace torchlight::runtime {

using collections::Byte;
using collections::List;
using object::ByteCode;
using object::InstKlass;
using object::PyInst;

FrameKlass::FrameKlass()
  : object::Klass(collections::CreateStringWithCString("frame")) {}

object::KlassPtr FrameKlass::Self() {
  static object::KlassPtr instance = std::make_shared<FrameKlass>();
  return instance;
}

PyFrame::PyFrame(PyCodePtr code)
  : object::PyObject(FrameKlass::Self()), code(std::move(code)) {}

void PyFrame::SetProgramCounter(Index pc) {
  programCounter = pc;
}

PyCodePtr PyFrame::Code() const {
  return code;
}

Index PyFrame::ProgramCounter() const {
  return programCounter;
}

PyDictPtr PyFrame::Locals() const {
  return locals;
}

PyDictPtr PyFrame::Globals() const {
  return globals;
}

PyDictPtr PyFrame::FastLocals() const {
  return fastLocals;
}

Stack<PyObjPtr>& PyFrame::Stack() {
  return stack;
}

PyInstPtr PyFrame::Instruction() const {
  if (!code->Instructions()) {
    ParseByteCode(code);
  }
  auto insts = std::dynamic_pointer_cast<object::PyList>(code->Instructions());
  return std::dynamic_pointer_cast<PyInst>(insts->Value().Get(programCounter));
}

bool PyFrame::Finished() const {
  if (!code->Instructions()) {
    ParseByteCode(code);
  }
  auto size = code->Instructions()->Value().Size();
  return programCounter >= size;
}

void PyFrame::NextProgramCounter() {
  programCounter++;
}

void ParseByteCode(const PyCodePtr& code) {
  auto iter = List<Byte>::Iterator::Begin(code->ByteCode()->Value().Value());

  auto byte = iter.Get();
  if (static_cast<object::Literal>(byte) != object::Literal::LIST) {
    throw std::runtime_error("Invalid byte code");
  }
  iter.Next();
  Index size = ReadU64(iter);
  auto insts = List<PyObjPtr>(size);
  while (size--) {
    auto byte = iter.Get();
    iter.Next();
    switch (static_cast<ByteCode>(byte)) {
      case ByteCode::LOAD_CONST: {
        insts.Add(object::CreateLoadConst(ReadU64(iter)));
        break;
      }
      case ByteCode::BINARY_ADD: {
        insts.Add(object::CreateBinaryAdd());
        break;
      }
      case ByteCode::PRINT: {
        insts.Add(object::CreatePrint());
        break;
      }
      default:
        throw std::runtime_error(
          "Unknown byte code:" + std::to_string(static_cast<int>(iter.Get()))
        );
        break;
    }
  }
  code->SetInstructions(std::make_shared<object::PyList>(insts));
}
}  // namespace torchlight::runtime
