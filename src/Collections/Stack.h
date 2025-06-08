#ifndef TENSORSLOW_COLLECTIONS_STACK_H
#define TENSORSLOW_COLLECTIONS_STACK_H
#include "Collections/List.h"
namespace tensorslow::Collections {
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
}  // namespace tensorslow::Collections
#endif  // TENSORSLOW_COLLECTIONS_STACK_H