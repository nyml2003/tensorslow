#include "../test_default.h"

#include "Collections/Bytes.h"
#include "Collections/Iterator.h"
#include "Collections/StringHelper.h"
#include "Object/Common.h"
#include "Object/PyBoolean.h"
#include "Object/PyBytes.h"
#include "Object/PyFloat.h"
#include "Object/PyInteger.h"
#include "Object/PyList.h"
#include "Object/PyString.h"
#include "Runtime/Serialize.h"

using namespace torchlight;
using namespace torchlight::Object;
using namespace torchlight::Collections;
using namespace torchlight::Runtime;

TEST(Serialize, SerializeEtDeserialize) {
  PyStrPtr str = CreatePyString(CreateStringWithCString("你好,世界！"));
  PyIntPtr integer = CreatePyInteger(42);
  PyFloatPtr floating = CreatePyFloat(3.14);
  PyListPtr list = CreatePyList(List<PyObjPtr>{str,integer, floating}, 3);
  PyBytesPtr bytes =
    CreatePyBytes(Bytes(List<Byte>({'H', 'e', 'l', 'l', 'o'})));
  PyBytesPtr emptyBytes = CreatePyBytes();
  PyListPtr emptyList = CreatePyList(0);
  PyObjPtr obj = CreatePyList(
    List<PyObjPtr>{str, integer, floating, list, bytes, emptyBytes, emptyList},
    7
  );
  PyObjPtr serialized = obj->_serialize_();
  PyBytesPtr bytesObj = std::dynamic_pointer_cast<PyBytes>(serialized);
  Bytes bytesData = bytesObj->Value();
  List<Byte> bytesList = bytesData.Value();
  auto iter = Iterator<Byte>::Begin(bytesList);
  PyObjPtr deserialized = ReadObject(iter);
  EXPECT_EQ(obj->eq(deserialized), CreatePyBoolean(true));
}