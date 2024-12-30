#include "collections/List.h"
#include "collections/Decimal.h"
#include "collections/Integer.h"
#include "collections/Map.h"
#include "collections/String.h"
#include "object/common.h"

#include <algorithm>
#include <stdexcept>

namespace torchlight::collections {

template <typename T>
List<T>::List(Index capacity)
  : capacity(capacity == 0 ? 1 : capacity), items(new T[capacity]) {}

template <typename T>
List<T>::List(Index capacity, std::shared_ptr<T[]> elements)
  : size(capacity), capacity(capacity), items(std::move(elements)) {}

template <typename T>
List<T>::List() : List(INIT_CAPACITY) {}

template <typename T>
T* List<T>::Data() const {
  return items.get();
}

template <typename T>
Index List<T>::Size() const {
  return size;
}

template <typename T>
Index List<T>::Capacity() const {
  return capacity;
}

template <typename T>
void List<T>::Add(T item) {
  if (Full()) {
    Expand();
  }
  items[size] = item;
  size++;
}

template <typename T>
T List<T>::Get(Index index) const {
  if (!ValidIndex(index)) {
    throw std::runtime_error("Get::Index out of range");
  }
  return items[index];
}

template <typename T>
void List<T>::Set(Index index, T element) {
  if (!ValidIndex(index)) {
    throw std::runtime_error("Set::Index out of range");
  }
  items[index] = element;
}

template <typename T>
bool List<T>::Empty() {
  return size == 0;
}

template <typename T>
bool List<T>::ValidIndex(Index index) const {
  return size > 0 && index < size;
}

template <typename T>
bool List<T>::Full() {
  return size == capacity;
}

template <typename T>
void List<T>::Expand(Index leastCapacity) {
  Index newCapacity = leastCapacity;
  std::shared_ptr<T[]> newItems(new T[newCapacity]);
  std::shared_ptr<T[]> oldItems = items;
  items = newItems;
  std::copy(oldItems.get(), oldItems.get() + size, items.get());
  capacity = newCapacity;
}

template <typename T>
void List<T>::Expand() {
  Expand(capacity * 2);
}

template <typename T>
void List<T>::Clear() {
  size = 0;
}

template <typename T>
void List<T>::RemoveAt(Index index) {
  if (!ValidIndex(index)) {
    throw std::runtime_error("RemoveAt::Index out of range");
  }
  std::move(items.get() + index + 1, items.get() + size, items.get() + index);
  size--;
}

template <typename T>
void List<T>::Insert(Index index, T item) {
  if (Full()) {
    Expand();
  }
  if (index > size) {
    throw std::runtime_error("Insert::Index out of range");
  }
  std::move_backward(
    items.get() + index, items.get() + size, items.get() + size + 1
  );
  items[index] = std::move(item);
  size++;
}

template <typename T>
Index List<T>::RemainingCapacity() {
  return capacity - size;
}

template <typename T>
void List<T>::Add(const List<T>& list) {
  if (this == &list) {
    Add(list.Copy());
  } else {
    if (RemainingCapacity() < list.Size()) {
      Expand(size + list.Size());
    }
    std::copy(
      list.items.get(), list.items.get() + list.Size(), items.get() + size
    );
    size += list.Size();
  }
}

template <typename T>
void List<T>::Add(T* items, Index count) {
  if (RemainingCapacity() < count) {
    Expand(size + count);
  }
  std::copy(items, items + count, this->items.get() + size);
  size += count;
}

template <typename T>
void List<T>::AppendElements(T element, Index count) {
  if (RemainingCapacity() < count) {
    Expand(size + count);
  }
  std::fill(items.get() + size, items.get() + size + count, element);
  size += count;
}

template <typename T>
List<T> List<T>::Slice(Index start, Index end) const {
  if (start >= size || end > size || start > end) {
    throw std::runtime_error("Slice::Index out of range");
  }
  return List<T>(end - start, std::shared_ptr<T[]>(items, items.get() + start));
}

template <typename T>
void List<T>::Insert(Index index, List<T>& list) {
  if (!ValidIndex(index)) {
    throw std::runtime_error("Insert::Index out of range");
  }
  if (list.Empty()) {
    return;
  }
  if (RemainingCapacity() < list.Size()) {
    Expand(size + list.Size());
  }
  std::move_backward(
    items.get() + index, items.get() + size, items.get() + size + list.Size()
  );
  std::copy(
    list.items.get(), list.items.get() + list.Size(), items.get() + index
  );

  size += list.Size();
}

template <typename T>
void List<T>::Remove(Index start, Index end) {
  if (start >= size || end > size || start > end) {
    throw std::runtime_error("Remove::Index out of range");
  }
  std::move(items.get() + end, items.get() + size, items.get() + start);
  size -= (end - start);
}

template <typename T>
void List<T>::Reverse() {
  std::reverse(items.get(), items.get() + size);
}

template <typename T>
void List<T>::TrimExcess() {
  if (size < capacity) {
    std::shared_ptr<T[]> newItems(new T[size]);
    std::copy(items.get(), items.get() + size, newItems.get());
    items = newItems;
    capacity = size;
  }
}

template <typename T>
void List<T>::Fill(T item) {
  std::fill(items.get(), items.get() + size, item);
  while (size < capacity) {
    Add(item);
  }
}

template <typename T>
List<T> List<T>::Copy() const {
  List<T> list(size);
  std::copy(items.get(), items.get() + size, list.items.get());
  list.size = size;  // 确保复制后的列表大小正确
  return list;
}

template <typename T>
void List<T>::PopBack() {
  if (size == 0) {
    throw std::runtime_error("PopBack::List is empty");
  }
  size--;
}

template class List<Index>;

template class List<String>;

template class List<Unicode>;

template class List<int32_t>;

template class List<Decimal>;

template class List<Integer>;

extern template class MapEntry<String, object::PyObjPtr>;

template class List<MapEntry<String, object::PyObjPtr>>;

template class List<Byte>;

template class List<object::PyObjPtr>;

template class List<double>;

}  // namespace torchlight::collections