#include "Object/PyList.h"
#include "ByteCode/ByteCode.h"
#include "Collections/BytesHelper.h"
#include "Collections/Integer.h"
#include "Function/FunctionForward.h"
#include "Function/PyNativeFunction.h"
#include "Object/Iterator.h"
#include "Object/Object.h"
#include "Object/ObjectHelper.h"
#include "Object/PyBoolean.h"
#include "Object/PyBytes.h"
#include "Object/PyInteger.h"
#include "Object/PyNone.h"
#include "Object/PyObject.h"
#include "Object/PySlice.h"
#include "Object/PyString.h"
#include "Object/PyType.h"

namespace torchlight::Object {

PyObjPtr CreatePyList(Index capacity) {
  if (capacity == 0) {
    return std::make_shared<PyList>(Collections::List<PyObjPtr>());
  }
  Collections::List<PyObjPtr> list(capacity);
  list.Fill(PyNone::Instance());
  return std::make_shared<PyList>(list);
}

PyObjPtr CreatePyList(Collections::List<PyObjPtr> list) {
  return std::make_shared<PyList>(list);
}

void ListKlass::Initialize() {
  LoadClass(CreatePyString("list")->as<PyString>(), Self());
  ConfigureBasicAttributes(Self());
  Self()->AddAttribute(
    CreatePyString("append")->as<PyString>(), CreatePyNativeFunction(ListAppend)
  );
  Self()->AddAttribute(
    CreatePyString("index")->as<PyString>(), CreatePyNativeFunction(ListIndex)
  );
  // 注册重载函数
  Self()->AddAttribute(
    CreatePyString("__getitem__")->as<PyString>(),
    CreatePyNativeFunction(CreateForwardFunction<ListKlass>(&ListKlass::getitem)
    )
  );
  Self()->AddAttribute(
    CreatePyString("__setitem__")->as<PyString>(),
    CreatePyNativeFunction(CreateForwardFunction<ListKlass>(&ListKlass::setitem)
    )
  );
  Self()->AddAttribute(
    CreatePyString("__len__")->as<PyString>(),
    CreatePyNativeFunction(CreateForwardFunction<ListKlass>(&ListKlass::len))
  );
  Self()->AddAttribute(
    CreatePyString("__contains__")->as<PyString>(),
    CreatePyNativeFunction(
      CreateForwardFunction<ListKlass>(&ListKlass ::contains)
    )
  );
  Self()->AddAttribute(
    CreatePyString("__iter__")->as<PyString>(),
    CreatePyNativeFunction(CreateForwardFunction<ListKlass>(&ListKlass::iter))
  );
  Self()->AddAttribute(
    CreatePyString("__add__")->as<PyString>(),
    CreatePyNativeFunction(CreateForwardFunction<ListKlass>(&ListKlass::add))
  );
  Self()->AddAttribute(
    CreatePyString("__mul__")->as<PyString>(),
    CreatePyNativeFunction(CreateForwardFunction<ListKlass>(&ListKlass::mul))
  );
  Self()->AddAttribute(
    CreatePyString("__str__")->as<PyString>(),
    CreatePyNativeFunction(CreateForwardFunction<ListKlass>(&ListKlass::str))
  );
  Self()->AddAttribute(
    CreatePyString("__repr__")->as<PyString>(),
    CreatePyNativeFunction(CreateForwardFunction<ListKlass>(&ListKlass::repr))
  );
  Self()->AddAttribute(
    CreatePyString("__eq__")->as<PyString>(),
    CreatePyNativeFunction(CreateForwardFunction<ListKlass>(&ListKlass::eq))
  );
  Self()->AddAttribute(
    CreatePyString("__init__")->as<PyString>(),
    CreatePyNativeFunction(CreateForwardFunction<ListKlass>(&ListKlass::init))
  );
  Self()->AddAttribute(
    CreatePyString("__serialize__")->as<PyString>(),
    CreatePyNativeFunction(
      CreateForwardFunction<ListKlass>(&ListKlass::_serialize_)
    )
  );
}

PyObjPtr ListKlass::init(const PyObjPtr& type, const PyObjPtr& args) {
  if (type->as<PyType>()->Owner() != Self()) {
    throw std::runtime_error("List does not support init operation");
  }
  if (!args->is<PyList>()) {
    throw std::runtime_error("List allocation argument must be a list");
  }
  auto argList = args->as<PyList>();
  if (argList->Length() == 0) {
    return CreatePyList({});
  }
  CheckNativeFunctionArgumentsWithExpectedLength(args, 1);
  auto value = argList->GetItem(0);
  if (!value->is<PyList>()) {
    throw std::runtime_error("List allocation argument must be a list");
  }
  return value;
}

PyObjPtr ListKlass::add(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  if (!lhs->is<PyList>() || !rhs->is<PyList>()) {
    throw std::runtime_error("List does not support add operation");
  }
  return lhs->as<PyList>()->Add(rhs->as<PyList>());
}

PyObjPtr ListKlass::mul(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  if (!lhs->is<PyList>() || !rhs->is<PyInteger>()) {
    throw std::runtime_error("List does not support mul operation");
  }
  auto list = lhs->as<PyList>();
  auto times = rhs->as<PyInteger>()->ToU64();
  if (list->Length() == 1) {
    auto value = list->GetItem(0);
    Collections::List<PyObjPtr> result(times, value);
    return CreatePyList(result);
  }
  Collections::List<PyObjPtr> result(list->Length() * times);
  for (Index i = 0; i < times; i++) {
    for (Index j = 0; j < list->Length(); j++) {
      result.Push(list->GetItem(j));
    }
  }
  return CreatePyList(result);
}

PyObjPtr ListKlass::str(const PyObjPtr& obj) {
  auto list = obj->as<PyList>();
  auto strList = Map(list, [](const PyObjPtr& value) { return value->str(); });
  return StringConcat(CreatePyList(
    {CreatePyString("[")->as<PyString>(),
     CreatePyString(", ")->as<PyString>()->Join(strList),
     CreatePyString("]")->as<PyString>()}
  ));
}

PyObjPtr ListKlass::repr(const PyObjPtr& obj) {
  auto list = obj->as<PyList>();
  auto reprList =
    Map(list, [](const PyObjPtr& value) { return value->repr(); });
  return StringConcat(CreatePyList(
    {CreatePyString("["), CreatePyString(", ")->as<PyString>()->Join(reprList),
     CreatePyString("]")}
  ));
}

PyObjPtr ListKlass::eq(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  if (!lhs->is<PyList>() || !rhs->is<PyList>()) {
    return CreatePyBoolean(false);
  }
  auto left = lhs->as<PyList>();
  auto right = rhs->as<PyList>();
  if (left->Length() != right->Length()) {
    return CreatePyBoolean(false);
  }
  for (Index i = 0; i < left->Length(); i++) {
    if (left->GetItem(i) != right->GetItem(i)) {
      return CreatePyBoolean(false);
    }
  }
  return CreatePyBoolean(true);
}

PyObjPtr ListKlass::getitem(const PyObjPtr& obj, const PyObjPtr& key) {
  if (!obj->is<PyList>()) {
    auto errorMessage = StringConcat(CreatePyList(
      {CreatePyString("AttributeError: '"), obj->Klass()->Name(),
       CreatePyString("' object has no attribute '__getitem__'")}
    ));
    throw std::runtime_error(errorMessage->as<PyString>()->ToCppString());
  }
  auto list = obj->as<PyList>();
  if (key->is<PyInteger>()) {
    auto index = key->as<PyInteger>();
    if (index->GetSign() == Collections::Integer::IntSign::Positive) {
      return list->GetItem(index->ToU64());
    }
    if (index->GetSign() == Collections::Integer::IntSign::Negative) {
      return list->GetItem(list->Length() + index->ToI64());
    }
  }
  if (key->is<PySlice>()) {
    auto slice = key->as<PySlice>();
    return list->GetSlice(slice);
  }
  if (key->is<PyList>()) {
    auto indexList = key->as<PyList>();
    auto result = obj;
    for (Index i = 0; i < indexList->Length(); i++) {
      result = result->getitem(indexList->GetItem(i));
    }
    return result;
  }
  auto errorMessage = StringConcat(CreatePyList(
    {CreatePyString("TypeError: list indices must be integers or slices, not '"
     ),
     key->Klass()->Name(), CreatePyString("'")}
  ));
  throw std::runtime_error(errorMessage->as<PyString>()->ToCppString());
}

PyObjPtr ListKlass::setitem(
  const PyObjPtr& obj,
  const PyObjPtr& key,
  const PyObjPtr& value
) {
  if (!obj->is<PyList>()) {
    auto errorMessage = StringConcat(CreatePyList(
      {CreatePyString("AttributeError: '"), obj->Klass()->Name(),
       CreatePyString("' object has no attribute '__setitem__'")}
    ));
    throw std::runtime_error(errorMessage->as<PyString>()->ToCppString());
  }
  auto list = obj->as<PyList>();
  // list[key] = value
  if (key->is<PyInteger>()) {
    auto index = key->as<PyInteger>()->ToU64();
    list->SetItem(index, value);
    return CreatePyNone();
  }
  // list[start:stop] = iterable
  if (key->is<PySlice>()) {
    auto slice = key->as<PySlice>();
    if (!slice->GetStep()->is<PyNone>()) {
      throw std::runtime_error("List does not support step in slice assignment"
      );
    }
    slice->BindLength(list->Length());
    auto stop = slice->GetStop()->as<PyInteger>()->ToU64();
    auto start = slice->GetStart()->as<PyInteger>()->ToU64();
    auto valueList = CreatePyListFromIterable(value);
    list->InsertAndReplace(start, stop, valueList);
    return CreatePyNone();
  }
  if (key->is<PyList>()) {
    auto indexList = key->as<PyList>();
    auto result = obj;
    for (Index i = 0; i < indexList->Length() - 1; i++) {
      result = result->getitem(indexList->GetItem(i));
    }
    result->setitem(indexList->GetItem(indexList->Length() - 1), value);
    return CreatePyNone();
  }
  auto errorMessage = StringConcat(CreatePyList(
    {CreatePyString("TypeError: list indices must be integers or slices, not '"
     ),
     key->Klass()->Name(), CreatePyString("'")}
  ));
  throw std::runtime_error(errorMessage->as<PyString>()->ToCppString());
}

PyObjPtr ListKlass::len(const PyObjPtr& obj) {
  if (!obj->is<PyList>()) {
    auto errorMessage = StringConcat(CreatePyList(
      {CreatePyString("TypeError: unsupported operand type(s) for"),
       CreatePyString(" len(): '"), obj->Klass()->Name(), CreatePyString("'")}
    ));
    throw std::runtime_error(errorMessage->as<PyString>()->ToCppString());
  }
  return CreatePyInteger(obj->as<PyList>()->Length());
}

PyObjPtr ListKlass::contains(const PyObjPtr& obj, const PyObjPtr& key) {
  if (!obj->is<PyList>()) {
    throw std::runtime_error("List does not support contains operation");
  }
  return CreatePyBoolean(obj->as<PyList>()->Contains(key));
}

PyObjPtr ListKlass::boolean(const PyObjPtr& obj) {
  if (!obj->is<PyList>()) {
    throw std::runtime_error("List does not support boolean operation");
  }
  return CreatePyBoolean(obj->as<PyList>()->Length() > 0);
}

PyObjPtr ListKlass::_serialize_(const PyObjPtr& obj) {
  if (!obj->is<PyList>()) {
    throw std::runtime_error("List does not support serialize operation");
  }
  auto list = obj->as<PyList>();
  PyObjPtr bytes =
    CreatePyBytes(Collections::Serialize(Literal::LIST)
                    .Add(Collections::Serialize(list->Length())));
  auto iter = CreateListIterator(obj);
  auto value = iter->next();
  while (!value->is<IterDone>()) {
    bytes = bytes->add(value->_serialize_());
    value = iter->next();
  }
  return bytes;
}

PyObjPtr ListAppend(const PyObjPtr& args) {
  CheckNativeFunctionArgumentsWithExpectedLength(args, 2);
  auto argList = args->as<PyList>();
  auto obj = argList->GetItem(1);
  auto list = argList->GetItem(0)->as<PyList>();
  list->Append(obj);
  return CreatePyNone();
}

PyObjPtr ListIndex(const PyObjPtr& args) {
  CheckNativeFunctionArgumentsWithExpectedLength(args, 2);
  auto funcName = CreatePyString("list_index")->as<PyString>();
  CheckNativeFunctionArgumentsAtIndexWithType(
    funcName, args, 0, ListKlass::Self()
  );
  auto argList = args->as<PyList>();
  auto obj = argList->GetItem(1);
  auto list = argList->GetItem(0)->as<PyList>();
  return CreatePyInteger(list->IndexOf(obj));
}

PyObjPtr ListKlass::iter(const PyObjPtr& obj) {
  if (!obj->is<PyList>()) {
    throw std::runtime_error("List does not support iter operation");
  }
  return CreateListIterator(obj);
}

PyObjPtr PyList::GetSlice(const PySlicePtr& slice) const {
  if (slice->GetStep()->is<PyNone>()) {
    slice->BindLength(Length());
    int64_t start = slice->GetStart()->as<PyInteger>()->ToI64();
    int64_t stop = slice->GetStop()->as<PyInteger>()->ToI64();
    return CreatePyList(value.Slice(start, stop))->as<PyList>();
  }
  slice->BindLength(Length());
  int64_t start = slice->GetStart()->as<PyInteger>()->ToI64();
  int64_t stop = slice->GetStop()->as<PyInteger>()->ToI64();
  int64_t step = slice->GetStep()->as<PyInteger>()->ToI64();
  auto subList = CreatePyList({})->as<PyList>();
  if (step > 0) {
    for (int64_t i = start; i < stop; i += step) {
      if (i >= Length()) {
        break;
      }
      subList->Append(GetItem(i));
    }
    return subList;
  }
  for (int64_t i = start; i > stop; i += step) {
    if (i >= Length()) {
      break;
    }
    subList->Append(GetItem(i));
  }
  return subList;
}

PyListPtr CreatePyListFromIterable(const PyObjPtr& iterator) {
  auto iter = iterator->iter();
  auto iterable = std::dynamic_pointer_cast<IIterator>(iter);
  if (!iterable) {
    throw std::runtime_error("object is not iterable");
  }
  auto value = iter->next();
  Collections::List<PyObjPtr> list;
  while (!value->is<IterDone>()) {
    list.Push(value);
    value = iter->next();
  }
  return CreatePyList(list)->as<PyList>();
}

}  // namespace torchlight::Object