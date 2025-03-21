#include "Object/PyMatrix.h"
#include "Collections/Matrix.h"
#include "Function/ObjectHelper.h"
#include "Object/Container/PyList.h"
#include "Object/Core/PyBoolean.h"
#include "Object/Core/PyNone.h"
#include "Object/Function/PyNativeFunction.h"
#include "Object/Number/PyFloat.h"
#include "Object/Number/PyInteger.h"
#include "Object/Object.h"
#include "Object/String/PyString.h"

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
  auto matrix = obj->as<PyMatrix>();
  auto shape = matrix->Shape();
  auto rows = shape->GetItem(0)->as<PyInteger>()->ToU64();
  auto cols = shape->GetItem(1)->as<PyInteger>()->ToU64();
  auto repr = CreatePyString("[")->as<PyString>();
  for (Index i = 0; i < rows; i++) {
    repr = repr->Add(CreatePyString("[")->as<PyString>());
    for (Index j = 0; j < cols; j++) {
      repr = repr->Add(CreatePyString(" ")->as<PyString>());
      repr = repr->Add(CreatePyFloat(matrix->At(i, j))->repr()->as<PyString>());
      if (j != cols - 1) {
        repr = repr->Add(CreatePyString(", ")->as<PyString>());
      }
    }
    repr = repr->Add(CreatePyString("]")->as<PyString>());
    if (i != rows - 1) {
      repr = repr->Add(CreatePyString("\n ")->as<PyString>());
    }
  }
  repr = repr->Add(CreatePyString("]")->as<PyString>());
  return repr;
}

PyObjPtr MatrixKlass::matmul(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  if (!lhs->is<PyMatrix>() || !rhs->is<PyMatrix>()) {
    throw std::runtime_error("MatrixKlass::matmul(): lhs or rhs is not a matrix"
    );
  }
  return lhs->as<PyMatrix>()->MatrixMultiply(rhs->as<PyMatrix>());
}

PyObjPtr MatrixKlass::gt(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  if (!lhs->is<PyMatrix>()) {
    throw std::runtime_error("MatrixKlass::gt(): lhs is not a matrix");
  }
  if (!rhs->is<PyFloat>()) {
    throw std::runtime_error("MatrixKlass::gt(): rhs is not a float");
  }
  auto matrix = lhs->as<PyMatrix>();
  auto compareObj = rhs->as<PyFloat>()->Value();
  auto shape = lhs->as<PyMatrix>()->Shape();
  auto rows = shape->GetItem(0)->as<PyInteger>()->ToU64();
  auto cols = shape->GetItem(1)->as<PyInteger>()->ToU64();
  // 初始化一个rows * cols的二维Python列表，用于存储比较结果
  Collections::List<PyObjPtr> data;
  for (Index i = 0; i < rows; i++) {
    Collections::List<PyObjPtr> row;
    for (Index j = 0; j < cols; j++) {
      row.Push(
        matrix->At(i, j) > compareObj ? CreatePyBoolean(true)
                                      : CreatePyBoolean(false)
      );
    }
    data.Push(CreatePyList(row));
  }
  return CreatePyList(data);
}

PyObjPtr MatrixKlass::eq(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  if (!lhs->is<PyMatrix>() || !rhs->is<PyFloat>()) {
    throw std::runtime_error("MatrixKlass::eq(): lhs or rhs is not a matrix");
  }
  auto matrix = lhs->as<PyMatrix>();
  auto compareObj = rhs->as<PyFloat>()->Value();
  auto shape = lhs->as<PyMatrix>()->Shape();
  auto rows = shape->GetItem(0)->as<PyInteger>()->ToU64();
  auto cols = shape->GetItem(1)->as<PyInteger>()->ToU64();
  Collections::List<PyObjPtr> data;
  for (Index i = 0; i < rows; i++) {
    Collections::List<PyObjPtr> row;
    for (Index j = 0; j < cols; j++) {
      row.Push(
        matrix->At(i, j) == compareObj ? CreatePyBoolean(true)
                                       : CreatePyBoolean(false)
      );
    }
    data.Push(CreatePyList(row));
  }
  return CreatePyList(data);
}

