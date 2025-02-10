#include "Runtime/PyFrame.h"
#include "ByteCode/ByteCode.h"
#include "ByteCode/PyCode.h"
#include "ByteCode/PyInst.h"
#include "Collections/IntegerHelper.h"
#include "Collections/Stack.h"
#include "Collections/StringHelper.h"
#include "Object/Common.h"
#include "Object/PyDictionary.h"
#include "Object/PyInteger.h"
#include "Object/PyList.h"
#include "Object/PyNone.h"
#include "Object/PyString.h"
#include "Object/PyType.h"
#include "Runtime/Serialize.h"

#include <cstring>
#include <memory>
#include <stdexcept>
#include <utility>

namespace torchlight::Runtime {

FrameKlass::FrameKlass() = default;

void FrameKlass::Initialize() {
  SetType(Object::CreatePyType(Self()));
  SetName(Object::CreatePyString("frame"));
  SetAttributes(Object::CreatePyDict());
}

Object::KlassPtr FrameKlass::Self() {
  static Object::KlassPtr instance = std::make_shared<FrameKlass>();
  return instance;
}

PyFrame::PyFrame(
  Object::PyCodePtr _code,
  Object::PyObjPtr _locals,      // 传入的是 PyObjPtr
  Object::PyObjPtr _globals,     // 传入的是 PyObjPtr
  Object::PyObjPtr _fastLocals,  // 传入的是 PyObjPtr
  Object::PyObjPtr _caller
)
  : Object::PyObject(FrameKlass::Self()),
    stack(),
    programCounter(0),
    code(std::move(_code)),
    locals(std::dynamic_pointer_cast<Object::PyDictionary>(_locals)
    ),  // 转换为 PyDictPtr
    globals(std::dynamic_pointer_cast<Object::PyDictionary>(_globals)
    ),  // 转换为 PyDictPtr
    fastLocals(std::dynamic_pointer_cast<Object::PyList>(_fastLocals)
    ),  // 转换为 PyListPtr
    caller(std::move(_caller)) {}

PyFramePtr CreateFrameWithCode(const Object::PyCodePtr& code) {
  auto locals = Object::CreatePyDict();
  auto globals = locals;
  auto fastLocals = Object::CreatePyList(code->NLocals());
  return std::make_shared<PyFrame>(
    code, locals, globals, fastLocals, Object::PyNone::Instance()
  );
}

PyFramePtr CreateFrameWithFunction(
  const Object::PyObjPtr& _function,
  const Object::PyObjPtr& _arguments,
  Object::PyObjPtr caller
) {
  if (_function->Klass() != Object::FunctionKlass::Self()) {
    throw std::runtime_error("Cannot create frame with non-function object");
  }
  auto function = std::dynamic_pointer_cast<Object::PyFunction>(_function);
  if (_arguments->Klass() != Object::ListKlass::Self()) {
    throw std::runtime_error("Cannot create frame with non-list object");
  }
  auto arguments = std::dynamic_pointer_cast<Object::PyList>(_arguments);
  auto code = function->Code();
  auto globals = function->Globals();
  auto locals = Object::CreatePyDict();
  Index nLocals = code->NLocals();
  Index argumentsSize = Object::ToU64(arguments->len());
  Collections::List<Object::PyObjPtr> fastLocalsList =
    arguments->Value().Copy();
  auto fastLocals =
    Object::CreatePyList(fastLocalsList, std::max(nLocals, argumentsSize));
  return std::make_shared<PyFrame>(
    code, locals, globals, fastLocals, std::move(caller)
  );
}

void PyFrame::SetProgramCounter(Index pc) {
  programCounter = pc;
}

Object::PyCodePtr PyFrame::Code() const {
  return code;
}

Index PyFrame::ProgramCounter() const {
  return programCounter;
}

Object::PyDictPtr& PyFrame::Locals() {
  return locals;
}

Object::PyDictPtr& PyFrame::Globals() {
  return globals;
}

Object::PyListPtr& PyFrame::FastLocals() {
  return fastLocals;
}

Collections::Stack<Object::PyObjPtr>& PyFrame::Stack() {
  return stack;
}

Object::PyInstPtr PyFrame::Instruction() const {
  if (!code->Instructions()) {
    ParseByteCode(code);
  }
  auto insts = std::dynamic_pointer_cast<Object::PyList>(code->Instructions());
  return std::dynamic_pointer_cast<Object::PyInst>(
    insts->Value().Get(programCounter)
  );
}

bool PyFrame::Finished() const {
  if (!isParsed) {
    ParseByteCode(code);
  }
  auto size = code->Instructions()->Value().Size();
  return programCounter >= size;
}

void PyFrame::NextProgramCounter() {
  programCounter++;
}

void ParseByteCode(const Object::PyCodePtr& code) {
  auto bytes = code->ByteCode()->Value().Value();
  auto iter = Collections::Iterator<Byte>::Begin(bytes);
  if (static_cast<Object::Literal>(iter.Get()) != Object::Literal::LIST) {
    throw std::runtime_error("Invalid insts");
  }
  iter.Next();
  Index size = ReadU64(iter);
  auto insts = Collections::List<Object::PyObjPtr>(size);
  while (size--) {
    auto byte = iter.Get();
    iter.Next();
    switch (static_cast<Object::ByteCode>(byte)) {
      case Object::ByteCode::LOAD_CONST: {
        insts.Push(Object::CreateLoadConst(ReadU64(iter)));
        break;
      }
      case Object::ByteCode::BINARY_ADD: {
        insts.Push(Object::CreateBinaryAdd());
        break;
      }
      case Object::ByteCode::BINARY_MULTIPLY: {
        insts.Push(Object::CreateBinaryMultiply());
        break;
      }
      case Object::ByteCode::BINARY_SUBTRACT: {
        insts.Push(Object::CreateBinarySubtract());
        break;
      }
      case Object::ByteCode::STORE_FAST: {
        insts.Push(Object::CreateStoreFast(ReadU64(iter)));
        break;
      }
      case Object::ByteCode::LOAD_FAST: {
        insts.Push(Object::CreateLoadFast(ReadU64(iter)));
        break;
      }
      case Object::ByteCode::COMPARE_OP: {
        insts.Push(
          Object::CreateCompareOp(static_cast<Object::CompareOp>(ReadU8(iter)))
        );
        break;
      }
      case Object::ByteCode::POP_JUMP_IF_FALSE: {
        insts.Push(Object::CreatePopJumpIfFalse(ReadI64(iter)));
        break;
      }
      case Object::ByteCode::POP_JUMP_IF_TRUE: {
        insts.Push(Object::CreatePopJumpIfTrue(ReadI64(iter)));
        break;
      }
      case Object::ByteCode::MAKE_FUNCTION: {
        insts.Push(Object::CreateMakeFunction());
        break;
      }
      case Object::ByteCode::CALL_FUNCTION: {
        insts.Push(Object::CreateCallFunction(ReadU64(iter)));
        break;
      }
      case Object::ByteCode::RETURN_VALUE: {
        insts.Push(Object::CreateReturnValue());
        break;
      }
      case Object::ByteCode::LOAD_NAME: {
        insts.Push(Object::CreateLoadName(ReadU64(iter)));
        break;
      }
      case Object::ByteCode::STORE_NAME: {
        insts.Push(Object::CreateStoreName(ReadU64(iter)));
        break;
      }
      case Object::ByteCode::LOAD_GLOBAL: {
        insts.Push(Object::CreateLoadGlobal(ReadU64(iter)));
        break;
      }
      case Object::ByteCode::POP_TOP: {
        insts.Push(Object::CreatePopTop());
        break;
      }
      case Object::ByteCode::LOAD_ATTR: {
        insts.Push(Object::CreateLoadAttr(ReadU64(iter)));
        break;
      }
      case Object::ByteCode::BUILD_LIST: {
        insts.Push(Object::CreateBuildList(ReadU64(iter)));
        break;
      }
      case Object::ByteCode::BINARY_MATRIX_MULTIPLY: {
        insts.Push(Object::CreateBinaryMatrixMultiply());
        break;
      }
      case Object::ByteCode::JUMP_ABSOLUTE: {
        insts.Push(Object::CreateJumpAbsolute(ReadU64(iter)));
        break;
      }
      case Object::ByteCode::BINARY_SUBSCR: {
        insts.Push(Object::CreateBinarySubscr());
        break;
      }
      case Object::ByteCode::STORE_SUBSCR: {
        insts.Push(Object::CreateStoreSubscr());
        break;
      }
      default:
        throw std::runtime_error(
          "Unknown byte code:" + std::to_string(static_cast<int>(iter.Get()))
        );
        break;
    }
  }
  code->SetInstructions(std::make_shared<Object::PyList>(insts));
}

Object::PyObjPtr FrameKlass::repr(Object::PyObjPtr obj) {
  if (obj->Klass() != FrameKlass::Self()) {
    throw std::runtime_error("Cannot repr non-frame object");
  }
  auto frame = std::dynamic_pointer_cast<PyFrame>(obj);
  auto code = frame->Code();
  auto name = code->Name();
  Object::PyObjPtr repr =
    Object::CreatePyString(Collections::CreateStringWithCString("<frame>"));
  repr = repr->add(Object::CreatePyString(
    Collections::CreateStringWithCString("\nprogramCounter: ")
  ));
  repr = repr->add(Object::CreatePyInteger(
                     Collections::CreateIntegerWithU64(frame->ProgramCounter())
  )
                     ->repr());
  repr = repr->add(Object::CreatePyString(
    Collections::CreateStringWithCString("\n\ninstruction:\n")
  ));
  repr = repr->add(frame->Instruction()->repr());
  repr = repr->add(
    Object::CreatePyString(Collections::CreateStringWithCString("\n\nstack:\n"))
  );
  auto stack = frame->Stack().GetContent();
  for (auto it = Collections::Iterator<Object::PyObjPtr>::Begin(stack);
       !it.End(); it.Next()) {
    repr =
      repr
        ->add(Object::CreatePyInteger(
                Collections::CreateIntegerWithU64(it.GetCurrentIndex())
        )
                ->repr())
        ->add(Object::CreatePyString(Collections::CreateStringWithCString((":"))
        ))
        ->add(it.Get()->repr())
        ->add(Object::CreatePyString(Collections::CreateStringWithCString("\n"))
        );
  }
  repr = repr->add(
    Object::CreatePyString(Collections::CreateStringWithCString("\nlocals:\n"))
  );
  repr = repr->add(frame->Locals()->repr());
  repr = repr->add(Object::CreatePyString(
    Collections::CreateStringWithCString("\n\nglobals:\n")
  ));
  repr = repr->add(frame->Globals()->repr());

  repr = repr->add(Object::CreatePyString(
    Collections::CreateStringWithCString("\n\nfastLocals:\n")
  ));
  repr = repr->add(frame->FastLocals()->repr());
  repr = repr->add(Object::CreatePyString(
    Collections::CreateStringWithCString("\n\ncaller:\n")
  ));
  repr = repr->add(frame->Caller()->repr());
  repr = repr->add(
    Object::CreatePyString(Collections::CreateStringWithCString("\n\ncode:\n"))
  );
  repr = repr->add(code->repr());
  repr = repr->add(
    Object::CreatePyString(Collections::CreateStringWithCString("</frame>\n"))
  );
  return repr;
}

Object::PyObjPtr PyFrame::Caller() const {
  return caller;
}

bool PyFrame::HasCaller() const {
  return caller != Object::CreatePyNone();
}
}  // namespace torchlight::Runtime
