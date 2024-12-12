#ifndef TORCHLIGHT_COLLECTIONS_STACK_H
#define TORCHLIGHT_COLLECTIONS_STACK_H

#include "collections/List.h"

namespace torchlight::collections {
template <typename T>
class Stack {
 private:
  List<T> content;

 public:
  void Push(const T& value);
  T Pop();
};
}  // namespace torchlight::collections

#endif  // TORCHLIGHT_STACK_H