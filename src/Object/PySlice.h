#ifndef TORCHLIGHT_OBJECT_PYSLICE_H
#define TORCHLIGHT_OBJECT_PYSLICE_H

#include "Object/Object.h"
#include "Object/ObjectHelper.h"
#include "Object/PyObject.h"
#include "Object/PyString.h"

namespace torchlight::Object {

class SliceKlass : public Klass {
 public:
  explicit SliceKlass() = default;
  static KlassPtr Self() {
    static KlassPtr instance = std::make_shared<SliceKlass>();
    LoadClass(CreatePyString("slice")->as<PyString>(), instance);
    ConfigureBasicAttributes(instance);
    return instance;
  }
  PyObjPtr construct(const PyObjPtr& type, const PyObjPtr& args) override;
  PyObjPtr str(const PyObjPtr& obj) override;
};

class PySlice : public PyObject {
 private:
  PyObjPtr start;
  PyObjPtr stop;
  PyObjPtr step;

 public:
  PySlice(PyObjPtr start, PyObjPtr stop, PyObjPtr step)
    : PyObject(SliceKlass::Self()),
      start(std::move(start)),
      stop(std::move(stop)),
      step(std::move(step)) {}

  PyObjPtr GetStart() const { return start; }
  PyObjPtr GetStop() const { return stop; }
  PyObjPtr GetStep() const { return step; }

  /**
   * @brief 对成员变量做数据清洗
   * @param length 目标对象的长度
   */
  void BindLength(Index length);
};

// [start:stop:step]

inline PyObjPtr CreatePySlice(
  const PyObjPtr& start,
  const PyObjPtr& stop,
  const PyObjPtr& step
) {
  return std::make_shared<PySlice>(start, stop, step);
}
using PySlicePtr = std::shared_ptr<PySlice>;

}  // namespace torchlight::Object

#endif  // TORCHLIGHT_OBJECT_PYSLICE_H