PyObjPtr MatrixKlass::mul(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  if (!lhs->is<PyMatrix>()) {
    throw std::runtime_error("MatrixKlass::mul(): lhs or rhs is not a matrix");
  }
  auto matrix = lhs->as<PyMatrix>();
  if (rhs->is<PyMatrix>()) {
    return matrix->Multiply(rhs->as<PyMatrix>());
  }
  if (rhs->is<PyFloat>()) {
    return matrix->Multiply(rhs->as<PyFloat>()->Value());
  }
  return lhs->as<PyMatrix>()->Multiply(rhs->as<PyMatrix>());
}

PyObjPtr MatrixKlass::add(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  if (!lhs->is<PyMatrix>() || !rhs->is<PyMatrix>()) {
    throw std::runtime_error("MatrixKlass::add(): lhs or rhs is not a matrix");
  }
  return lhs->as<PyMatrix>()->Add(rhs->as<PyMatrix>());
}

PyObjPtr MatrixKlass::sub(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  if (!lhs->is<PyMatrix>() || !rhs->is<PyMatrix>()) {
    throw std::runtime_error("MatrixKlass::sub(): lhs or rhs is not a matrix");
  }
  return lhs->as<PyMatrix>()->Subtract(rhs->as<PyMatrix>());
}

PyObjPtr MatrixKlass::len(const PyObjPtr& obj) {
  if (!obj->is<PyMatrix>()) {
    throw std::runtime_error("MatrixKlass::len(): obj is not a matrix");
  }
  return obj->as<PyMatrix>()->Rows();
}

PyObjPtr MatrixKlass::getitem(const PyObjPtr& obj, const PyObjPtr& key) {
  if (!obj->is<PyMatrix>()) {
    throw std::runtime_error("MatrixKlass::getitem(): obj is not a matrix");
  }
  auto matrix = obj->as<PyMatrix>();
  // a[row,col] a[row] a[row][col] a[rowStart:rowEnd,colStart:colEnd]
  if (key->is<PyList>()) {
    // a[row,col] 或者 a[rowStart:rowEnd,colStart:colEnd]
    auto keyList = key->as<PyList>();
    if (keyList->GetItem(0)->is<PyInteger>()) {
      // a[row,col]
      if (keyList->Length() != 2) {
        throw std::runtime_error("MatrixKlass::getitem(): key length is not 2");
      }
      auto shape = matrix->Shape();
      auto matrixRow = shape->GetItem(0)->as<PyInteger>()->ToU64();
      auto matrixCol = shape->GetItem(1)->as<PyInteger>()->ToU64();
      Index rowValue = 0;
      Index colValue = 0;
      auto row = keyList->GetItem(0)->as<PyInteger>();
      if (row->GetSign() == Collections::Integer::IntSign::Positive) {
        rowValue = row->ToU64();
      }
      if (row->GetSign() == Collections::Integer::IntSign::Negative) {
        rowValue = matrixRow + row->ToI64();
      }
      auto col = keyList->GetItem(1)->as<PyInteger>();
      if (col->GetSign() == Collections::Integer::IntSign::Positive) {
        colValue = col->ToU64();
      }
      if (col->GetSign() == Collections::Integer::IntSign::Negative) {
        colValue = matrixCol + col->ToI64();
      }
      return CreatePyMatrix(
        Collections::Matrix(1, 1, {matrix->At(rowValue, colValue)})
      );
    }
    if (keyList->GetItem(0)->is<PySlice>()) {
      // a[rowStart:rowEnd,colStart:colEnd]
      if (keyList->Length() != 2) {
        throw std::runtime_error("MatrixKlass::getitem(): key length is not 2");
      }
      auto rowSlice = keyList->GetItem(0)->as<PySlice>();
      auto shape = matrix->Shape();
      rowSlice->BindLength(matrix->Shape()->GetItem(0)->as<PyInteger>()->ToU64()
      );
      auto colSlice = keyList->GetItem(1)->as<PySlice>();
      colSlice->BindLength(matrix->Shape()->GetItem(1)->as<PyInteger>()->ToU64()
      );
      auto rowStart = rowSlice->GetStart()->as<PyInteger>()->ToU64();
      auto rowStop = rowSlice->GetStop()->as<PyInteger>()->ToU64();
      auto colStart = colSlice->GetStart()->as<PyInteger>()->ToU64();
      auto colStop = colSlice->GetStop()->as<PyInteger>()->ToU64();
      return matrix->GetSlice(rowStart, colStart, rowStop, colStop);
    }
  }
  if (key->is<PySlice>()) {
    // a[rowStart:rowEnd]
    auto rowSlice = key->as<PySlice>();
    rowSlice->BindLength(matrix->Shape()->GetItem(0)->as<PyInteger>()->ToU64());
    auto rowStart = rowSlice->GetStart()->as<PyInteger>()->ToU64();
    auto rowStop = rowSlice->GetStop()->as<PyInteger>()->ToU64();
    return matrix->GetRows(rowStart, rowStop);
  }
  throw std::runtime_error("MatrixKlass::getitem(): key type is not supported");
}

