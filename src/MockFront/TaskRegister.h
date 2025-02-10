#ifndef TORCHLIGHT_MOCKFRONT_TASK_REGISTER_H
#define TORCHLIGHT_MOCKFRONT_TASK_REGISTER_H

#include "Collections/String.h"
#include "Collections/StringHelper.h"
#include "MockFront/TaskManager.h"

namespace torchlight::MockFront {
template <typename T>
class TaskRegistrar {
 public:
  explicit TaskRegistrar(const char* _name) {
    Collections::String name = Collections::CreateStringWithCString(_name);
    auto& manager = TaskManager::Instance();
    manager.RegisterTask(name, &T::Run);
    manager.EnableTask(name);
  }
};

#define REGISTER_TASK(className, name) \
  static TaskRegistrar<className> registrar_##className(name);
}  // namespace torchlight::MockFront

#endif