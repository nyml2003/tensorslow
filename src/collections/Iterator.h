#ifndef TORCHLIGHT_COLLECTIONS_ITERATOR_H
#define TORCHLIGHT_COLLECTIONS_ITERATOR_H

#include "collections/List.h"

namespace torchlight::collections {

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

  Iterator(const Iterator& iterator);
  Iterator& operator=(const Iterator& iterator);

  const T Get() const;
  void Next();

  [[nodiscard]] Index GetCurrentIndex() const;
  [[nodiscard]] bool End() const;

  static Iterator Begin(const List<T>& list);
  static Iterator RBegin(const List<T>& list);

  const List<T>& GetList() const;
};

}  // namespace torchlight::collections

#endif