PyObjPtr MatrixKlass::setitem(
  const PyObjPtr& obj,
  const PyObjPtr& key,
  const PyObjPtr& value
) {
  if (!obj->is<PyMatrix>()) {
    throw std::runtime_error("MatrixKlass::setitem(): obj is not a matrix");
  }
  // a[rowStart:rowStop,colStart:colStop] = matrix
  if (!key->is<PyList>()) {
    throw std::runtime_error("MatrixKlass::setitem(): key is not a list");
  }
  // TODO a[0,0] = 0的情况
  if (!value->is<PyMatrix>()) {
    throw std::runtime_error("MatrixKlass::setitem(): value is not a matrix");
  }
  auto matrix = obj->as<PyMatrix>();
  auto keyList = key->as<PyList>();
  auto other = value->as<PyMatrix>();
  auto rowSlice = keyList->GetItem(0)->as<PySlice>();
  rowSlice->BindLength(matrix->Shape()->GetItem(0)->as<PyInteger>()->ToU64());
  auto colSlice = keyList->GetItem(1)->as<PySlice>();
  colSlice->BindLength(matrix->Shape()->GetItem(1)->as<PyInteger>()->ToU64());
  auto rowStart = rowSlice->GetStart()->as<PyInteger>()->ToU64();
  auto rowStop = rowSlice->GetStop()->as<PyInteger>()->ToU64();
  auto colStart = colSlice->GetStart()->as<PyInteger>()->ToU64();
  auto colStop = colSlice->GetStop()->as<PyInteger>()->ToU64();
  matrix->SetSlice(rowStart, colStart, rowStop, colStop, other);
  return CreatePyNone();
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

  if (argList->Length() != 1) {
    throw std::runtime_error("Zeros(): args length is not 1");
  }
  auto shape = argList->GetItem(0)->as<PyList>();
  if (shape->Length() != 2) {
    throw std::runtime_error("Zeros(): shape length is not 2");
  }
  auto rows = shape->GetItem(0)->as<PyInteger>()->ToU64();
  auto cols = shape->GetItem(1)->as<PyInteger>()->ToU64();
  Collections::List<double> data(rows * cols, 0.0);
  return CreatePyMatrix(Collections::Matrix(rows, cols, data));
}

