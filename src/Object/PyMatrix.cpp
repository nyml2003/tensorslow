#include "Collections/Matrix.h"
#include "Function/PyIife.h"
#include "Function/PyNativeFunction.h"
#include "Object/Common.h"
#include "Object/PyDictionary.h"
#include "Object/PyFloat.h"
#include "Object/PyInteger.h"
#include "Object/PyList.h"
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
  methods.Put(CreatePyString("T"), CreatePyIife(Transpose));
  methods.Put(CreatePyString("shape"), CreatePyIife(Shape));
  SetAttributes(CreatePyDict(methods));
  Klass::Initialize();
}

KlassPtr MatrixKlass::Self() {
  static KlassPtr instance = std::make_shared<MatrixKlass>();
  return instance;
}

PyObjPtr Transpose(PyObjPtr args) {
  if (args->Klass() != ListKlass::Self()) {
    throw std::runtime_error("Transpose(): args is not a list");
  }
  if (args->len() != CreatePyInteger(1)) {
    throw std::runtime_error("Transpose(): args length is not 1");
  }
  auto matrix =
    std::dynamic_pointer_cast<PyMatrix>(args->getitem(CreatePyInteger(0)));
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

PyObjPtr MatrixKlass::mul(PyObjPtr lhs, PyObjPtr rhs) {
  if (lhs->Klass() != Self() || rhs->Klass() != Self()) {
    ThrowUnsupportedOperandError(lhs, rhs, CreatePyString("__mul__"));
  }
  auto left = std::dynamic_pointer_cast<PyMatrix>(lhs);
  auto right = std::dynamic_pointer_cast<PyMatrix>(rhs);
  return std::make_shared<PyMatrix>(left->Value().Multiply(right->Value()));
}

PyObjPtr MatrixKlass::add(PyObjPtr lhs, PyObjPtr rhs) {
  if (lhs->Klass() != Self() || rhs->Klass() != Self()) {
    ThrowUnsupportedOperandError(lhs, rhs, CreatePyString("__add__"));
  }
  auto left = std::dynamic_pointer_cast<PyMatrix>(lhs);
  auto right = std::dynamic_pointer_cast<PyMatrix>(rhs);
  return std::make_shared<PyMatrix>(left->Value().Add(right->Value()));
}

PyObjPtr Matrix(PyObjPtr args) {
  if (args->Klass() != ListKlass::Self()) {
    throw std::runtime_error("Matrix(): args is not a list");
  }
  if (args->len() != CreatePyInteger(1)) {
    throw std::runtime_error("Matrix(): args length is not 1");
  }
  auto list =
    std::dynamic_pointer_cast<PyList>(args->getitem(CreatePyInteger(0)));
  auto rows = list->len();
  auto cols = list->getitem(CreatePyInteger(0))->len();
  Collections::List<Collections::List<double>> data;
  for (Index i = 0; i < ToU64(rows); i++) {
    auto row =
      std::dynamic_pointer_cast<PyList>(list->getitem(CreatePyInteger(i)));
    if (row->len() != cols) {
      throw std::runtime_error("Matrix(): row length is not equal to cols");
    }
    Collections::List<double> rowData;
    for (Index j = 0; j < ToU64(cols); j++) {
      if (row->getitem(CreatePyInteger(j))->Klass() != FloatKlass::Self()) {
        throw std::runtime_error("Matrix(): element is not a float");
      }
      auto element =
        std::dynamic_pointer_cast<PyFloat>(row->getitem(CreatePyInteger(j)));
      rowData.Push(element->Value());
    }
    data.Push(rowData);
  }
  return std::make_shared<PyMatrix>(Collections::Matrix(data));
}

PyObjPtr Eye(PyObjPtr args) {
  if (args->Klass() != ListKlass::Self()) {
    throw std::runtime_error("Eye(): args is not a list");
  }
  if (args->len() != CreatePyInteger(1)) {
    throw std::runtime_error("Eye(): args length is not 1");
  }
  auto n =
    std::dynamic_pointer_cast<PyInteger>(args->getitem(CreatePyInteger(0)));
  return std::make_shared<PyMatrix>(Collections::Matrix::eye(ToU64(n)));
}

PyObjPtr Zeros(PyObjPtr args) {
  if (args->Klass() != ListKlass::Self()) {
    throw std::runtime_error("Zeros(): args is not a list");
  }
  if (args->len() != CreatePyInteger(2)) {
    throw std::runtime_error("Zeros(): args length is not 2");
  }
  auto rows =
    std::dynamic_pointer_cast<PyInteger>(args->getitem(CreatePyInteger(0)));
  auto cols =
    std::dynamic_pointer_cast<PyInteger>(args->getitem(CreatePyInteger(1)));
  return std::make_shared<PyMatrix>(
    Collections::Matrix(ToU64(rows), ToU64(cols))
  );
}

PyObjPtr Ones(PyObjPtr args) {
  if (args->Klass() != ListKlass::Self()) {
    throw std::runtime_error("Ones(): args is not a list");
  }
  if (args->len() != CreatePyInteger(2)) {
    throw std::runtime_error("Ones(): args length is not 2");
  }
  auto rows =
    std::dynamic_pointer_cast<PyInteger>(args->getitem(CreatePyInteger(0)));
  auto cols =
    std::dynamic_pointer_cast<PyInteger>(args->getitem(CreatePyInteger(1)));
  Collections::List<double> data(ToU64(rows) * ToU64(cols), 1.0);
  return std::make_shared<PyMatrix>(
    Collections::Matrix(ToU64(rows), ToU64(cols), data)
  );
}

PyObjPtr Diagnostic(PyObjPtr args) {
  if (args->Klass() != ListKlass::Self()) {
    throw std::runtime_error("Diagnostic(): args is not a list");
  }
  if (args->len() != CreatePyInteger(1)) {
    throw std::runtime_error("Diagnostic(): args length is not 1");
  }
  auto n =
    std::dynamic_pointer_cast<PyInteger>(args->getitem(CreatePyInteger(0)));
  Collections::List<double> data(ToU64(n) * ToU64(n), 0.0);
  Collections::Matrix matrix(ToU64(n), ToU64(n), data);
  for (Index i = 0; i < ToU64(n); i++) {
    matrix.Set(i, i, 1.0);
  }
  return std::make_shared<PyMatrix>(
    Collections::Matrix(ToU64(n), ToU64(n), data)
  );
}

PyObjPtr Shape(PyObjPtr args) {
  if (args->Klass() != ListKlass::Self()) {
    throw std::runtime_error("Shape(): args is not a list");
  }
  if (args->len() != CreatePyInteger(1)) {
    throw std::runtime_error("Shape(): args length is not 1");
  }
  auto matrix =
    std::dynamic_pointer_cast<PyMatrix>(args->getitem(CreatePyInteger(0)));
  auto shape = matrix->Value().Shape();
  return CreatePyList({CreatePyInteger(shape[0]), CreatePyInteger(shape[1])});
}

PyObjPtr Reshape(PyObjPtr args) {
  if (args->Klass() != ListKlass::Self()) {
    throw std::runtime_error("Reshape(): args is not a list");
  }
  if (args->len() != CreatePyInteger(2)) {
    throw std::runtime_error("Reshape(): args length is not 2");
  }
  auto matrix =
    std::dynamic_pointer_cast<PyMatrix>(args->getitem(CreatePyInteger(0)));
  auto list =
    std::dynamic_pointer_cast<PyList>(args->getitem(CreatePyInteger(1)));
  auto rows =
    std::dynamic_pointer_cast<PyInteger>(list->getitem(CreatePyInteger(0)));
  auto cols =
    std::dynamic_pointer_cast<PyInteger>(list->getitem(CreatePyInteger(1)));
  return std::make_shared<PyMatrix>(
    matrix->Value().Reshape(ToU64(rows), ToU64(cols))
  );
}

}  // namespace torchlight::Object