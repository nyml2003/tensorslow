#ifndef TORCHLIGHT_COLLECTIONS_ITERATOR_H
#define TORCHLIGHT_COLLECTIONS_ITERATOR_H
#include "Collections/List.h"
namespace torchlight::Collections {
template <typename T>
class Iterator {
 private:
  enum class IteratorOrder { Forward, Reverse };
  const List<T>& listRef;  // 常量列表引用
  Index currentIndex;      // 当前索引
  bool isEnd;              // 是否到达末尾
  IteratorOrder order;     // 迭代器顺序
 public:
  explicit Iterator(const List<T>& list, Index index, IteratorOrder order);
  Iterator() = delete;
  ~Iterator() = default;
  Iterator(Iterator&& other) noexcept = delete;
  Iterator& operator=(Iterator&& other) noexcept = delete;
  Iterator(const Iterator& iterator);
  Iterator& operator=(const Iterator& iterator);
  T Get() const;
  void Next();
  [[nodiscard]] Index GetCurrentIndex() const;
  [[nodiscard]] bool End() const;
  [[nodiscard]] bool First() const;
  static Iterator Begin(const List<T>& list);
  static Iterator RBegin(const List<T>& list);
  [[nodiscard]] const List<T>& GetList() const;
  List<T> Advance(Index count);
  List<T> Preview(Index count);
  Iterator Copy() const;
};

template <typename T>
Iterator<T>::Iterator(const List<T>& list, Index index, IteratorOrder order)
  : listRef(list), currentIndex(index), isEnd(list.Size() == 0), order(order) {}
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
T Iterator<T>::Get() const {
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
bool Iterator<T>::First() const {
  switch (order) {
    case IteratorOrder::Forward:
      return currentIndex == 0;
    case IteratorOrder::Reverse:
      return currentIndex == listRef.Size() - 1;
  }
  return false;
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
template <typename T>
List<T> Iterator<T>::Advance(Index count) {
  List<T> result;
  for (Index i = 0; i < count; i++) {
    if (isEnd) {
      break;
    }
    result.Push(Get());
    Next();
  }
  return result;
}
template <typename T>
Iterator<T> Iterator<T>::Copy() const {
  return Iterator(listRef, currentIndex, order);
}
template <typename T>
List<T> Iterator<T>::Preview(Index count) {
  List<T> result;
  auto copy = Copy();
  for (Index i = 0; i < count; i++) {
    if (copy.End()) {
      break;
    }
    result.Push(copy.Get());
    copy.Next();
  }
  return result;
}

}  // namespace torchlight::Collections
#endif