PyObjPtr Ones(const PyObjPtr& args) {
  if (!args->is<PyList>()) {
    throw std::runtime_error("Ones(): args is not a list");
  }
  auto argList = args->as<PyList>();

  if (argList->Length() != 1) {
    throw std::runtime_error("Ones(): args length is not 1");
  }
  auto shape = argList->GetItem(0)->as<PyList>();
  if (shape->Length() != 2) {
    throw std::runtime_error("Ones(): shape length is not 2");
  }
  auto rows = shape->GetItem(0)->as<PyInteger>()->ToU64();
  auto cols = shape->GetItem(1)->as<PyInteger>()->ToU64();
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

PyObjPtr Where(const PyObjPtr& args) {
  CheckNativeFunctionArgumentsWithExpectedLength(args, 3);
  CheckNativeFunctionArgumentsAtIndexWithType(
    CreatePyString("Where")->as<PyString>(), args, 0, ListKlass::Self()
  );
  CheckNativeFunctionArgumentsAtIndexWithType(
    CreatePyString("Where")->as<PyString>(), args, 1, FloatKlass::Self()
  );
  CheckNativeFunctionArgumentsAtIndexWithType(
    CreatePyString("Where")->as<PyString>(), args, 2, FloatKlass::Self()
  );
  auto trueValue = args->as<PyList>()->GetItem(1)->as<PyFloat>()->Value();
  auto falseValue = args->as<PyList>()->GetItem(2)->as<PyFloat>()->Value();
  auto list = args->as<PyList>()->GetItem(0)->as<PyList>();
  auto cols = list->GetItem(0)->as<PyList>()->Length();
  auto rows = list->Length();
  Collections::List<double> data(rows * cols, falseValue);
  for (Index i = 0; i < rows; i++) {
    auto row = list->GetItem(i)->as<PyList>();
    for (Index j = 0; j < cols; j++) {
      if (!row->GetItem(j)->is<PyBoolean>()) {
        throw std::runtime_error("Where(): element is not a boolean");
      }
      if (row->GetItem(j)->as<PyBoolean>()->Value()) {
        data[i * cols + j] = trueValue;
      }
    }
  }
  return CreatePyMatrix(Collections::Matrix(rows, cols, data));
}

PyObjPtr Ravel(const PyObjPtr& args) {
  if (!args->is<PyList>()) {
    throw std::runtime_error("Ravel(): args is not a list");
  }
  auto argList = args->as<PyList>();

  if (argList->Length() != 1) {
    throw std::runtime_error("Ravel(): args length is not 1");
  }
  auto matrix = argList->GetItem(0)->as<PyMatrix>();
  auto data = matrix->Ravel();
  Collections::List<PyObjPtr> result(data.Size());
  for (Index i = 0; i < data.Size(); i++) {
    result.Push(CreatePyFloat(data[i]));
  }
  return CreatePyList(result);
}

PyObjPtr Concatenate(const PyObjPtr& args) {
  if (!args->is<PyList>()) {
    throw std::runtime_error("Concatenate(): args is not a list");
  }
  auto argList = args->as<PyList>();

  if (argList->Length() != 1) {
    throw std::runtime_error("Concatenate(): args length is not 1");
  }
  auto list = argList->GetItem(0)->as<PyList>();
  auto rows = list->Length();
  auto cols = list->GetItem(0)
                ->as<PyMatrix>()
                ->Shape()
                ->GetItem(1)
                ->as<PyInteger>()
                ->ToU64();
  Collections::List<double> data;
  for (Index i = 0; i < rows; i++) {
    auto row = list->GetItem(i)->as<PyMatrix>();
    if (row->Shape()->GetItem(1)->as<PyInteger>()->ToU64() != cols) {
      throw std::runtime_error("Concatenate(): cols is not equal");
    }
    auto rowData = row->Ravel();
    for (Index j = 0; j < rowData.Size(); j++) {
      data.Push(rowData[j]);
    }
  }
  return CreatePyMatrix(Collections::Matrix(rows, cols, data));
}

}  // namespace torchlight::Object