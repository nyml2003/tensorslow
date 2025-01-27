#ifndef TORCHLIGHT_MOCKFRONT_TASK_MANAGER_H
#define TORCHLIGHT_MOCKFRONT_TASK_MANAGER_H

#include "ByteCode/PyCode.h"
#include "Collections/Map.h"
#include "Collections/String.h"

#include <functional>

namespace torchlight::MockFront {

using TaskFunction =
  std::function<Object::PyCodePtr(const Collections::String&)>;

class TaskManager {
 public:
  static TaskManager& Instance();

  void RegisterTask(const Collections::String& name, const TaskFunction& task);
  void EnableTask(const Collections::String& name);
  void RunAllEnabledTasks();
  Collections::String test_dir;

 private:
  TaskManager();

  Collections::Map<Collections::String, TaskFunction> tasks;
  Collections::List<Collections::String> enabledTasks;
};

}  // namespace torchlight::MockFront

#endif  // TORCHLIGHT_MOCKFRONT_TASK_MANAGER_H