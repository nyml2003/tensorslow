#include "Collections/BytesHelper.h"
#include "Collections/StringHelper.h"
#include "MockFront/TaskManager.h"
#include "Object/PyObject.h"
#include "MockFront/utils.h"

#include <memory>

namespace torchlight::MockFront {

void CleanTestDir() {
  system(("rm -rf " + Collections::ToCppString(TaskManager::Instance().test_dir)
  )
           .c_str());
  system(("mkdir -p " +
          Collections::ToCppString(TaskManager::Instance().test_dir))
           .c_str());
}

void WriteToFile(
  const Collections::String& taskName,
  const Object::PyCodePtr& code
) {
  Object::DebugPrint(code);
  Collections::Bytes data =
    std::dynamic_pointer_cast<Object::PyBytes>(code->_serialize_())->Value();
  Collections::String filename = CreateFilename(taskName);
  Collections::Write(data, filename);
}

Collections::String CreateFilename(const Collections::String& name) {
  return TaskManager::Instance().test_dir.Add(name).Add(
    Collections::CreateStringWithCString(".pyc")
  );
}

}  // namespace torchlight::MockFront