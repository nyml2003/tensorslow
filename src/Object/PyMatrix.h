#ifndef TORCHLIGHT_OBJECT_PYMATRIX_H
#define TORCHLIGHT_OBJECT_PYMATRIX_H

#include "Collections/Matrix.h"
#include "Function/ObjectHelper.h"
#include "Object/Container/PyList.h"
#include "Object/Core/CoreHelper.h"
#include "Object/Core/Klass.h"
#include "Object/Core/PyObject.h"
#include "Object/Function/PyIife.h"
#include "Object/Function/PyNativeFunction.h"
#include "Object/Number/PyInteger.h"
#include "Object/Object.h"
#include "Object/String/PyString.h"
namespace torchlight::Object {

PyObjPtr Transpose(const PyObjPtr& args);

PyObjPtr Matrix(const PyObjPtr& args);

PyObjPtr Eye(const PyObjPtr& args);

PyObjPtr Zeros(const PyObjPtr& args);

PyObjPtr Ones(const PyObjPtr& args);

PyObjPtr Diagnostic(const PyObjPtr& args);

PyObjPtr Reshape(const PyObjPtr& args);

PyObjPtr Shape(const PyObjPtr& args);

PyObjPtr Where(const PyObjPtr& args);

PyObjPtr Concatenate(const PyObjPtr& args);

PyObjPtr Ravel(const PyObjPtr& args);

class MatrixKlass : public Klass {
 public:
  explicit MatrixKlass() = default;
  static KlassPtr Self() {
    static KlassPtr instance = std::make_shared<MatrixKlass>();
    LoadClass(CreatePyString("matrix")->as<PyString>(), instance);
    ConfigureBasicAttributes(instance);
    instance->AddAttribute(
      CreatePyString("T")->as<PyString>(), CreatePyIife(Transpose)
    );
    instance->AddAttribute(
      CreatePyString("shape")->as<PyString>(), CreatePyIife(Shape)
    );
    instance->AddAttribute(
      CreatePyString("reshape")->as<PyString>(), CreatePyNativeFunction(Reshape)
    );
    instance->AddAttribute(
      CreatePyString("ravel")->as<PyString>(), CreatePyNativeFunction(Ravel)
    );
    return instance;
  }
  PyObjPtr repr(const PyObjPtr& obj) override;
  PyObjPtr str(const PyObjPtr& obj) override { return repr(obj); }

  PyObjPtr matmul(const PyObjPtr& lhs, const PyObjPtr& rhs) override;

  PyObjPtr mul(const PyObjPtr& lhs, const PyObjPtr& rhs) override;

  PyObjPtr add(const PyObjPtr& lhs, const PyObjPtr& rhs) override;

  PyObjPtr sub(const PyObjPtr& lhs, const PyObjPtr& rhs) override;

  PyObjPtr gt(const PyObjPtr& lhs, const PyObjPtr& rhs) override;

  PyObjPtr eq(const PyObjPtr& lhs, const PyObjPtr& rhs) override;

  PyObjPtr len(const PyObjPtr& obj) override;

  PyObjPtr setitem(
    const PyObjPtr& obj,
    const PyObjPtr& key,
    const PyObjPtr& value
  ) override;

  PyObjPtr getitem(const PyObjPtr& obj, const PyObjPtr& key) override;
};

class PyMatrix;
using PyMatrixPtr = std::shared_ptr<PyMatrix>;

inline PyMatrixPtr CreatePyMatrix(Collections::Matrix matrix) {
  return std::make_shared<PyMatrix>(std::move(matrix));
}

class PyMatrix : public PyObject {
  friend class MatrixKlass;

 private:
  Collections::Matrix matrix;

 public:
  explicit PyMatrix(Collections::Matrix matrix)
    : PyObject(MatrixKlass::Self()), matrix(std::move(matrix)) {}

  void Shuffle() { matrix.Shuffle(); }
  PyMatrixPtr Transpose() const { return CreatePyMatrix(matrix.Transpose()); }
  PyMatrixPtr MatrixMultiply(const PyMatrixPtr& other) const {
    return CreatePyMatrix(matrix.MatrixMultiply(other->matrix));
  }
  PyMatrixPtr Multiply(const PyMatrixPtr& other) const {
    return CreatePyMatrix(matrix.Multiply(other->matrix));
  }
  PyMatrixPtr Multiply(double scalar) const {
    return CreatePyMatrix(matrix.Multiply(scalar));
  }
  PyMatrixPtr Add(const PyMatrixPtr& other) const {
    return CreatePyMatrix(matrix.Add(other->matrix));
  }
  PyMatrixPtr Subtract(const PyMatrixPtr& other) const {
    return CreatePyMatrix(matrix.Add(other->matrix.Multiply(-1)));
  }
  PyStrPtr ToString() const {
    return CreatePyString(matrix.ToString())->as<PyString>();
  }
  PyListPtr Shape() const {
    return CreatePyList({CreatePyInteger(matrix.Shape()[0]),
                         CreatePyInteger(matrix.Shape()[1])})
      ->as<PyList>();
  }
  PyIntPtr Rows() const {
    return CreatePyInteger(matrix.Rows())->as<PyInteger>();
  }
  PyIntPtr Cols() const {
    return CreatePyInteger(matrix.Cols())->as<PyInteger>();
  }

  PyMatrixPtr Reshape(Index rows, Index cols) const {
    return CreatePyMatrix(matrix.Reshape(rows, cols));
  }
  void SetRows(Index start, Index stop, const PyMatrixPtr& other) {
    matrix.SetRows(start, stop, other->matrix);
  }
  void SetCols(Index start, Index stop, const PyMatrixPtr& other) {
    matrix.SetCols(start, stop, other->matrix);
  }
  void SetSlice(
    Index rowStart,
    Index colStart,
    Index rowStop,
    Index colStop,
    const PyMatrixPtr& other
  ) {
    matrix.SetSlice(rowStart, colStart, rowStop, colStop, other->matrix);
  }
  PyMatrixPtr GetRows(Index start, Index stop) const {
    return CreatePyMatrix(matrix.GetRows(start, stop));
  }
  PyMatrixPtr GetCols(Index start, Index stop) const {
    return CreatePyMatrix(matrix.GetCols(start, stop));
  }
  PyMatrixPtr
  GetSlice(Index rowStart, Index colStart, Index rowStop, Index colStop) const {
    return CreatePyMatrix(matrix.GetSlice(rowStart, colStart, rowStop, colStop)
    );
  }
  double At(Index row, Index col) const { return matrix.At(row, col); }

  Collections::List<double> Ravel() const { return matrix.Data(); }
};

using PyMatrixPtr = std::shared_ptr<PyMatrix>;

}  // namespace torchlight::Object

#endif