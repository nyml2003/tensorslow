#include "object/PyCode.h"
#include "collections/impl/Bytes.h"
#include "collections/impl/String.h"
#include "object/ByteCode.h"
#include "object/Klass.h"
#include "object/PyBytes.h"
#include "object/PyList.h"
#include "object/PyObject.h"
#include "object/PyString.h"

#include <cstring>
#include <memory>

namespace torchlight::object {
using collections::ToString;

PyCode::PyCode(
  const PyObjPtr& byteCodes,
  const PyObjPtr& consts,
  const PyObjPtr& names,
  const PyObjPtr& filename
)
  : PyObject(CodeKlass::Self()) {
  if (byteCodes->Klass() != BytesKlass::Self()) {
    throw std::runtime_error("byteCodes must be a bytes object");
  }
  byteCode = std::dynamic_pointer_cast<PyBytes>(byteCodes);
  if (consts->Klass() != ListKlass::Self()) {
    throw std::runtime_error("consts must be a list object");
  }
  this->consts = std::dynamic_pointer_cast<PyList>(consts);
  if (names->Klass() != ListKlass::Self()) {
    throw std::runtime_error("names must be a list object");
  }
  this->names = std::dynamic_pointer_cast<PyList>(names);
  if (filename->Klass() != StringKlass::Self()) {
    throw std::runtime_error("filename must be a string object");
  }
  this->filename = std::dynamic_pointer_cast<PyString>(filename);
}

PyListPtr PyCode::Instructions() {
  return instructions;
}

void PyCode::SetInstructions(const PyListPtr& insts) {
  instructions = insts;
}

PyBytesPtr PyCode::ByteCode() const {
  return byteCode;
}

PyListPtr PyCode::Consts() const {
  return consts;
}

PyListPtr PyCode::Names() const {
  return names;
}

PyStrPtr PyCode::Filename() const {
  return filename;
}

CodeKlass::CodeKlass()
  : object::Klass(collections::CreateStringWithCString("code")) {}

object::KlassPtr CodeKlass::Self() {
  static object::KlassPtr instance = std::make_shared<CodeKlass>();
  return instance;
}

PyObjPtr CodeKlass::repr(PyObjPtr self) {
  if (self->Klass() != Self()) {
    return nullptr;
  }
  auto code = std::dynamic_pointer_cast<PyCode>(self);
  String result = collections::CreateStringWithCString("<code object ");
  result.InplaceConcat(code->Filename()->Value());
  result.InplaceConcat(collections::CreateStringWithCString(" at "));
  result.InplaceConcat(String(ToString(reinterpret_cast<uint64_t>(self.get())))
  );
  result.InplaceConcat(collections::CreateStringWithCString(">\n"));
  result.InplaceConcat(collections::CreateStringWithCString("Consts:\n"));
  auto const_list = std::dynamic_pointer_cast<PyList>(code->Consts())->Value();
  for (auto it = List<PyObjPtr>::Iterator::Begin(const_list); !it.End();
       it.Next()) {
    auto obj = it.Get()->repr();
    result.InplaceConcat(ToString(it.Index()));
    result.InplaceConcat(collections::CreateStringWithCString("  "));
    auto str = std::dynamic_pointer_cast<PyString>(obj);
    result.InplaceConcat(str->Value());
    result.InplaceConcat(collections::CreateStringWithCString("\n"));
  }
  result.InplaceConcat(collections::CreateStringWithCString("Names:\n"));
  auto names = std::dynamic_pointer_cast<PyList>(code->Names())->Value();
  for (auto it = List<PyObjPtr>::Iterator::Begin(names); !it.End(); it.Next()) {
    result.InplaceConcat(ToString(it.Index()));
    result.InplaceConcat(collections::CreateStringWithCString("  "));
    auto name = std::dynamic_pointer_cast<PyString>(it.Get()->repr());
    result.InplaceConcat(name->Value());
    result.InplaceConcat(collections::CreateStringWithCString("\n"));
  }
  // result.InplaceConcat(collections::CreateStringWithCString("Instructions:\n"));
  // auto insts = code->Instructions();
  // for (auto it = List<PyObjPtr>::Iterator::Begin(insts->Value()); !it.End();
  //      it.Next()) {
  //   result.InplaceConcat(ToString(it.Index()));
  //   result.InplaceConcat(collections::CreateStringWithCString("  "));
  //   auto inst_str = std::dynamic_pointer_cast<PyString>(it.Get()->repr());
  //   result.InplaceConcat(inst_str->Value());
  //   result.InplaceConcat(collections::CreateStringWithCString("\n"));
  // }
  return std::make_shared<PyString>(result);
}

PyObjPtr CodeKlass::_serialize_(PyObjPtr self) {
  if (self->Klass() != Self()) {
    return nullptr;
  }
  auto code = std::dynamic_pointer_cast<PyCode>(self);
  PyObjPtr result =
    std::make_shared<PyBytes>(collections::CreateBytesWithCString(""));
  result = result->add(code->Filename()->_serialize_());
  result = result->add(code->Consts()->_serialize_());
  result = result->add(code->Names()->_serialize_());
  result = result->add(code->ByteCode()->_serialize_());
  return result;
}

}  // namespace torchlight::object