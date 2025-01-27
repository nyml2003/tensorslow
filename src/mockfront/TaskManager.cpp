#include "Collections/Iterator.h"
#include "Collections/StringHelper.h"
#include "MockFront/utils.h"
#include "TaskManager.h"

#include <iostream>

namespace torchlight::MockFront {

TaskManager& TaskManager::Instance() {
  static TaskManager instance;
  return instance;
}

void TaskManager::RegisterTask(
  const Collections::String& name,
  const TaskFunction& task
) {
  tasks.Put(name, task);
}

void TaskManager::EnableTask(const Collections::String& name) {
  enabledTasks.Push(name);
}

void TaskManager::RunAllEnabledTasks() {
  CleanTestDir();
  for (auto it =
         Collections::Iterator<Collections::String>::Begin(enabledTasks);
       !it.End(); it.Next()) {
    auto taskName = it.Get();
    std::cout << "Running task: " << Collections::ToCppString(taskName)
              << std::endl;
    auto task = tasks.Get(taskName);
    auto bytes = task(taskName);
    WriteToFile(taskName, bytes);
  }
}

TaskManager::TaskManager()
  : test_dir(Collections::CreateStringWithCString("/app/test/integration/")) {}

}  // namespace torchlight::MockFront