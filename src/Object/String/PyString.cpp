#include "Object/String/PyString.h"
#include "ByteCode/ByteCode.h"
#include "Collections/String/BytesHelper.h"
#include "Collections/String/StringHelper.h"
#include "Object/Container/PyList.h"
#include "Object/Core/CoreHelper.h"
#include "Object/Core/PyBoolean.h"
#include "Object/Core/PyType.h"
#include "Object/Function/FunctionForward.h"
#include "Object/Function/PyNativeFunction.h"
#include "Object/Iterator/Iterator.h"
#include "Object/Iterator/IteratorHelper.h"
#include "Object/Number/PyInteger.h"
#include "Object/Object.h"
#include "PyBytes.h"

#include <iostream>

namespace tensorslow::Object {
Index PyString::indent = 0;
std::unordered_map<size_t, std::shared_ptr<PyString>> PyString::stringPool;
std::mutex PyString::poolMutex;
void StringKlass::Initialize() {
  InitKlass(CreatePyString("str")->as<PyString>(), Self());
  Self()->AddAttribute(
    CreatePyString("join")->as<PyString>(), CreatePyNativeFunction(StringJoin)
  );
  //  Self()->AddAttribute(
  //    CreatePyString("split")->as<PyString>(),
  //    CreatePyNativeFunction(StringSplit)
  //  );
  Self()->AddAttribute(
    CreatePyString("upper")->as<PyString>(), CreatePyNativeFunction(StringUpper)
  );
  Self()->AddAttribute(
    CreatePyString("__add__")->as<PyString>(),
    CreatePyNativeFunction(CreateForwardFunction<StringKlass>(&StringKlass::add)
    )
  );
  Self()->AddAttribute(
    CreatePyString("__eq__")->as<PyString>(),
    CreatePyNativeFunction(CreateForwardFunction<StringKlass>(&StringKlass::eq))
  );
  Self()->AddAttribute(
    CreatePyString("__len__")->as<PyString>(),
    CreatePyNativeFunction(CreateForwardFunction<StringKlass>(&StringKlass::len)
    )
  );
  Self()->AddAttribute(
    CreatePyString("__str__")->as<PyString>(),
    CreatePyNativeFunction(CreateForwardFunction<StringKlass>(&StringKlass::str)
    )
  );
  Self()->AddAttribute(
    CreatePyString("__repr__")->as<PyString>(),
    CreatePyNativeFunction(CreateForwardFunction<StringKlass>(&StringKlass::repr
    ))
  );
  Self()->AddAttribute(
    CreatePyString("__iter__")->as<PyString>(),
    CreatePyNativeFunction(CreateForwardFunction<StringKlass>(&StringKlass::iter
    ))
  );
  Self()->AddAttribute(
    CreatePyString("__serialize__")->as<PyString>(),
    CreatePyNativeFunction(
      CreateForwardFunction<StringKlass>(&StringKlass::_serialize_)
    )
  );
  Self()->AddAttribute(
    CreatePyString("__init__")->as<PyString>(),
    CreatePyNativeFunction(CreateForwardFunction<StringKlass>(&StringKlass::init
    ))
  );
}

PyObjPtr StringKlass::init(const PyObjPtr& klass, const PyObjPtr& args) {
  if (klass->as<PyType>()->Owner() != Self()) {
    throw std::runtime_error("init(): klass is not a string");
  }
  auto argList = args->as<PyList>();
  if (argList->Length() == 0) {
    return CreatePyString("");
  }
  if (argList->Length() != 1) {
    throw std::runtime_error("init(): args must be a list with one element");
  }
  return argList->GetItem(0)->str();
}

PyObjPtr StringKlass::add(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  if (!lhs->is(StringKlass::Self()) || !rhs->is(StringKlass::Self())) {
    throw std::runtime_error("StringKlass::add(): lhs or rhs is not a string");
  }
  auto left = lhs->as<PyString>();
  auto right = rhs->as<PyString>();
  return left->Add(right);
}

PyObjPtr StringKlass::eq(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  if (!lhs->is(StringKlass::Self()) || !rhs->is(StringKlass::Self())) {
    return CreatePyBoolean(false);
  }
  auto left = lhs->as<PyString>();
  auto right = rhs->as<PyString>();
  return CreatePyBoolean(left->Equal(right));
}

PyObjPtr StringKlass::len(const PyObjPtr& obj) {
  if (!obj->is(StringKlass::Self())) {
    throw std::runtime_error("StringKlass::len(): obj is not a string");
  }
  auto string = obj->as<PyString>();
  return CreatePyInteger(string->Length());
}

PyObjPtr StringKlass::str(const PyObjPtr& obj) {
  if (!obj->is(StringKlass::Self())) {
    throw std::runtime_error("StringKlass::str(): obj is not a string");
  }
  return obj;
}

PyObjPtr StringKlass::repr(const PyObjPtr& obj) {
  if (!obj->is(StringKlass::Self())) {
    throw std::runtime_error("StringKlass::repr(): obj is not a string");
  }
  auto string = obj->as<PyString>();
  return StringConcat(
    CreatePyList({CreatePyString("'"), string, CreatePyString("'")})
  );
}

PyObjPtr StringKlass::iter(const PyObjPtr& obj) {
  if (!obj->is(StringKlass::Self())) {
    throw std::runtime_error("StringKlass::iter(): obj is not a string");
  }
  return CreateStringIterator(obj);
}

PyObjPtr StringKlass::hash(const PyObjPtr& obj) {
  if (!obj->is(StringKlass::Self())) {
    throw std::runtime_error("StringKlass::hash(): obj is not a string");
  }
  if (obj->Hashed()) {
    return CreatePyInteger(obj->HashValue());
  }
  auto string = obj->as<PyString>();
  size_t hash = string->Hash();
  string->SetHashValue(hash);
  return CreatePyInteger(hash);
}

PyObjPtr StringKlass::boolean(const PyObjPtr& obj) {
  if (!obj->is(StringKlass::Self())) {
    throw std::runtime_error("StringKlass::boolean(): obj is not a string");
  }
  auto string = obj->as<PyString>();
  return CreatePyBoolean(string->Length() > 0);
}

PyObjPtr StringKlass::_serialize_(const PyObjPtr& obj) {
  if (!obj->is(StringKlass::Self())) {
    throw std::runtime_error("StringKlass::_serialize_(): obj is not a string");
  }
  Collections::StringBuilder bytes(Collections::Serialize(Literal::STRING));
  bytes.Append(Collections::Serialize(obj->as<PyString>()->value));
  return CreatePyBytes(bytes.ToString());
}

PyStrPtr PyString::GetItem(Index index) {
  if (index >= value.GetCodePointCount()) {
    throw std::runtime_error("PyString::GetItem(): index out of range");
  }
  return CreatePyString(
    Collections::String(value.Slice(index, index + 1)), false
  );
}

PyStrPtr PyString::Join(const PyObjPtr& iterable) {
  Collections::StringBuilder sb;
  for (Index i = 0; i < iterable->as<PyList>()->Length(); i++) {
    auto item = iterable->as<PyList>()->GetItem(i);
    if (i == 0) {
      sb.Append(item->as<PyString>()->value);
    } else {
      sb.Append(value);
      sb.Append(item->as<PyString>()->value);
    }
  }
  return CreatePyString(sb.ToString(), false)->as<PyString>();
}

// PyListPtr PyString::Split(const PyStrPtr& delimiter) {
//   auto parts = value.Split(delimiter->value);
//   auto result = CreatePyList(parts.Size())->as<PyList>();
//   for (Index i = 0; i < parts.Size(); i++) {
//     result->SetItem(i, CreatePyString(parts[i]));
//   }
//   return result;
// }

PyStrPtr PyString::Add(const PyStrPtr& other) {
  return CreatePyString(value.Add(other->value), false)->as<PyString>();
}

void PyString::Print(bool enableIndent) const {
  if (enableIndent) {
    for (Index i = 0; i < indent; i++) {
      std::cout << "  " << std::flush;
    }
  }
  std::cout << ToCppString() << std::flush;
}

void PyString::PrintLine(bool enableIndent) const {
  if (enableIndent) {
    for (Index i = 0; i < indent; i++) {
      std::cout << "  " << std::flush;
    }
  }
  std::cout << ToCppString() << std::endl;
}

std::string PyString::ToCppString() const {
  return value.ToCppString();
}

bool PyString::Equal(const PyStrPtr& other) {
  return value.Equal(other->value);
}

PyStrPtr PyString::Upper() {
  return CreatePyString(value.Upper())->as<PyString>();
}

PyObjPtr StringConcat(const PyObjPtr& args) {
  CheckNativeFunctionArguments(args);
  auto argList = args->as<PyList>();
  auto funcName = CreatePyString("StringConcat")->as<PyString>();
  auto result = CreatePyString("")->as<PyString>();
  for (Index i = 0; i < argList->Length(); i++) {
    auto value = argList->GetItem(i);
    CheckNativeFunctionArgumentWithType(
      funcName, value, i, StringKlass::Self()
    );
    result = result->Add(value->as<PyString>());
  }
  return result;
}

PyObjPtr StringUpper(const PyObjPtr& args) {
  CheckNativeFunctionArgumentsWithExpectedLength(args, 1);
  auto funcName = CreatePyString("StringUpper")->as<PyString>();
  CheckNativeFunctionArgumentsAtIndexWithType(
    funcName, args, 0, StringKlass::Self()
  );
  auto argList = args->as<PyList>();
  auto value = argList->GetItem(0)->as<PyString>();
  return value->Upper();
}

PyObjPtr StringJoin(const PyObjPtr& args) {
  CheckNativeFunctionArgumentsWithExpectedLength(args, 2);
  auto argList = args->as<PyList>();
  auto delimiter = argList->GetItem(0)->as<PyString>();
  auto list = argList->GetItem(1)->as<PyList>();
  auto strList = Map(list, [](const PyObjPtr& item) { return item->str(); });
  return delimiter->Join(strList);
}

// PyObjPtr StringSplit(const PyObjPtr& args) {
//   CheckNativeFunctionArgumentsWithExpectedLength(args, 2);
//   auto argList = args->as<PyList>();
//   auto delimiter = argList->GetItem(0)->as<PyString>();
//   auto value = argList->GetItem(1)->as<PyString>();
//   return value->Split(delimiter);
// }

PyStrPtr PyString::Create(const Collections::String& value) {
  std::lock_guard<std::mutex> lock(poolMutex);
  auto hash = value.HashValue();
  auto iter = stringPool.find(hash);
  if (iter != stringPool.end()) {
    return iter->second;
  }
  auto result = std::make_shared<PyString>(value);
  stringPool[hash] = result;
  return result;
}

PyStrPtr CreatePyString(const Collections::String& value, bool pooling) {
  if (pooling) {
    return PyString::Create(value);
  }
  return std::make_shared<PyString>(value);
}

PyStrPtr CreatePyString(const std::string& value) {
  return PyString::Create(Collections::CreateStringWithCString(value.c_str()));
}

PyStrPtr CreatePyString(const char* value) {
  return PyString::Create(Collections::CreateStringWithCString(value));
}

}  // namespace tensorslow::Object