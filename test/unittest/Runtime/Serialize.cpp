#include <memory>
#include "../test_default.h"

#include "Function/ObjectHelper.h"
#include "Object/Container/PyDictionary.h"
#include "Object/Container/PyList.h"
#include "Object/Number/PyFloat.h"
#include "Object/Number/PyInteger.h"
#include "Object/String/PyBytes.h"
#include "Object/String/PyString.h"
#include "Runtime/Genesis.h"

namespace torchlight {

class SerializeTest : public ::testing::Test {
 protected:
  void SetUp() override {
    globals =
      std::dynamic_pointer_cast<Object::PyDictionary>(Runtime::Genesis());
  }

  void TearDown() override {
    // 清理代码（如果需要）
  }

  Object::PyDictPtr globals;
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
  Object::Invoke(emptyList, Object::CreatePyString("print"), {});
  Object::Invoke(emptyList, Object::CreatePyString("append"), {str});
  Object::Invoke(emptyList, Object::CreatePyString("append"), {integer});
  Object::Invoke(emptyList, Object::CreatePyString("append"), {floating});
  Object::Invoke(emptyList, Object::CreatePyString("print"), {});
  // print->Call(Object::CreatePyList({str->repr()}));
  // print->Call(Object::CreatePyList({str->str()}));
  // print->Call(Object::CreatePyList({integer->repr()}));
  // print->Call(Object::CreatePyList({integer->str()}));
  // print->Call(Object::CreatePyList({floating->repr()}));
  // print->Call(Object::CreatePyList({floating->str()}));
  // print->Call(Object::CreatePyList({list->repr()}));
  // print->Call(Object::CreatePyList({list->str()}));
  // print->Call(Object::CreatePyList({bytes->repr()}));
  // print->Call(Object::CreatePyList({bytes->str()}));
  // print->Call(Object::CreatePyList({emptyBytes->repr()}));
  // print->Call(Object::CreatePyList({emptyBytes->str()}));
  // print->Call(Object::CreatePyList({emptyList->repr()}));
  // print->Call(Object::CreatePyList({emptyList->str()}));
  // print->Call(Object::CreatePyList({obj->repr()}));
  // print->Call(Object::CreatePyList({obj->str()}));
  // print->Call(Object::CreatePyList({dict->repr()}));
  // print->Call(Object::CreatePyList({dict->str()}));
  // print->Call(
  //   Object::CreatePyList({str->getattr(Object::CreatePyString("__class__"))})
  // );
  // print->Call(
  //   Object::CreatePyList({str->getattr(Object::CreatePyString("__class__"))->getattr(Object::CreatePyString("__name__"))})
  // );
  //   Object::PyObjPtr serialized = dict->_serialize_();
  // PyBytesPtr bytesObj = std::dynamic_pointer_cast<PyBytes>(serialized);
  // Bytes bytesData = bytesObj->Value();
  // List<Byte> bytesList = bytesData.Value();
  // auto iter = Iterator<Byte>::Begin(bytesList);
  // Object::PyObjPtr deserialized = ReadObject(iter);
  // EXPECT_EQ(obj->eq(deserialized), Object::CreatePyBoolean(true));
}

}  // namespace torchlight