#include "Object/Core/CoreHelper.h"
#include "Object/Container/PyDictionary.h"
#include "Object/Container/PyList.h"
#include "Object/Core/PyBoolean.h"
#include "Object/Core/PyNone.h"
#include "Object/Core/PyType.h"
#include "Object/Function/PyIife.h"
#include "Object/Iterator/Iterator.h"
#include "Object/Iterator/IteratorHelper.h"
#include "Object/Iterator/PyGenerator.h"
#include "Object/Number/PyFloat.h"
#include "Object/Number/PyInteger.h"
#include "Object/PyMatrix.h"
#include "Runtime/Interpreter.h"

namespace torchlight::Object {
void LoadClass(const PyStrPtr& name, const KlassPtr& klass) {
  klass->SetName(name);
  klass->SetAttributes(CreatePyDict()->as<PyDictionary>());
  klass->SetType(CreatePyType(klass)->as<PyType>());
  auto objectType = CreatePyType(ObjectKlass::Self());
  klass->SetSuper(CreatePyList({objectType})->as<PyList>());
  klass->SetMro(CreatePyList({CreatePyType(klass), objectType})->as<PyList>());
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

void InitKlass(const Object::PyStrPtr& name, const Object::KlassPtr& klass) {
  LoadClass(name, klass);
  ConfigureBasicAttributes(klass);
}

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

PyObjPtr GetAttr(const PyObjPtr& obj, const PyStrPtr& attrName) noexcept {
  if (obj->Klass()->Attributes()->Contains(attrName)) {
    return obj->Klass()->Attributes()->Get(attrName);
  }
  if (obj->Klass()->Super()->Length() == 0 && obj->Klass() == ObjectKlass::Self()) {
    return nullptr;
  }
  for (Index i = 0; i < obj->Klass()->Mro()->Length(); i++) {
    auto klass = obj->Klass()->Mro()->GetItem(i)->as<PyType>();
    if (klass->Owner()->Attributes()->Contains(attrName)) {
      return klass->Owner()->Attributes()->Get(attrName);
    }
  }
  return nullptr;
}

PyObjPtr BindSelf(const PyObjPtr& obj, const PyObjPtr& attr) {
  if (attr->is(NativeFunctionKlass::Self())) {
    return CreatePyMethod(obj, attr);
  }
  if (attr->is(FunctionKlass::Self())) {
    return CreatePyMethod(obj, attr);
  }
  if (attr->is(IifeKlass::Self())) {
    return attr->as<PyIife>()->Call(CreatePyList({obj}));
  }
  return attr;
}

void CacheAttr(
  const Object::PyObjPtr& obj,
  const Object::PyObjPtr& key,
  const Object::PyObjPtr& attr
) {
  if (attr->is(FunctionKlass::Self())) {
    obj->Methods()->Put(key, attr);
    return;
  }
  if (attr->is(NativeFunctionKlass::Self())) {
    obj->Methods()->Put(key, attr);
    return;
  }
  if (attr->is(IifeKlass::Self())) {
    obj->Attributes()->Put(key, attr);
    return;
  }
  obj->Attributes()->Put(key, attr);
}

PyObjPtr GetBases(const PyObjPtr& args) {
  CheckNativeFunctionArgumentsWithExpectedLength(args, 1);
  return args->as<PyList>()->GetItem(0)->Klass()->Type()->Owner()->Super();
}
PyObjPtr GetMro(const PyObjPtr& args) {
  CheckNativeFunctionArgumentsWithExpectedLength(args, 1);
  return args->as<PyList>()->GetItem(0)->as<PyType>()->Owner()->Mro();
}
PyObjPtr GetDict(const PyObjPtr& args) {
  CheckNativeFunctionArgumentsWithExpectedLength(args, 1);
  auto obj = args->as<PyList>()->GetItem(0);
  return obj->Attributes()->Add(obj->Methods())->as<PyDictionary>();
}
PyListPtr ComputeMro(const PyTypePtr& type) {
  auto oldMro = type->Owner()->Mro();
  if (oldMro) {
    //    Function::DebugPrint(StringConcat(CreatePyList(
    //      {CreatePyString("Mro for "), type->Owner()->Name(),
    //       CreatePyString(" already computed: "), oldMro->str()}
    //    )));
    return oldMro;
  }
  //  Function::DebugPrint(StringConcat(CreatePyList(
  //    {CreatePyString("Computing Mro for "), type->Owner()->Name(),
  //     CreatePyString(" with super: "), type->Owner()->Super()->str()}
  //  )));
  auto bases = type->Owner()->Super();
  PyListPtr mros = CreatePyList({})->as<PyList>();
  for (Index i = 0; i < bases->Length(); i++) {
    auto base = bases->GetItem(i)->as<PyType>();
    auto mro = base->Owner()->Mro();
    mros->Append(mro->Copy());
  }
  //  Function::DebugPrint(StringConcat(
  //    CreatePyList({CreatePyString("Mros needed to merge: "), mros->str()})
  //  ));
  //  ForEach(mros, [&](const PyObjPtr& mro) {
  //    mro->str()->as<PyString>()->Print();
  //  });
  //  CreatePyString("")->as<PyString>()->PrintLine();
  auto mro = MergeMro(mros);
  //  Function::DebugPrint(
  //    StringConcat(CreatePyList({CreatePyString("Merged Mro: "), mro->str()}))
  //  );
  //  ForEach(mros, [&](const PyObjPtr& mro) {
  //    mro->str()->as<PyString>()->Print();
  //  });
  //  CreatePyString("")->as<PyString>()->PrintLine();
  mro = CreatePyList({type})->as<PyList>()->Add(mro)->as<PyList>();
  //  Function::DebugPrint(StringConcat(CreatePyList(
  //    {CreatePyString("Mro for "), type->Owner()->Name(), CreatePyString(":"),
  //     mro->str()}
  //  )));
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
    //    Function::DebugPrint(StringConcat(
    //      CreatePyList({CreatePyString("Mros to merge: "), mros->str()})
    //    ));
    bool notFindBase = true;
    for (Index i = 0; i < mros->Length() && notFindBase; i++) {
      auto head = mros->GetItem(i)->as<PyList>()->GetItem(0)->as<PyType>();
      bool couldPlaceAhead = CouldTypePlaceAhead(mros, head, i);
      if (!couldPlaceAhead) {
        continue;
      }
      notFindBase = false;
      result->Append(head);
      //      Function::DebugPrint(StringConcat(
      //        CreatePyList({CreatePyString("choose base: "),
      //        head->Owner()->Name()})
      //      ));
      //      Function::DebugPrint(StringConcat(
      //        CreatePyList({CreatePyString("Mros merging: "), mros->str()})
      //      ));
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
    //    Function::DebugPrint(StringConcat(
    //      CreatePyList({CreatePyString("Mros after merge: "), mros->str()})
    //    ));
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

PyObjPtr KlassStr(const PyObjPtr& args) {
  return StringConcat(CreatePyList(
    {CreatePyString("<"), args->as<PyList>()->GetItem(0)->Klass()->Name(),
     CreatePyString(" object at "), Function::Identity(args),
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
     CreatePyString(" object at "), Function::Identity(args),
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

KlassPtr CreatePyKlass(
  const PyStrPtr& name,
  const PyDictPtr& attributes,
  const PyListPtr& super
) {
  auto klass = std::make_shared<Klass>();
  auto type = CreatePyType(klass)->as<PyType>();
  klass->SetName(name);
  klass->SetAttributes(attributes);
  klass->SetType(type);
  klass->SetSuper(super);
  klass->SetMro(ComputeMro(type));
  ConfigureBasicAttributes(klass);
  return klass;
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

void BasicKlassLoad() {
  StringKlass::Self()->Initialize();
  IntegerKlass::Self()->Initialize();
  ListKlass::Self()->Initialize();
  DictionaryKlass::Self()->Initialize();
  TypeKlass::Self()->Initialize();
  BooleanKlass::Self()->Initialize();

  NativeFunctionKlass::Self()->Initialize();
  IifeKlass::Self()->Initialize();
  ListIteratorKlass::Self()->Initialize();
  IterDoneKlass::Self()->Initialize();
}

void NativeClassLoad() {
  NoneKlass::Self()->Initialize();
  ObjectKlass::Self()->Initialize();
  FunctionKlass::Self()->Initialize();
  MethodKlass::Self()->Initialize();
  ListReverseIteratorKlass::Self()->Initialize();
  StringIteratorKlass::Self()->Initialize();
  DictItemIteratorKlass::Self()->Initialize();
  GeneratorKlass::Self()->Initialize();
  FloatKlass::Self()->Initialize();
  CodeKlass::Self()->Initialize();
  FrameKlass::Self()->Initialize();
  InstKlass::Self()->Initialize();
  BytesKlass::Self()->Initialize();
  MatrixKlass::Self()->Initialize();
  SliceKlass::Self()->Initialize();
}

}  // namespace torchlight::Object