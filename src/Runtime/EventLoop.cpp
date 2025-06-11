#include "Runtime/EventLoop.h"
#include "Object/Container/PyList.h"
#include "Runtime/VirtualMachine.h"

namespace tensorslow::Runtime {

EventLoop& EventLoop::Instance() {
  static EventLoop instance;
  return instance;
}

void EventLoop::Run() {
  running = true;
  std::unique_lock<std::mutex> lock(queueMutex);  // 加锁提前到循环外
  while (running) {
    if (VirtualMachine::Instance().CurrentFrame() != nullptr) {
      continue;
    }

    // 处理 micro task 队列
    while (!microTaskQueue.empty()) {
      auto task = microTaskQueue.front();
      microTaskQueue.pop();
      lock.unlock();
      Evaluator::InvokeCallable(task, Object::CreatePyList());
      lock.lock();
    }

    // 处理 macro task 队列
    if (!macroTaskQueue.empty()) {
      auto task = macroTaskQueue.front();
      macroTaskQueue.pop();
      lock.unlock();
      Evaluator::InvokeCallable(task, Object::CreatePyList());
      lock.lock();
      continue;  // 确保再次处理 micro tasks（可选）
    }

    if (microTaskQueue.empty() && macroTaskQueue.empty()) {
      running = false;  // 主动结束循环
    } else {
      taskConditionVar.wait(lock, [this] {
        return !macroTaskQueue.empty() || !microTaskQueue.empty() || !running;
      });
    }
  }
}

void EventLoop::Stop() {
  running = false;
}

void EventLoop::EnqueueTask(const Object::PyObjPtr& task) {
  std::lock_guard<std::mutex> lock(queueMutex);
  macroTaskQueue.push(task);
}

void EventLoop::EnqueueMicroTask(const Object::PyObjPtr& task) {
  std::lock_guard<std::mutex> lock(queueMutex);
  microTaskQueue.push(task);
  taskConditionVar.notify_one();
}

}  // namespace tensorslow::Runtime