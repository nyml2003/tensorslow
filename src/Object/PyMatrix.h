#ifndef TORCHLIGHT_OBJECT_PYMATRIX_H
#define TORCHLIGHT_OBJECT_PYMATRIX_H

#include "Collections/Matrix.h"

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

  PyObjPtr repr(const PyObjPtr& obj) override;

  PyObjPtr matmul(const PyObjPtr& lhs, const PyObjPtr& rhs) override;

  PyObjPtr mul(const PyObjPtr& lhs, const PyObjPtr& rhs) override;

  PyObjPtr add(const PyObjPtr& lhs, const PyObjPtr& rhs) override;
};

PyObjPtr Transpose(const PyObjPtr& args);

PyObjPtr Matrix(const PyObjPtr& args);

PyObjPtr Eye(const PyObjPtr& args);

PyObjPtr Zeros(const PyObjPtr& args);

PyObjPtr Ones(const PyObjPtr& args);

PyObjPtr Diagnostic(const PyObjPtr& args);

PyObjPtr Reshape(const PyObjPtr& args);

PyObjPtr Shape(const PyObjPtr& args);

}  // namespace torchlight::Object

#endif