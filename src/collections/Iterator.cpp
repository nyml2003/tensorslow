#include "collections/Iterator.h"

#include <stdexcept>
#include "collections/Map.h"
#include "object/common.h"

namespace torchlight::collections {

template <typename T>
Iterator<T>::Iterator(const List<T>& list, Index index, IteratorOrder order)
  : listRef(list), currentIndex(index), order(order), isEnd(list.Size() == 0) {}

template <typename T>
Iterator<T>::Iterator(const Iterator<T>& iterator)
  : listRef(iterator.listRef),
    currentIndex(iterator.currentIndex),
    isEnd(iterator.isEnd),
    order(iterator.order) {}

template <typename T>
Iterator<T>& Iterator<T>::operator=(const Iterator<T>& iterator) {
  if (this != &iterator) {
    currentIndex = iterator.currentIndex;
    isEnd = iterator.isEnd;
    order = iterator.order;
  }
  return *this;
}

template <typename T>
const T Iterator<T>::Get() const {
  if (isEnd) {
    throw std::out_of_range("Iterator is at the end");
  }
  return listRef.Get(currentIndex);
}

template <typename T>
void Iterator<T>::Next() {
  if (isEnd) {
    return;
  }
  if (order == IteratorOrder::Forward) {
    if (currentIndex < listRef.Size() - 1) {
      currentIndex++;
    } else {
      isEnd = true;
    }
  } else {
    if (currentIndex > 0) {
      currentIndex--;
    } else {
      isEnd = true;
    }
  }
}

template <typename T>
Index Iterator<T>::GetCurrentIndex() const {
  return currentIndex;
}

template <typename T>
bool Iterator<T>::End() const {
  return isEnd;
}

template <typename T>
Iterator<T> Iterator<T>::Begin(const List<T>& list) {
  return Iterator(list, 0, IteratorOrder::Forward);
}

template <typename T>
Iterator<T> Iterator<T>::RBegin(const List<T>& list) {
  return Iterator(list, list.Size() - 1, IteratorOrder::Reverse);
}

template <typename T>
const List<T>& Iterator<T>::GetList() const {
  return listRef;
}

template class Iterator<int32_t>;

template class Iterator<uint32_t>;

extern template class MapEntry<object::PyObjPtr, object::PyObjPtr>;

template class Iterator<MapEntry<object::PyObjPtr, object::PyObjPtr>>;

}  // namespace torchlight::collections