#include "test_default.h"

#include "collections/impl/String.h"
#include "object/PyDictionary.h"
#include "object/PyString.h"

using torchlight::collections::CreateStringWithCString;
using torchlight::object::CreatePyDict;
using torchlight::object::CreatePyString;

TEST(Map, Basic) {
  auto map = CreatePyDict();
  map->setitem(
    CreatePyString(CreateStringWithCString("k1")),
    CreatePyString(CreateStringWithCString("v1"))
  );
  map->setitem(
    CreatePyString(CreateStringWithCString("k2")),
    CreatePyString(CreateStringWithCString("v2"))
  );
  map->setitem(
    CreatePyString(CreateStringWithCString("k3")),
    CreatePyString(CreateStringWithCString("v3"))
  );
  print(map);
  map->delitem(CreatePyString(CreateStringWithCString("k2")));
  print(map);
}