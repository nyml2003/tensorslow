#ifndef TORCHLIGHT_RUNTIME_INTERPRETER_H
#define TORCHLIGHT_RUNTIME_INTERPRETER_H

#include "runtime/PyFrame.h"
namespace torchlight::runtime {

class Interpreter {
 private:
  PyFramePtr frame;

 public:
  explicit Interpreter(PyFramePtr frame);

  void Run();
};

}  // namespace torchlight::runtime

#endif