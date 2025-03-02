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
#include "Object/PyList.h"
#include "Object/PyNone.h"
#include "Object/PyObject.h"
#include "Object/PyString.h"
#include "Object/PyType.h"
#include "Runtime/PyFrame.h"
namespace torchlight::Object {

PyObjPtr Invoke(
  const PyObjPtr& obj,
  const PyObjPtr& methodName,
  std::initializer_list<PyObjPtr> arguments
) {
  if (!obj->Klass()->Attributes()->Contains(methodName)) {
    return CreatePyNone();
  }
  Collections::List<PyObjPtr> argumentsList(arguments);
  argumentsList.Unshift(obj);
  PyListPtr args =
    std::dynamic_pointer_cast<PyList>(CreatePyList(argumentsList));
  auto method =
    std::dynamic_pointer_cast<Object::PyMethod>(obj->getattr(methodName))
      ->Method();
  auto isNative = std::dynamic_pointer_cast<PyNativeFunction>(method);
  if (isNative) {
    return isNative->Call(args);
  }
  return Runtime::CreateFrameWithPyFunction(
           std::dynamic_pointer_cast<PyFunction>(method), args
  )
    ->EvalWithDestory();
}

void BasicKlassLoad() {
  Object::StringKlass::Initialize();
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
  auto iterable = std::dynamic_pointer_cast<IIterator>(iter);
  if (!iterable) {
    throw std::runtime_error("object is not iterable");
  }
  auto value = iter->next();
  while (!value->is<IterDone>()) {
    func(value, iterable->CurrentIndex(), obj);
    value = iter->next();
  }
}

PyObjPtr Identity(const PyObjPtr& obj) {
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
PyListPtr ComputeMro(const PyTypePtr& type) {
  if (type->Owner()->Mro() != nullptr) {
    return type->Owner()->Mro();
  }
  // DebugPrint(StringConcat(CreatePyList(
  //   {CreatePyString("Computing Mro for "), type->Owner()->Name(),
  //    CreatePyString(" with super: "), type->Owner()->Super()->str()}
  // )));
  auto bases = type->Owner()->Super();
  PyListPtr mros = CreatePyList({})->as<PyList>();
  for (Index i = 0; i < bases->Length(); i++) {
    auto base = bases->GetItem(i)->as<PyObject>()->Klass()->Type();
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
  DebugPrint(StringConcat(CreatePyList(
    {CreatePyString("Mro for "), type->Owner()->Name(), CreatePyString(": "),
     mro->str()}
  )));
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
  obj->str()->as<PyString>()->PrintLine();
}

PyObjPtr Print(const PyObjPtr& args) {
  CheckNativeFunctionArguments(args);
  auto argList = args->as<PyList>();
  CreatePyString(" ")->as<PyString>()->Join(argList)->PrintLine();
  return CreatePyNone();
}

PyObjPtr Len(const PyObjPtr& args) {
  CheckNativeFunctionArgumentsWithExpectedLength(args, 1);
  auto value = args->as<PyList>()->GetItem(0);
  return value->len();
}

void LoadClass(const PyStrPtr& name, const KlassPtr& klass) {
  klass->SetName(name);
  klass->SetAttributes(CreatePyDict());
  klass->SetType(CreatePyType(klass));
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
    CreatePyString("__repr__")->as<PyString>(),
    CreatePyNativeFunction(KlassRepr)
  );
  klass->AddAttribute(
    CreatePyString("__bases__")->as<PyString>(), CreatePyIife(GetBases)
  );
  klass->AddAttribute(
    CreatePyString("__mro__")->as<PyString>(), CreatePyIife(GetMro)
  );
}

PyObjPtr KlassRepr(const PyObjPtr& args) {
  CheckNativeFunctionArgumentsWithExpectedLength(args, 1);
  auto obj = args->as<PyList>()->GetItem(0);
  return CreatePyString("<")
    ->add(obj->getattr(CreatePyString("__name__")->str()))
    ->add(CreatePyString(" object at ")
            ->add(CreatePyString(Collections::CreateIntegerWithU64(
                                   reinterpret_cast<uint64_t>(obj.get())
            )
                                   .ToHexString())))
    ->add(CreatePyString(">"));
}

}  // namespace torchlight::Object