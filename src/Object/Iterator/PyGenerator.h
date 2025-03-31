#ifndef TORCHLIGHT_OBJECT_PYGENERATOR_H
#define TORCHLIGHT_OBJECT_PYGENERATOR_H
#include "Object/Core/PyObject.h"
#include "Object/Iterator/Iterator.h"
#include "Object/Runtime/PyFrame.h"
#include "Runtime/Interpreter.h"

namespace torchlight::Object {
class PyGenerator;
class GeneratorKlass : public Klass {
 public:
  explicit GeneratorKlass() = default;
  static KlassPtr Self() {
    static KlassPtr instance = std::make_shared<GeneratorKlass>();
    return instance;
  }

  void Initialize() override {
    if (this->isInitialized) {
      return;
    }
    LoadClass(CreatePyString("generator")->as<PyString>(), Self());
    ConfigureBasicAttributes(Self());
    this->isInitialized = true;
  }

  PyObjPtr iter(const PyObjPtr& obj) override { return obj; }
  PyObjPtr next(const PyObjPtr& obj) override;
};

class PyGenerator : public PyObject {
 private:
  PyFramePtr frame;
  bool isExhausted{};

 public:
  explicit PyGenerator(PyFramePtr frame)
    : PyObject(GeneratorKlass::Self()), frame(std::move(frame)) {}
  [[nodiscard]] PyFramePtr Frame() const { return frame; }
  [[nodiscard]] bool IsExhausted() const { return isExhausted; }
  void SetExhausted() { isExhausted = true; }
  PyObjPtr Next() {
    if (isExhausted) {
      return CreateIterDone();
    }
    auto result = frame->StackTop();
    auto lastFrame = Runtime::Interpreter::Instance().CurrentFrame();
    auto newGenerator = frame->Eval();
    Runtime::Interpreter::Instance().SetFrame(lastFrame);
    if (!newGenerator->is<PyGenerator>()) {
      // 说明是return
      isExhausted = true;
    }
    return result;
  }
};

using PyGeneratorPtr = std::shared_ptr<PyGenerator>;

inline PyObjPtr CreatePyGenerator(const PyFramePtr& frame) {
  return std::make_shared<PyGenerator>(frame);
}

}  // namespace torchlight::Object

#endif