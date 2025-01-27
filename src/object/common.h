#ifndef TORCHLIGHT_OBJECT_COMMON_H
#define TORCHLIGHT_OBJECT_COMMON_H

#include <memory>

namespace torchlight::Object {

class Klass;

using KlassPtr = std::shared_ptr<Klass>;

class IntegerKlass;

class FloatKlass;

class BooleanKlass;

class StringKlass;

class ListKlass;

class DictionaryKlass;

class NoneKlass;

class BytesKlass;

class NotImplementKlass;

class TypeKlass;

class PyObject;

using PyObjPtr = std::shared_ptr<PyObject>;

class PyNotNotImplement;

using PyNotImplementedPtr = std::shared_ptr<PyNotNotImplement>;

class PyInteger;

using PyIntPtr = std::shared_ptr<PyInteger>;

class PyFloat;

using PyFloatPtr = std::shared_ptr<PyFloat>;

class PyBoolean;

using PyBoolPtr = std::shared_ptr<PyBoolean>;

class PyString;

using PyStrPtr = std::shared_ptr<PyString>;

class PyList;

using PyListPtr = std::shared_ptr<PyList>;

class PyDictionary;

using PyDictPtr = std::shared_ptr<PyDictionary>;

class PyNone;

using PyNonePtr = std::shared_ptr<PyNone>;

class PyBytes;

using PyBytesPtr = std::shared_ptr<PyBytes>;

class PyType;

using PyTypePtr = std::shared_ptr<PyType>;

}  // namespace torchlight::Object

#endif  // TORCHLIGHT_OBJECT_COMMON_H
