#ifndef TENSORSLOW_OBJECT_PYGENERATOR_H
#define TENSORSLOW_OBJECT_PYGENERATOR_H
#include "Object/Core/PyNone.h"
#include "Object/Core/PyObject.h"
#include "Object/Iterator/Iterator.h"
#include "Object/Runtime/PyFrame.h"
#include "Runtime/Interpreter.h"

namespace tensorslow::Object {
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

class PyGenerator;
using PyGeneratorPtr = std::shared_ptr<PyGenerator>;

class PyGenerator : public PyObject {
 private:
  PyFramePtr frame;
  bool isExhausted{};
  std::function<PyObjPtr(const PyGeneratorPtr&)> func;

 public:
  explicit PyGenerator(PyFramePtr _frame)
    : PyObject(GeneratorKlass::Self()), frame(std::move(_frame)) {
    func = [](const PyGeneratorPtr& self) {
      auto result = self->frame->StackTop();
      auto lastFrame = Runtime::Interpreter::Instance().CurrentFrame();
      auto newGenerator = self->frame->Eval();
      Runtime::Interpreter::Instance().SetFrame(lastFrame);
      if (!newGenerator->is(GeneratorKlass::Self())) {
        // 说明是return
        self->isExhausted = true;
      }
      return result;
    };
  }

  explicit PyGenerator(std::function<PyObjPtr(const PyGeneratorPtr&)> func)
    : PyObject(GeneratorKlass::Self()), func(std::move(func)) {}
  [[nodiscard]] PyFramePtr Frame() const { return frame; }
  [[nodiscard]] bool IsExhausted() const { return isExhausted; }
  void SetExhausted() { isExhausted = true; }
  PyObjPtr Next() {
    if (isExhausted) {
      return CreateIterDone();
    }
    return func(shared_from_this()->as<PyGenerator>());
  }
};

inline PyObjPtr CreatePyGenerator(const PyFramePtr& frame) {
  return std::make_shared<PyGenerator>(frame);
}

inline PyObjPtr CreatePyGenerator(
  const std::function<PyObjPtr(const PyGeneratorPtr&)>& func
) {
  return std::make_shared<PyGenerator>(func);
}

}  // namespace tensorslow::Object

#endif