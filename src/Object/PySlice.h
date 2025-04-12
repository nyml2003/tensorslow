#ifndef TORCHLIGHT_OBJECT_PYSLICE_H
#define TORCHLIGHT_OBJECT_PYSLICE_H

#include "Function/BuiltinFunction.h"
#include "Object/Core/CoreHelper.h"
#include "Object/Core/PyObject.h"
#include "Object/Object.h"
#include "Object/String/PyString.h"
namespace torchlight::Object {

class SliceKlass : public Klass {
 public:
  explicit SliceKlass() = default;
  static KlassPtr Self() {
    static KlassPtr instance = std::make_shared<SliceKlass>();
    return instance;
  }
  void Initialize() override {
    if (this->isInitialized) {
      return;
    }
    LoadClass(CreatePyString("slice")->as<PyString>(), Self());
    ConfigureBasicAttributes(Self());
    this->isInitialized = true;
  }
  PyObjPtr init(const PyObjPtr& type, const PyObjPtr& args) override;
  PyObjPtr str(const PyObjPtr& obj) override;
};

class PySlice : public PyObject {
 private:
  PyObjPtr start;
  PyObjPtr stop;
  PyObjPtr step;

 public:
  PySlice(PyObjPtr _start, PyObjPtr _stop, PyObjPtr _step)
    : PyObject(SliceKlass::Self()),
      start(std::move(_start)),
      stop(std::move(_stop)),
      step(std::move(_step)) {}

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
