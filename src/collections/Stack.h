#ifndef TORCHLIGHT_COLLECTIONS_STACK_H
#define TORCHLIGHT_COLLECTIONS_STACK_H
#include "Collections/List.h"
namespace torchlight::Collections {
template <typename T>
class Stack {
 private:
  List<T> content;

 public:
  void Push(const T& value) { content.Push(value); }
  T Pop() { return content.Pop(); }
  List<T> GetContent() const { return content; }
};
}  // namespace torchlight::Collections
#endif  // TORCHLIGHT_STACK_H