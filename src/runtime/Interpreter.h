#ifndef TORCHLIGHT_RUNTIME_INTERPRETER_H
#define TORCHLIGHT_RUNTIME_INTERPRETER_H

#include "object/PyCode.h"
namespace torchlight::runtime {

class Interpreter {
 private:
  object::PyObjPtr frame;

  object::PyObjPtr returnValue;

 public:
  explicit Interpreter();

  void Run(const object::PyCodePtr& code);

  void BuildFrameWithFunction(
    const object::PyObjPtr& func,
    const collections::List<object::PyObjPtr>& arguments
  );

  void EvalFrame();

  void LeaveFrame();

  void DestroyFrame();
};

}  // namespace torchlight::runtime

#endif