#include "collections/Stack.h"
#include "object/common.h"

namespace torchlight::collections {

template <typename T>
void Stack<T>::Push(const T& value) {
  content.Add(value);
}

template <typename T>
T Stack<T>::Pop() {
  T value = content.Get(content.Size() - 1);
  content.PopBack();
  return value;
}

template class Stack<object::PyObjPtr>;

}  // namespace torchlight::collections