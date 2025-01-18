#include "Collections/IntegerHelper.h"
#include "Collections/Stack.h"
#include "Collections/StringHelper.h"
#include "Object/ByteCode.h"
#include "Object/Common.h"
#include "Object/PyCode.h"
#include "Object/PyDictionary.h"
#include "Object/PyInst.h"
#include "Object/PyInteger.h"
#include "Object/PyList.h"
#include "Object/PyNone.h"
#include "Object/PyString.h"
#include "Runtime/PyFrame.h"
#include "Runtime/Serialize.h"

#include <cstring>
#include <memory>
#include <stdexcept>
#include <utility>

namespace torchlight::Runtime {

FrameKlass::FrameKlass()
  : Object::Klass(Collections::CreateStringWithCString("frame")) {}

Object::KlassPtr FrameKlass::Self() {
  static Object::KlassPtr instance = std::make_shared<FrameKlass>();
  return instance;
}

PyFrame::PyFrame(
  Object::PyCodePtr code,
  Object::PyDictPtr locals,
  Object::PyDictPtr globals,
  Object::PyListPtr fastLocals,
  Object::PyObjPtr caller
)
  : Object::PyObject(FrameKlass::Self()),
    stack(),
    programCounter(0),
    code(std::move(code)),
    locals(std::move(locals)),
    globals(std::move(globals)),
    fastLocals(std::move(fastLocals)),
    caller(std::move(caller)) {}

// PyFrame::PyFrame(PyCodePtr code)
//   : Object::PyObject(FrameKlass::Self()),
//     code(std::move(code)),
//     locals(std::make_shared<Object::PyDictionary>()),
//     globals(locals) {
//   List<PyObjPtr> fastLocalsList(this->code->NLocals());
//   fastLocalsList.Fill(Object::PyNone::Instance());
//   fastLocals =
//   std::make_shared<Object::PyList>(List<PyObjPtr>(fastLocalsList)); caller =
//   Object::PyNone::Instance();
// }

// PyFrame::PyFrame(
//   const PyFunctionPtr& function,
//   const List<PyObjPtr>& arguments,
//   PyObjPtr caller
// )
//   : Object::PyObject(FrameKlass::Self()),
//     code(function->Code()),
//     globals(function->Globals()),
//     caller(std::move(caller)) {
//   code = function->Code();
//   locals = std::make_shared<Object::PyDictionary>();
//   Index nLocals = code->NLocals();
//   List<PyObjPtr> fastLocalsList(std::max(nLocals, arguments.Size()));
//   for (auto it = List<PyObjPtr>::Iterator::Begin(arguments); !it.End();
//        it.Next()) {
//     fastLocalsList.Add(it.Get());
//   }
//   if (nLocals > arguments.Size()) {
//     fastLocalsList.AppendElements(
//       Object::PyNone::Instance(), nLocals - arguments.Size()
//     );
//   }
//   fastLocals = std::make_shared<Object::PyList>(fastLocalsList);
// }

PyFramePtr CreateFrameWithCode(const Object::PyCodePtr& code) {
  auto locals = Object::CreatePyDict();
  auto globals = locals;
  auto fastLocals = Object::CreatePyList(code->NLocals());
  return std::make_shared<PyFrame>(
    code, locals, globals, fastLocals, Object::PyNone::Instance()
  );
}

PyFramePtr CreateFrameWithFunction(
  const PyFunctionPtr& function,
  const Collections::List<Object::PyObjPtr>& arguments,
  Object::PyObjPtr caller
) {
  auto code = function->Code();
  auto globals = function->Globals();
  auto locals = Object::CreatePyDict();
  Index nLocals = code->NLocals();
  Collections::List<Object::PyObjPtr> fastLocalsList(arguments.Size());
  for (auto it = Collections::Iterator<Object::PyObjPtr>::Begin(arguments);
       !it.End(); it.Next()) {
    fastLocalsList.Push(it.Get());
  }
  auto fastLocals = Object::CreatePyList(fastLocalsList, nLocals);
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
  if (!code->Instructions()) {
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
      case Object::ByteCode::BINARY_SUBTRACT: {
        insts.Push(Object::CreateBinarySubtract());
        break;
      }
      case Object::ByteCode::PRINT: {
        insts.Push(Object::CreatePrint());
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
    Object::CreatePyString(Collections::CreateStringWithCString("<frame>\n"));
  repr = repr->add(
    Object::CreatePyString(Collections::CreateStringWithCString("stack:\n"))
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
        ->add(it.Get()->repr())->add(Object::CreatePyString(
          Collections::CreateStringWithCString("\n")
        ));
  }
  repr =
    repr->add(Object::CreatePyString(Collections::CreateStringWithCString("\n"))
    );
  repr = repr->add(
    Object::CreatePyString(Collections::CreateStringWithCString("locals:\n"))
  );
  repr = repr->add(frame->Locals()->repr());
  repr =
    repr->add(Object::CreatePyString(Collections::CreateStringWithCString("\n"))
    );
  repr = repr->add(
    Object::CreatePyString(Collections::CreateStringWithCString("globals:\n"))
  );
  repr = repr->add(frame->Globals()->repr());
  repr =
    repr->add(Object::CreatePyString(Collections::CreateStringWithCString("\n"))
    );
  repr = repr->add(Object::CreatePyString(
    Collections::CreateStringWithCString("fastLocals:\n")
  ));
  repr = repr->add(frame->FastLocals()->repr());
  repr =
    repr->add(Object::CreatePyString(Collections::CreateStringWithCString("\n"))
    );
  repr = repr->add(
    Object::CreatePyString(Collections::CreateStringWithCString("caller:\n"))
  );
  repr = repr->add(frame->Caller()->repr());
  repr =
    repr->add(Object::CreatePyString(Collections::CreateStringWithCString("\n"))
    );
  repr = repr->add(
    Object::CreatePyString(Collections::CreateStringWithCString("code:\n"))
  );
  repr = repr->add(code->repr());
  repr =
    repr->add(Object::CreatePyString(Collections::CreateStringWithCString("\n"))
    );
  repr = repr->add(Object::CreatePyString(
    Collections::CreateStringWithCString("instruction:\n")
  ));
  repr = repr->add(frame->Instruction()->repr());
  repr =
    repr->add(Object::CreatePyString(Collections::CreateStringWithCString("\n"))
    );
  repr = repr->add(Object::CreatePyString(
    Collections::CreateStringWithCString("programCounter:\n")
  ));
  repr = repr->add(Object::CreatePyInteger(
                     Collections::CreateIntegerWithU64(frame->ProgramCounter())
  )
                     ->repr());
  return repr;
}

Object::PyObjPtr PyFrame::Caller() const {
  return caller;
}

bool PyFrame::HasCaller() const {
  return caller != Object::PyNone::Instance();
}
}  // namespace torchlight::Runtime
