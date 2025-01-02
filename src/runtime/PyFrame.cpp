#include "runtime/PyFrame.h"
#include "collections/Stack.h"
#include "collections/common.h"
#include "collections/impl/String.h"
#include "object/ByteCode.h"
#include "object/PyCode.h"
#include "object/PyDictionary.h"
#include "object/PyInst.h"
#include "object/PyList.h"
#include "object/PyNone.h"
#include "runtime/Serialize.h"

#include <cstring>
#include <memory>
#include <stdexcept>
#include <utility>

namespace torchlight::runtime {

using collections::Byte;
using collections::Index;
using collections::List;
using collections::Stack;
using object::ByteCode;
using object::PyCodePtr;
using object::PyDictPtr;
using object::PyInst;
using object::PyInstPtr;
using object::PyList;
using object::PyListPtr;
using object::PyObjPtr;
using object::PyStrPtr;

FrameKlass::FrameKlass()
  : object::Klass(collections::CreateStringWithCString("frame")) {}

object::KlassPtr FrameKlass::Self() {
  static object::KlassPtr instance = std::make_shared<FrameKlass>();
  return instance;
}

PyFrame::PyFrame(PyCodePtr code)
  : object::PyObject(FrameKlass::Self()),
    code(std::move(code)),
    locals(std::make_shared<object::PyDictionary>()),
    globals(locals) {
  List<PyObjPtr> fastLocalsList(this->code->NLocals());
  fastLocalsList.Fill(object::PyNone::Instance());
  fastLocals = std::make_shared<object::PyList>(List<PyObjPtr>(fastLocalsList));
  caller = object::PyNone::Instance();
}

PyFrame::PyFrame(
  const PyFunctionPtr& function,
  const List<PyObjPtr>& arguments,
  PyObjPtr caller
)
  : object::PyObject(FrameKlass::Self()),
    code(function->Code()),
    globals(function->Globals()),
    caller(std::move(caller)) {
  code = function->Code();
  locals = std::make_shared<object::PyDictionary>();
  List<PyObjPtr> fastLocalsList(arguments.Size());
  for (auto it = List<PyObjPtr>::Iterator::Begin(arguments); !it.End();
       it.Next()) {
    fastLocalsList.Add(it.Get());
  }
  fastLocals = std::make_shared<object::PyList>(fastLocalsList);
}

void PyFrame::SetProgramCounter(Index pc) {
  programCounter = pc;
}

PyCodePtr PyFrame::Code() const {
  return code;
}

Index PyFrame::ProgramCounter() const {
  return programCounter;
}

PyDictPtr& PyFrame::Locals() {
  return locals;
}

PyDictPtr& PyFrame::Globals() {
  return globals;
}

PyListPtr& PyFrame::FastLocals() {
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
  if (static_cast<object::Literal>(iter.Get()) != object::Literal::LIST) {
    throw std::runtime_error("Invalid insts");
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
      case ByteCode::STORE_FAST: {
        insts.Add(object::CreateStoreFast(ReadU64(iter)));
        break;
      }
      case ByteCode::LOAD_FAST: {
        insts.Add(object::CreateLoadFast(ReadU64(iter)));
        break;
      }
      case ByteCode::COMPARE_OP: {
        insts.Add(
          object::CreateCompareOp(static_cast<object::CompareOp>(ReadU8(iter)))
        );
        break;
      }
      case ByteCode::POP_JUMP_IF_FALSE: {
        insts.Add(object::CreatePopJumpIfFalse(ReadI64(iter)));
        break;
      }
      case ByteCode::POP_JUMP_IF_TRUE: {
        insts.Add(object::CreatePopJumpIfTrue(ReadI64(iter)));
        break;
      }
      case ByteCode::MAKE_FUNCTION: {
        insts.Add(object::CreateMakeFunction());
        break;
      }
      case ByteCode::CALL_FUNCTION: {
        insts.Add(object::CreateCallFunction(ReadU64(iter)));
        break;
      }
      case ByteCode::RETURN_VALUE: {
        insts.Add(object::CreateReturnValue());
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

PyObjPtr PyFrame::Caller() const {
  return caller;
}

bool PyFrame::HasCaller() const {
  return caller != object::PyNone::Instance();
}
}  // namespace torchlight::runtime
