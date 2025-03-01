#ifndef TORCHLIGHT_OBJECT_COMMON_H
#define TORCHLIGHT_OBJECT_COMMON_H

#include <memory>

namespace torchlight::Object {

class Klass;
using KlassPtr = std::shared_ptr<Klass>;

class PyObject;
using PyObjPtr = std::shared_ptr<PyObject>;
class PyString;
using PyStrPtr = std::shared_ptr<PyString>;
class PyList;
using PyListPtr = std::shared_ptr<PyList>;
class PyDictionary;
using PyDictPtr = std::shared_ptr<PyDictionary>;
class PyType;
using PyTypePtr = std::shared_ptr<PyType>;

}  // namespace torchlight::Object

#endif  // TORCHLIGHT_OBJECT_COMMON_H
