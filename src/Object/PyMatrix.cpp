#include "Object/PyMatrix.h"
#include "Collections/Matrix.h"
#include "Function/PyNativeFunction.h"
#include "Object/PyFloat.h"
#include "Object/PyList.h"
#include "Object/PyString.h"

namespace torchlight::Object {

PyObjPtr Transpose(const PyObjPtr& args) {
  CheckNativeFunctionArgumentsWithExpectedLength(args, 1);
  CheckNativeFunctionArgumentsAtIndexWithType(
    CreatePyString("Transpose")->as<PyString>(), args, 0, MatrixKlass::Self()
  );
  return args->as<PyList>()->GetItem(0)->as<PyMatrix>()->Transpose();
}

PyObjPtr MatrixKlass::repr(const PyObjPtr& obj) {
  if (!obj->is<PyMatrix>()) {
    throw std::runtime_error("MatrixKlass::repr(): obj is not a matrix");
  }
  return obj->as<PyMatrix>()->ToString();
}

PyObjPtr MatrixKlass::matmul(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  if (!lhs->is<PyMatrix>() || !rhs->is<PyMatrix>()) {
    throw std::runtime_error("MatrixKlass::matmul(): lhs or rhs is not a matrix"
    );
  }
  return lhs->as<PyMatrix>()->MatrixMultiply(rhs->as<PyMatrix>());
}

PyObjPtr MatrixKlass::mul(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  if (!lhs->is<PyMatrix>() || !rhs->is<PyMatrix>()) {
    throw std::runtime_error("MatrixKlass::mul(): lhs or rhs is not a matrix");
  }
  return lhs->as<PyMatrix>()->Multiply(rhs->as<PyMatrix>());
}

PyObjPtr MatrixKlass::add(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  if (!lhs->is<PyMatrix>() || !rhs->is<PyMatrix>()) {
    throw std::runtime_error("MatrixKlass::add(): lhs or rhs is not a matrix");
  }
  return lhs->as<PyMatrix>()->Add(rhs->as<PyMatrix>());
}

PyObjPtr Matrix(const PyObjPtr& args) {
  if (!args->is<PyList>()) {
    throw std::runtime_error("Matrix(): args is not a list");
  }
  auto argList = args->as<PyList>();
  if (argList->Length() != 1) {
    throw std::runtime_error("Matrix(): args length is not 1");
  }
  auto list = argList->GetItem(0)->as<PyList>();
  auto rows = list->Length();
  auto cols = list->GetItem(0)->as<PyList>()->Length();
  Collections::List<double> data;
  for (Index i = 0; i < rows; i++) {
    auto row = list->GetItem(i)->as<PyList>();
    if (row->Length() != cols) {
      throw std::runtime_error("Matrix(): row length is not equal to cols");
    }
    for (Index j = 0; j < cols; j++) {
      if (!row->GetItem(j)->is<PyFloat>()) {
        throw std::runtime_error("Matrix(): element is not a float");
      }
      auto element = row->GetItem(j)->as<PyFloat>();
      data.Push(element->Value());
    }
  }
  return CreatePyMatrix(Collections::Matrix(rows, cols, data));
}

PyObjPtr Eye(const PyObjPtr& args) {
  if (!args->is<PyList>()) {
    throw std::runtime_error("Eye(): args is not a list");
  }
  auto argList = args->as<PyList>();
  if (argList->Length() != 1) {
    throw std::runtime_error("Eye(): args length is not 1");
  }
  auto dim = argList->GetItem(0)->as<PyInteger>()->ToU64();
  return CreatePyMatrix(Collections::Matrix::Eye(dim));
}

PyObjPtr Zeros(const PyObjPtr& args) {
  if (!args->is<PyList>()) {
    throw std::runtime_error("Zeros(): args is not a list");
  }
  auto argList = args->as<PyList>();
  if (argList->Length() != 2) {
    throw std::runtime_error("Zeros(): args length is not 2");
  }
  auto rows = argList->GetItem(0)->as<PyInteger>()->ToU64();
  auto cols = argList->GetItem(1)->as<PyInteger>()->ToU64();
  Collections::List<double> data(rows * cols, 0.0);
  return CreatePyMatrix(Collections::Matrix(rows, cols, data));
}

PyObjPtr Ones(const PyObjPtr& args) {
  if (!args->is<PyList>()) {
    throw std::runtime_error("Ones(): args is not a list");
  }
  auto argList = args->as<PyList>();
  if (argList->Length() != 2) {
    throw std::runtime_error("Ones(): args length is not 2");
  }
  auto rows = argList->GetItem(0)->as<PyInteger>()->ToU64();
  auto cols = argList->GetItem(1)->as<PyInteger>()->ToU64();
  Collections::List<double> data(rows * cols, 1.0);
  return CreatePyMatrix(Collections::Matrix(rows, cols, data));
}

PyObjPtr Diagnostic(const PyObjPtr& args) {
  if (!args->is<PyList>()) {
    throw std::runtime_error("Diagnostic(): args is not a list");
  }
  auto argList = args->as<PyList>();
  if (argList->Length() != 1) {
    throw std::runtime_error("Diagnostic(): args length is not 1");
  }
  auto arg0 = argList->GetItem(0);
  if (!arg0->is<PyList>()) {
    throw std::runtime_error("Diagnostic(): arg0 is not a list");
  }
  auto list = arg0->as<PyList>();
  auto dim = list->Length();
  Collections::List<double> data(dim * dim, 0.0);
  for (Index i = 0; i < dim; i++) {
    auto element = list->GetItem(i);
    if (!element->is<PyFloat>()) {
      throw std::runtime_error("Diagnostic(): element is not a float");
    }
    data[i * dim + i] = element->as<PyFloat>()->Value();
  }
  return CreatePyMatrix(Collections::Matrix(dim, dim, data));
}

PyObjPtr Shape(const PyObjPtr& args) {
  if (!args->is<PyList>()) {
    throw std::runtime_error("Shape(): args is not a list");
  }
  return args->as<PyList>()->GetItem(0)->as<PyMatrix>()->Shape();
}

PyObjPtr Reshape(const PyObjPtr& args) {
  if (!args->is<PyList>()) {
    throw std::runtime_error("Reshape(): args is not a list");
  }
  auto argList = args->as<PyList>();
  if (argList->Length() != 2) {
    throw std::runtime_error("Reshape(): args length is not 2");
  }
  auto matrix = argList->GetItem(0)->as<PyMatrix>();
  auto list = argList->GetItem(1)->as<PyList>();
  if (list->Length() != 2) {
    throw std::runtime_error("Reshape(): list length is not 2");
  }
  auto rows = list->GetItem(0)->as<PyInteger>()->ToU64();
  auto cols = list->GetItem(1)->as<PyInteger>()->ToU64();
  return matrix->Reshape(rows, cols);
}

}  // namespace torchlight::Object