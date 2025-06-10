#include "Runtime/EventLoop.h"
#include <condition_variable>
#include "Object/Container/PyList.h"

namespace tensorslow::Runtime {

EventLoop& EventLoop::Instance() {
  static EventLoop instance;
  return instance;
}

void EventLoop::Run() {
  running = true;
  while (running) {
    std::unique_lock<std::mutex> lock(queueMutex);

    // Process microtasks first
    while (!microTaskQueue.empty()) {
      auto task = microTaskQueue.front();
      microTaskQueue.pop();
      lock.unlock();
      task->Call(Object::CreatePyList());
      lock.lock();
    }

    // Process regular tasks
    if (!macroTaskQueue.empty()) {
      auto task = macroTaskQueue.front();
      macroTaskQueue.pop();
      lock.unlock();
      task->Call(Object::CreatePyList());
      lock.lock();
    } else {
      // Wait for next task or timeout
      taskConditionVar.wait(lock, [this] {
        return !macroTaskQueue.empty() || !microTaskQueue.empty();
      });
    }
  }
}

void EventLoop::Stop() {
  running = false;
}

void EventLoop::EnqueueTask(const Object::PyNativeFunctionPtr& task) {
  std::lock_guard<std::mutex> lock(queueMutex);
  macroTaskQueue.push(task);
}

void EventLoop::EnqueueMicroTask(const Object::PyNativeFunctionPtr& task) {
  std::lock_guard<std::mutex> lock(queueMutex);
  microTaskQueue.push(task);
  taskConditionVar.notify_one();
}

}  // namespace tensorslow::Runtime