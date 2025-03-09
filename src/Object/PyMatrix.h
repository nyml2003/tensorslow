#ifndef TORCHLIGHT_OBJECT_PYMATRIX_H
#define TORCHLIGHT_OBJECT_PYMATRIX_H

#include "Collections/Matrix.h"
#include "Function/PyIife.h"
#include "Object/Klass.h"
#include "Object/ObjectHelper.h"
#include "Object/PyInteger.h"
#include "Object/PyList.h"
#include "Object/PyObject.h"
#include "Object/PySlice.h"
#include "Object/PyString.h"

namespace torchlight::Object {

PyObjPtr Transpose(const PyObjPtr& args);

PyObjPtr Matrix(const PyObjPtr& args);

PyObjPtr Eye(const PyObjPtr& args);

PyObjPtr Zeros(const PyObjPtr& args);

PyObjPtr Ones(const PyObjPtr& args);

PyObjPtr Diagnostic(const PyObjPtr& args);

PyObjPtr Reshape(const PyObjPtr& args);

PyObjPtr Shape(const PyObjPtr& args);

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
    return instance;
  }

  // PyObjPtr getitem(const PyObjPtr& obj, const PyObjPtr& key) override;

  // PyObjPtr setitem(
  //   const PyObjPtr& obj,
  //   const PyObjPtr& key,
  //   const PyObjPtr& value
  // ) override;

  PyObjPtr repr(const PyObjPtr& obj) override;

  PyObjPtr matmul(const PyObjPtr& lhs, const PyObjPtr& rhs) override;

  PyObjPtr mul(const PyObjPtr& lhs, const PyObjPtr& rhs) override;

  PyObjPtr add(const PyObjPtr& lhs, const PyObjPtr& rhs) override;
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


  PyMatrixPtr Transpose() const { return CreatePyMatrix(matrix.Transpose()); }
  PyMatrixPtr MatrixMultiply(const PyMatrixPtr& other) const {
    return CreatePyMatrix(matrix.MatrixMultiply(other->matrix));
  }
  PyMatrixPtr Multiply(const PyMatrixPtr& other) const {
    return CreatePyMatrix(matrix.Multiply(other->matrix));
  }
  PyMatrixPtr Add(const PyMatrixPtr& other) const {
    return CreatePyMatrix(matrix.Add(other->matrix));
  }
  PyStrPtr ToString() const {
    return CreatePyString(matrix.ToString())->as<PyString>();
  }

  PyListPtr Shape() const {
    return CreatePyList({CreatePyInteger(matrix.Shape()[0]),
                         CreatePyInteger(matrix.Shape()[1])})
      ->as<PyList>();
  }

  PyMatrixPtr Reshape(Index rows, Index cols) const {
    return CreatePyMatrix(matrix.Reshape(rows, cols));
  }

};

using PyMatrixPtr = std::shared_ptr<PyMatrix>;

}  // namespace torchlight::Object

#endif