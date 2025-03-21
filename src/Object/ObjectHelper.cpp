#include "Object/ObjectHelper.h"
#include "Collections/IntegerHelper.h"
#include "Function/PyFunction.h"
#include "Function/PyIife.h"
#include "Function/PyMethod.h"
#include "Function/PyNativeFunction.h"
#include "Object/Iterator.h"
#include "Object/Object.h"
#include "Object/PyBoolean.h"
#include "Object/PyDictionary.h"
#include "Object/PyFloat.h"
#include "Object/PyInteger.h"
#include "Object/PyList.h"
#include "Object/PyMatrix.h"
#include "Object/PyNone.h"
#include "Object/PyObject.h"
#include "Object/PyString.h"
#include "Object/PyType.h"
#include "Runtime/Interpreter.h"

#include <random>
#include <thread>
#include <iostream>
namespace torchlight::Object {

PyObjPtr
Invoke(const PyObjPtr& obj, const PyObjPtr& methodName, const PyListPtr& args) {
  auto func = obj->getattr(methodName);
  if (func == nullptr) {
    auto errorMessge = CreatePyString("AttributeError: ")
                         ->add(obj->str())
                         ->add(CreatePyString(" has no attribute "))
                         ->add(methodName->str())
                         ->as<PyString>();
    throw std::runtime_error(errorMessge->ToCppString());
  }
  return Runtime::Interpreter::Eval(func, args);
}

void BasicKlassLoad() {
  Object::StringKlass::Initialize();
  Object::IntegerKlass::Initialize();
  Object::ListKlass::Initialize();
  Object::DictionaryKlass::Initialize();
  Object::TypeKlass::Initialize();
  Object::BooleanKlass::Initialize();
  Object::NativeFunctionKlass::Initialize();
  Object::IifeKlass::Initialize();
  Object::ListIteratorKlass::Initialize();
  Object::IterDoneKlass::Initialize();
}

void ForEach(
  const PyObjPtr& obj,
  const std::function<
    void(const PyObjPtr& value, Index index, const PyObjPtr& obj)>& func
) {
  auto iter = obj->iter();
  auto iterable = iter->as<IIterator>();
  if (!iterable) {
    throw std::runtime_error("object is not iterable");
  }
  auto value = iter->next();
  while (!value->is<IterDone>()) {
    func(value, iterable->CurrentIndex(), obj);
    value = iter->next();
  }
}

PyObjPtr Map(
  const PyObjPtr& iterable,
  const std::function<PyObjPtr(const PyObjPtr& value)>& func
) {
  auto iter = iterable->iter();
  auto iterableObj = iter->as<IIterator>();
  if (!iterableObj) {
    throw std::runtime_error("object is not iterable");
  }
  auto value = iter->next();
  Collections::List<PyObjPtr> result;
  while (!value->is<IterDone>()) {
    result.Push(func(value));
    value = iter->next();
  }
  return CreatePyList(result)->as<PyList>();
}

PyObjPtr Str(const PyObjPtr& args) {
  CheckNativeFunctionArguments(args);
  auto argList = args->as<PyList>();
  if (argList->Length() == 0) {
    return CreatePyString("");
  }
  if (argList->Length() != 1) {
    throw std::runtime_error("str() takes at most 1 argument");
  }
  return args->as<PyList>()->GetItem(0)->str();
}

PyObjPtr KlassStr(const PyObjPtr& args) {
  return StringConcat(CreatePyList(
    {CreatePyString("<"), args->as<PyList>()->GetItem(0)->Klass()->Name(),
     CreatePyString(" object at "), Identity(args),
     CreatePyString(">")}
  ));
}

PyObjPtr Repr(const PyObjPtr& args) {
  CheckNativeFunctionArgumentsWithExpectedLength(args, 1);
  return args->as<PyList>()->GetItem(0)->repr();
}

PyObjPtr KlassRepr(const PyObjPtr& args) {
  return StringConcat(CreatePyList(
    {CreatePyString("<"), args->as<PyList>()->GetItem(0)->Klass()->Name(),
     CreatePyString(" object at "), Identity(args),
     CreatePyString(">")}
  ));
}

PyObjPtr Bool(const PyObjPtr& args) {
  CheckNativeFunctionArgumentsWithExpectedLength(args, 1);
  return args->as<PyList>()->GetItem(0)->boolean();
}

PyObjPtr KlassBool(const PyObjPtr& args) {
  CheckNativeFunctionArgumentsWithExpectedLength(args, 1);
  return CreatePyBoolean(true);
}

PyObjPtr Identity(const PyObjPtr& args) {
  CheckNativeFunctionArgumentsWithExpectedLength(args, 1);
  auto obj = args->as<PyList>()->GetItem(0);
  return CreatePyString(
    Collections::CreateIntegerWithU64(reinterpret_cast<uint64_t>(obj.get()))
      .ToHexString()
  );
}

PyObjPtr CreatePyClass(const PyTypePtr& type) {
  return std::make_shared<PyObject>(type->Owner());
}

PyObjPtr GetBases(const PyObjPtr& args) {
  CheckNativeFunctionArgumentsWithExpectedLength(args, 1);
  return args->as<PyList>()->GetItem(0)->Klass()->Type()->Owner()->Super();
}
PyObjPtr GetMro(const PyObjPtr& args) {
  CheckNativeFunctionArgumentsWithExpectedLength(args, 1);
  return args->as<PyList>()->GetItem(0)->Klass()->Type()->Owner()->Mro();
}
PyObjPtr GetDict(const PyObjPtr& args) {
  CheckNativeFunctionArgumentsWithExpectedLength(args, 1);
  auto obj = args->as<PyList>()->GetItem(0);
  if (obj->is<PyType>()) {
    return obj->as<PyType>()->Owner()->Attributes();
  }
  return obj->Attributes();
}
PyListPtr ComputeMro(const PyTypePtr& type) {
  if (type->Owner()->Mro() != nullptr) {
    // DebugPrint(StringConcat(CreatePyList(
    //   {CreatePyString("Mro for "), type->Owner()->Name(),
    //    CreatePyString(" already computed: "), type->Owner()->Mro()->str()}
    // )));
    return type->Owner()->Mro();
  }
  // DebugPrint(StringConcat(CreatePyList(
  //   {CreatePyString("Computing Mro for "), type->Owner()->Name(),
  //    CreatePyString(" with super: "), type->Owner()->Super()->str()}
  // )));
  auto bases = type->Owner()->Super();
  PyListPtr mros = CreatePyList({})->as<PyList>();
  for (Index i = 0; i < bases->Length(); i++) {
    auto base = bases->GetItem(i)->as<PyType>();
    mros->Append(ComputeMro(base));
  }
  // DebugPrint(StringConcat(
  //   CreatePyList({CreatePyString("Mros needed to merge: "), mros->str()})
  // ));
  auto mro = MergeMro(mros);
  // DebugPrint(
  //   StringConcat(CreatePyList({CreatePyString("Merged Mro: "), mro->str()}))
  // );
  mro = CreatePyList({type})->as<PyList>()->Add(mro)->as<PyList>();
  // DebugPrint(StringConcat(CreatePyList(
  //   {CreatePyString("Mro for "), type->Owner()->Name(), CreatePyString(": "),
  //    mro->str()}
  // )));
  return mro;
}

void CleanMros(const PyListPtr& mros) {
  for (Index i = 0; i < mros->Length();) {
    if (mros->GetItem(i)->as<PyList>()->Length() == 0) {
      mros->RemoveAt(i);
    } else {
      i++;
    }
  }
}

PyListPtr MergeMro(const PyListPtr& mros) {
  if (mros->Length() == 0) {
    return CreatePyList({})->as<PyList>();
  }
  PyListPtr result = CreatePyList({})->as<PyList>();
  CleanMros(mros);
  while (mros->Length() > 1) {
    // DebugPrint(StringConcat(
    //   CreatePyList({CreatePyString("Mros to merge: "), mros->str()})
    // ));
    bool notFindBase = true;
    for (Index i = 0; i < mros->Length() && notFindBase; i++) {
      auto head = mros->GetItem(i)->as<PyList>()->GetItem(0)->as<PyType>();
      bool couldPlaceAhead = CouldTypePlaceAhead(mros, head, i);
      if (!couldPlaceAhead) {
        continue;
      }
      notFindBase = false;
      result->Append(head);
      // DebugPrint(StringConcat(
      //   CreatePyList({CreatePyString("choose base: "),
      //   head->Owner()->Name()})
      // ));
      // DebugPrint(StringConcat(
      //   CreatePyList({CreatePyString("Mros merging: "), mros->str()})
      // ));
      for (Index j = 0; j < mros->Length(); j++) {
        if (i == j) {
          continue;
        }
        if (IsTrue(mros->GetItem(j)->as<PyList>()->GetItem(0)->eq(head))) {
          mros->GetItem(j)->as<PyList>()->RemoveAt(0);
          if (mros->GetItem(j)->as<PyList>()->Length() == 0) {
            mros->RemoveAt(j);
          }
        }
      }
      mros->GetItem(i)->as<PyList>()->RemoveAt(0);
      if (mros->GetItem(i)->as<PyList>()->Length() == 0) {
        mros->RemoveAt(i);
      }
    }
    // DebugPrint(StringConcat(
    //   CreatePyList({CreatePyString("Mros after merge: "), mros->str()})
    // ));
  }
  if (mros->Length() == 0) {
    return result;
  }
  auto last_mro = mros->GetItem(0)->as<PyList>();
  for (Index i = 0; i < last_mro->Length(); i++) {
    result->Append(last_mro->GetItem(i));
  }
  return result;
}

bool FirstOrNotInMro(const PyListPtr& mro, const PyTypePtr& type) {
  auto head = mro->GetItem(0)->as<PyType>();
  if (IsTrue(head->eq(type))) {
    return true;
  }
  for (Index i = 1; i < mro->Length(); i++) {
    if (IsTrue(mro->GetItem(i)->as<PyType>()->eq(type))) {
      return false;
    }
  }
  return true;
}

bool CouldTypePlaceAhead(
  const PyListPtr& mros,
  const PyTypePtr& type,
  Index ignore
) {
  for (Index i = 0; i < mros->Length(); i++) {
    if (i == ignore) {
      continue;
    }
    if (!FirstOrNotInMro(mros->GetItem(i)->as<PyList>(), type)) {
      return false;
    }
  }
  return true;
}

void DebugPrint(const PyObjPtr& obj) {
  if (obj->is<PyString>()) {
    std::cout << obj->as<PyString>()->ToCppString() << std::endl;
    return;
  }
  std::cout << obj->str()->as<PyString>()->ToCppString() << std::endl;
}

PyObjPtr Print(const PyObjPtr& args) {
  CheckNativeFunctionArguments(args);
  auto argList = args->as<PyList>();
  for (Index i = 0; i < argList->Length(); i++) {
    auto arg = argList->GetItem(i);
    arg->str()->as<PyString>()->Print();
    if (i < argList->Length() - 1) {
      CreatePyString(" ")->as<PyString>()->Print();
    }
  }
  CreatePyString("\n")->as<PyString>()->Print();
  return CreatePyNone();
}

PyObjPtr Len(const PyObjPtr& args) {
  CheckNativeFunctionArgumentsWithExpectedLength(args, 1);
  auto value = args->as<PyList>()->GetItem(0);
  return value->len();
}

PyObjPtr Next(const PyObjPtr& args) {
  CheckNativeFunctionArgumentsWithExpectedLength(args, 1);
  auto value = args->as<PyList>()->GetItem(0);
  return value->next();
}

Object::PyObjPtr RandInt(const Object::PyObjPtr& args) {
  CheckNativeFunctionArgumentsWithExpectedLength(args, 2);
  auto argList = args->as<PyList>();
  auto left = argList->GetItem(0)->as<PyInteger>();
  auto right = argList->GetItem(1)->as<PyInteger>();
  if (IsTrue(left->ge(Object::CreatePyInteger(0x7fffffff))) ||
      IsTrue(right->ge(Object::CreatePyInteger(0x7fffffff))) ||
      IsTrue(left->ge(right))) {
    left->str()->as<PyString>()->PrintLine();
    right->str()->as<PyString>()->PrintLine();
    throw std::runtime_error(
      "RandInt function need left argument less than right argument"
    );
  }
  auto cppLeft = left->ToU64();
  auto cppRight = right->ToU64();
  std::random_device rd;   // 随机数设备，用于生成种子
  std::mt19937 gen(rd());  // 使用 Mersenne Twister 算法生成随机数
  std::uniform_int_distribution<>
    dis(  // 生成 [cppLeft, cppRight] 之间的均匀分布
      static_cast<std::mt19937::result_type>(cppLeft),
      static_cast<std::mt19937::result_type>(cppRight)
    );

  auto result = dis(gen);
  return Object::CreatePyInteger(result);
}

Object::PyObjPtr Sleep(const Object::PyObjPtr& args) {
  CheckNativeFunctionArgumentsWithExpectedLength(args, 1);
  auto seconds = args->as<PyList>()->GetItem(0)->as<PyInteger>();
  if (IsTrue(seconds->lt(Object::CreatePyInteger(0)))) {
    seconds->str()->as<PyString>()->PrintLine();
    throw std::runtime_error("Sleep function need non-negative argument");
  }
  auto secondsValue = seconds->ToU64();
  std::this_thread::sleep_for(std::chrono::seconds(secondsValue));
  return Object::CreatePyNone();
}
Object::PyObjPtr Normal(const Object::PyObjPtr& args) {
  CheckNativeFunctionArgumentsWithExpectedLength(args, 3);
  auto argList = args->as<PyList>();
  auto loc = argList->GetItem(0)->as<PyFloat>()->Value();
  auto scale = argList->GetItem(1)->as<PyFloat>()->Value();
  std::random_device randomDevice;
  std::mt19937 gen(randomDevice());
  std::normal_distribution<> dis(loc, scale);
  auto size = argList->GetItem(2);
  if (size->is<PyInteger>()) {
    auto sizeValue = size->as<PyInteger>()->ToU64();
    auto result = CreatePyList(sizeValue)->as<PyList>();
    for (Index i = 0; i < sizeValue; i++) {
      result->SetItem(i, CreatePyFloat(dis(gen)));
    }
    return result;
  }
  if (size->is<PyList>()) {
    auto sizeList = size->as<PyList>();
    auto row = sizeList->GetItem(0)->as<PyInteger>()->ToU64();
    auto col = sizeList->GetItem(1)->as<PyInteger>()->ToU64();
    auto sizeValue = row * col;
    Collections::List<double> result(sizeValue);
    for (Index i = 0; i < sizeValue; i++) {
      result.Push(dis(gen));
    }
    return CreatePyMatrix(Collections::Matrix(row, col, result));
  }
  throw std::runtime_error("Normal function need integer or list argument");
}

Object::PyObjPtr Shuffle(const Object::PyObjPtr& args) {
  CheckNativeFunctionArgumentsWithExpectedLength(args, 1);
  auto argList = args->as<PyList>();
  auto arg = argList->GetItem(0);
  if (arg->is<PyList>()) {
    arg->as<PyList>()->Shuffle();
    return CreatePyNone();
  }
  if (arg->is<PyMatrix>()) {
    arg->as<PyMatrix>()->Shuffle();
    return CreatePyNone();
  }
  throw std::runtime_error("Shuffle function need list or matrix argument");
}

Object::PyObjPtr Input(const Object::PyObjPtr& args) {
  CheckNativeFunctionArguments(args);
  if (args->as<PyList>()->Length() == 1) {
    auto prompt = args->as<PyList>()->GetItem(0)->as<PyString>()->ToCppString();
    std::cout << prompt;
  }
  std::string input;
  std::cin >> input;
  return Object::CreatePyString(input);
}

void LoadClass(const PyStrPtr& name, const KlassPtr& klass) {
  klass->SetName(name);
  klass->SetAttributes(CreatePyDict());
  klass->SetType(CreatePyType(klass)->as<PyType>());
  klass->SetSuper(CreatePyList({PyObject::Instance()}));
  klass->SetMro(
    CreatePyList({CreatePyType(klass), CreatePyType(ObjectKlass::Self())})
  );
  klass->SetNative();
}

void ConfigureBasicAttributes(const KlassPtr& klass) {
  klass->AddAttribute(
    CreatePyString("__name__")->as<PyString>(), klass->Name()
  );
  klass->AddAttribute(
    CreatePyString("__class__")->as<PyString>(), klass->Type()
  );
  klass->AddAttribute(
    CreatePyString("__bases__")->as<PyString>(), CreatePyIife(GetBases)
  );
  klass->AddAttribute(
    CreatePyString("__mro__")->as<PyString>(), CreatePyIife(GetMro)
  );
  klass->AddAttribute(
    CreatePyString("__dict__")->as<PyString>(), CreatePyIife(GetDict)
  );
}

PyObjPtr GetAttr(const PyObjPtr& obj, const PyStrPtr& attrName) noexcept {
  if (obj->Klass()->Attributes()->Contains(attrName)) {
    return obj->Klass()->Attributes()->Get(attrName);
  }
  if (obj->Klass()->Super()->Length() == 0 &&
      obj->Klass() == ObjectKlass::Self()) {
    return nullptr;
  }
  for (Index i = 0; i < obj->Klass()->Mro()->Length(); i++) {
    auto klass = obj->Klass()->Mro()->GetItem(i)->as<PyType>()->Owner();
    if (klass->Attributes()->Contains(attrName)) {
      return klass->Attributes()->Get(attrName);
    }
  }
  return nullptr;
}

PyObjPtr AttrWrapper(const PyObjPtr& obj, const PyObjPtr& attr) {
  if (attr->is<PyNativeFunction>()) {
    return CreatePyMethod(obj, attr);
  }
  if (attr->is<PyFunction>()) {
    return CreatePyMethod(obj, attr);
  }
  if (attr->is<PyIife>()) {
    auto reuslt = attr->as<PyIife>()->Call(CreatePyList({obj}));
    return reuslt;
  }
  return attr;
}
}  // namespace torchlight::Object