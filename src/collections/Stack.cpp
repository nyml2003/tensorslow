#include "collections/Stack.h"
#include "object/common.h"

namespace torchlight::collections {

template <typename T>
void Stack<T>::Push(const T& value) {
  content.Push(value);
}

template <typename T>
T Stack<T>::Pop() {
  return content.Pop();
}

template class Stack<object::PyObjPtr>;

}  // namespace torchlight::collections