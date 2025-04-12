#include <memory>
#include "../test_default.h"

#include "Collections/Iterator.h"
#include "Function/BuiltinFunction.h"
#include "Object/Container/PyDictionary.h"
#include "Object/Container/PyList.h"
#include "Object/Core/PyBoolean.h"
#include "Object/Function/PyFunction.h"
#include "Object/Function/PyNativeFunction.h"
#include "Object/Number/PyFloat.h"
#include "Object/Number/PyInteger.h"
#include "Object/String/PyBytes.h"
#include "Object/String/PyString.h"
#include "Runtime/Genesis.h"
#include "Runtime/Serialize.h"

namespace torchlight {

class SerializeTest : public ::testing::Test {
 protected:
  void SetUp() override {
    globals =
      std::dynamic_pointer_cast<Object::PyDictionary>(Runtime::Genesis());
    Object::LoadBootstrapClasses();
    Object::LoadRuntimeSupportClasses();
    print = globals->getitem(Object::CreatePyString("print"))
              ->as<Object::PyNativeFunction>();
  }

  void TearDown() override {
    // 清理代码（如果需要）
  }

  Object::PyDictPtr globals;
  Object::PyNativeFunctionPtr print;
};

TEST_F(SerializeTest, SerializeEtDeserialize) {
  Object::PyObjPtr str = Object::CreatePyString("你好,世界！");
  Object::PyObjPtr integer = Object::CreatePyInteger(42);
  Object::PyObjPtr floating = Object::CreatePyFloat(3.14);
  Object::PyObjPtr list = Object::CreatePyList({str, integer, floating});
  Object::PyObjPtr bytes =
    Object::CreatePyBytes(Collections::Bytes({'H', 'e', 'l', 'l', 'o'}));
  Object::PyObjPtr emptyBytes = Object::CreatePyBytes();
  Object::PyObjPtr emptyList = Object::CreatePyList(0);
  Object::PyObjPtr obj = Object::CreatePyList(
    {str, integer, floating, list, bytes, emptyBytes, emptyList}
  );
  Object::PyObjPtr dict = Object::CreatePyDict();
  dict->setitem(Object::CreatePyString("str"), str);
  dict->setitem(Object::CreatePyString("integer"), integer);
  dict->setitem(Object::CreatePyString("floating"), floating);
  dict->setitem(Object::CreatePyString("list"), list);
  emptyList->str()->as<Object::PyString>()->PrintLine();
  Object::Invoke(
    emptyList, Object::CreatePyString("append"), Object::CreatePyList({str})
  );
  Object::Invoke(
    emptyList, Object::CreatePyString("append"), Object::CreatePyList({integer})
  );
  Object::Invoke(
    emptyList, Object::CreatePyString("append"),
    Object::CreatePyList({floating})
  );
  emptyList->str()->as<Object::PyString>()->PrintLine();
  print->Call(Object::CreatePyList({str->repr()}));
  print->Call(Object::CreatePyList({str->str()}));
  print->Call(Object::CreatePyList({integer->repr()}));
  print->Call(Object::CreatePyList({integer->str()}));
  print->Call(Object::CreatePyList({floating->repr()}));
  print->Call(Object::CreatePyList({floating->str()}));
  print->Call(Object::CreatePyList({list->repr()}));
  print->Call(Object::CreatePyList({list->str()}));
  print->Call(Object::CreatePyList({bytes->repr()}));
  print->Call(Object::CreatePyList({bytes->str()}));
  print->Call(Object::CreatePyList({emptyBytes->repr()}));
  print->Call(Object::CreatePyList({emptyBytes->str()}));
  print->Call(Object::CreatePyList({emptyList->repr()}));
  print->Call(Object::CreatePyList({emptyList->str()}));
  print->Call(Object::CreatePyList({obj->repr()}));
  print->Call(Object::CreatePyList({obj->str()}));
  print->Call(Object::CreatePyList({dict->repr()}));
  print->Call(Object::CreatePyList({dict->str()}));
  print->Call(
    Object::CreatePyList({str->getattr(Object::CreatePyString("__class__"))})
  );
  print->Call(
    Object::CreatePyList({str->getattr(Object::CreatePyString("__class__"))
                            ->getattr(Object::CreatePyString("__name__"))})
  );
  Object::PyObjPtr serialized = obj->_serialize_();
  Object::PyBytesPtr bytesObj =
    std::dynamic_pointer_cast<Object::PyBytes>(serialized);
  Collections::Bytes bytesData = bytesObj->Value();
  Collections::List<Byte> bytesList = bytesData.Value();
  auto iter = Collections::Iterator<Byte>::Begin(bytesList);
  Object::PyObjPtr deserialized = Runtime::ReadObject(iter);
  EXPECT_EQ(obj->eq(deserialized), Object::CreatePyBoolean(true));
}

}  // namespace torchlight