#ifndef TORCHLIGHT_OBJECT_PYMATRIX_H
#define TORCHLIGHT_OBJECT_PYMATRIX_H

#include "Collections/Matrix.h"
#include "Object/Common.h"
#include "Object/Klass.h"
#include "Object/PyObject.h"

namespace torchlight::Object {

class PyMatrix : public PyObject {
 private:
  Collections::Matrix matrix;

 public:
  explicit PyMatrix(Collections::Matrix matrix);

  [[nodiscard]] Collections::Matrix Value() const;
};

using PyMatrixPtr = std::shared_ptr<PyMatrix>;

class MatrixKlass : public Klass {
 public:
  explicit MatrixKlass();
  static KlassPtr Self();

  void Initialize() override;

  PyObjPtr repr(PyObjPtr obj) override;

  PyObjPtr matmul(PyObjPtr lhs, PyObjPtr rhs) override;

  PyObjPtr mul(PyObjPtr lhs, PyObjPtr rhs) override;

  PyObjPtr add(PyObjPtr lhs, PyObjPtr rhs) override;
};

PyObjPtr Transpose(PyObjPtr args);

PyObjPtr Matrix(PyObjPtr args);

PyObjPtr Eye(PyObjPtr args);

PyObjPtr Zeros(PyObjPtr args);

PyObjPtr Ones(PyObjPtr args);

PyObjPtr Diagnostic(PyObjPtr args);

PyObjPtr Reshape(PyObjPtr args);

PyObjPtr Shape(PyObjPtr args);

}  // namespace torchlight::Object

#endif