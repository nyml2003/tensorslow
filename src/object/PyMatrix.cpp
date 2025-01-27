#include "Function/PyNativeFunction.h"
#include "Object/PyDictionary.h"
#include "Object/PyMatrix.h"
#include "Object/PyString.h"
#include "Object/PyType.h"

namespace torchlight::Object {

PyMatrix::PyMatrix(Collections::Matrix matrix)
  : PyObject(MatrixKlass::Self()), matrix(std::move(matrix)) {}

Collections::Matrix PyMatrix::Value() const {
  return matrix;
}

MatrixKlass::MatrixKlass() = default;

void MatrixKlass::Initialize() {
  SetType(CreatePyType(Self()));
  SetName(CreatePyString("matrix"));
  Collections::Map<PyObjPtr, PyObjPtr> methods;
  methods.Put(CreatePyString("transpose"), CreatePyNativeFunction(Transpose));

  Klass::Initialize();
}

KlassPtr MatrixKlass::Self() {
  static KlassPtr instance = std::make_shared<MatrixKlass>();
  return instance;
}

PyObjPtr Transpose(PyObjPtr args) {
  if (args->Klass() != MatrixKlass::Self()) {
    throw std::runtime_error("Transpose(): args is not a matrix");
  }
  auto matrix = std::dynamic_pointer_cast<PyMatrix>(args);
  return std::make_shared<PyMatrix>(matrix->Value().Transpose());
}

PyObjPtr MatrixKlass::repr(PyObjPtr obj) {
  if (obj->Klass() != Self()) {
    throw std::runtime_error("PyMatrix::repr(): obj is not a matrix object");
  }
  auto matrix = std::dynamic_pointer_cast<PyMatrix>(obj);
  return CreatePyString(matrix->Value().ToString());
}

PyObjPtr MatrixKlass::matmul(PyObjPtr lhs, PyObjPtr rhs) {
  if (lhs->Klass() != Self() || rhs->Klass() != Self()) {
    ThrowUnsupportedOperandError(lhs, rhs, CreatePyString("__matmul__"));
  }
  auto left = std::dynamic_pointer_cast<PyMatrix>(lhs);
  auto right = std::dynamic_pointer_cast<PyMatrix>(rhs);
  return std::make_shared<PyMatrix>(left->Value().MatrixMultiply(right->Value())
  );
}

PyObjPtr Matrix(PyObjPtr args) {
  if (args->Klass() != ListKlass::Self()) {
    throw std::runtime_error("Matrix(): args is not a list");
  }
  auto list = std::dynamic_pointer_cast<PyList>(args);
  Collections::List<PyObjPtr> rawList = list->Value();
  Collections::List<Collections::List<double>> matrix;
  return std::make_shared<PyMatrix>(Collections::Matrix(matrix));
}
}  // namespace torchlight::Object