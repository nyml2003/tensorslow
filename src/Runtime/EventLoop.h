#ifndef TENSORSLOW_RUNTIME_EVENTLOOP_H
#define TENSORSLOW_RUNTIME_EVENTLOOP_H

#include <mutex>
#include <queue>
#include "Object/Core/PyObject.h"

namespace tensorslow::Runtime {

class EventLoop {
 private:
  std::queue<Object::PyObjPtr> macroTaskQueue;  // 宏任务队列
  std::queue<Object::PyObjPtr> microTaskQueue;  // 微任务队列
  std::mutex queueMutex;
  std::condition_variable taskConditionVar;
  bool running = false;

 public:
  static EventLoop& Instance();

  void Run();
  void Stop();

  void EnqueueTask(const Object::PyObjPtr& task);
  void EnqueueMicroTask(const Object::PyObjPtr& task);
  [[nodiscard]] bool Idle() const {
    return macroTaskQueue.empty() && microTaskQueue.empty();
  }
};

}  // namespace tensorslow::Runtime

#endif  // TENSORSLOW_RUNTIME_EVENTLOOP_H