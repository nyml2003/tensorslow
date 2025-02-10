#ifndef TORCHLIGHT_MOCKFRONT_UTILS_H
#define TORCHLIGHT_MOCKFRONT_UTILS_H

#include "ByteCode/PyCode.h"
#include "Collections/String.h"

namespace torchlight::MockFront {

void CleanTestDir();

void WriteToFile(
  const Collections::String& taskName,
  const Object::PyCodePtr& code
);

Collections::String CreateFilename(const Collections::String& name);

}  // namespace torchlight::MockFront

#endif