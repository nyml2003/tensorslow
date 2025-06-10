#ifndef TENSORSLOW_RUNTIME_EVENTLOOP_H
#define TENSORSLOW_RUNTIME_EVENTLOOP_H

#include <mutex>
#include <queue>
#include "Object/Function/PyNativeFunction.h"

namespace tensorslow::Runtime {

class EventLoop {
 private:
  std::queue<Object::PyNativeFunctionPtr> macroTaskQueue;  // 宏任务队列
  std::queue<Object::PyNativeFunctionPtr> microTaskQueue;  // 微任务队列
  std::mutex queueMutex;
  std::condition_variable taskConditionVar;
  bool running = false;

 public:
  static EventLoop& Instance();

  void Run();
  void Stop();

  void EnqueueTask(const Object::PyNativeFunctionPtr& task);
  void EnqueueMicroTask(const Object::PyNativeFunctionPtr& task);
  [[nodiscard]] bool Idle() const {
    return macroTaskQueue.empty() && microTaskQueue.empty();
  }
};

}  // namespace tensorslow::Runtime

#endif  // TENSORSLOW_RUNTIME_EVENTLOOP_H