#ifndef TORCHLIGHT_RUNTIME_INTERPRETER_H
#define TORCHLIGHT_RUNTIME_INTERPRETER_H

#include "ByteCode/PyCode.h"
#include "Object/Common.h"

namespace torchlight::Runtime {

class Interpreter {
 private:
  Object::PyObjPtr frame;

  Object::PyObjPtr returnValue;

  Object::PyDictPtr builtins;

 public:
  explicit Interpreter();

  void Run(const Object::PyCodePtr& code);

  void BuildFrameWithFunction(
    const Object::PyObjPtr& func,
    const Object::PyObjPtr& _arguments
  );

  void EvalFrame();

  void LeaveFrame();

  void DestroyFrame();
};

}  // namespace torchlight::Runtime

#endif