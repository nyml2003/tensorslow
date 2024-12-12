#ifndef TORCHLIGHT_OBJECT_COMMON_H
#define TORCHLIGHT_OBJECT_COMMON_H

#include <memory>

namespace torchlight::object {

class Klass;

using KlassPtr = std::shared_ptr<Klass>;

class IntegerKlass;

class FloatKlass;

class BooleanKlass;

class StringKlass;

class ListKlass;

class DictionaryKlass;

class TupleKlass;

class TypeKlass;

class NoneKlass;

class NotImplementedKlass;

class PyObject;

using PyObjPtr = std::shared_ptr<PyObject>;

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

class PyTuple;

using PyTuplePtr = std::shared_ptr<PyTuple>;

class PyType;

using PyTypePtr = std::shared_ptr<PyType>;

class PyNone;

using PyNonePtr = std::shared_ptr<PyNone>;

class PyNotImplemented;

using PyNotImplementedPtr = std::shared_ptr<PyNotImplemented>;

class PyBytes;

using PyBytesPtr = std::shared_ptr<PyBytes>;
}  // namespace torchlight::object

#endif  // TORCHLIGHT_OBJECT_COMMON_H
