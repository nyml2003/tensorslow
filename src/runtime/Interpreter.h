#ifndef TORCHLIGHT_RUNTIME_INTERPRETER_H
#define TORCHLIGHT_RUNTIME_INTERPRETER_H

#include "Object/PyCode.h"
namespace torchlight::Runtime {

class Interpreter {
 private:
  Object::PyObjPtr frame;

  Object::PyObjPtr returnValue;

 public:
  explicit Interpreter();

  void Run(const Object::PyCodePtr& code);

  void BuildFrameWithFunction(
    const Object::PyObjPtr& func,
    const Collections::List<Object::PyObjPtr>& arguments
  );

  void EvalFrame();

  void LeaveFrame();

  void DestroyFrame();
};

}  // namespace torchlight::Runtime

#endif