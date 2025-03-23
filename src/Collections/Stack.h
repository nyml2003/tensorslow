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
  T Top() const { return content.Last(); }
  List<T> Top(Index k) { return content.Pop(k); }
  [[nodiscard]] bool Empty() const { return content.Empty(); }
  [[nodiscard]] Index Size() const { return content.Size(); }
};
}  // namespace torchlight::Collections
#endif  // TORCHLIGHT_STACK_H