#ifndef TORCHLIGHT_RUNTIME_PYGENERATOR_H
#define TORCHLIGHT_RUNTIME_PYGENERATOR_H
#include "Object/Iterator.h"
#include "Object/PyObject.h"
#include "Runtime/Interpreter.h"
#include "Runtime/PyFrame.h"

namespace torchlight::Runtime {

class GeneratorKlass : public Object::Klass {
 public:
  explicit GeneratorKlass() = default;
  static Object::KlassPtr Self() {
    static Object::KlassPtr instance = std::make_shared<GeneratorKlass>();
    LoadClass(
      Object::CreatePyString("generator")->as<Object::PyString>(), instance
    );
    ConfigureBasicAttributes(instance);
    return instance;
  }

  Object::PyObjPtr iter(const Object::PyObjPtr& obj) override { return obj; }
  Object::PyObjPtr next(const Object::PyObjPtr& obj) override;
};

class PyGenerator : public Object::PyObject {
 private:
  PyFramePtr frame;
  bool isExhausted{};

 public:
  explicit PyGenerator(PyFramePtr frame)
    : Object::PyObject(GeneratorKlass::Self()), frame(std::move(frame)) {}
  [[nodiscard]] PyFramePtr Frame() const { return frame; }
  [[nodiscard]] bool IsExhausted() const { return isExhausted; }
  void SetExhausted() { isExhausted = true; }
  Object::PyObjPtr Next() {
    if (isExhausted) {
      return Object::CreateIterDone();
    }
    auto result = frame->StackTop();
    auto lastFrame = Interpreter::Instance().CurrentFrame();
    auto newGenerator = frame->Eval();
    Interpreter::Instance().SetFrame(lastFrame);
    if (!newGenerator->is<PyGenerator>()) {
      // 说明是return
      isExhausted = true;
    }
    return result;
  }
};

using PyGeneratorPtr = std::shared_ptr<PyGenerator>;

inline Object::PyObjPtr CreatePyGenerator(const PyFramePtr& frame) {
  return std::make_shared<PyGenerator>(frame);
}

}  // namespace torchlight::Runtime

#endif