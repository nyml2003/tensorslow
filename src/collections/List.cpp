#include "collections/Decimal.h"
#include "collections/Integer.h"
#include "collections/List.h"
#include "collections/Map.h"
#include "collections/String.h"
#include "object/common.h"


#include <stdexcept>

namespace torchlight::collections {

template <typename T>
List<T>::List(Index capacity) : capacity(capacity) {
  if (capacity == 0) {
    capacity = 1;
  }
  items = std::shared_ptr<T[]>(new T[capacity], std::default_delete<T[]>());
}

template <typename T>
List<T>::List(Index capacity, std::shared_ptr<T[]> elements)
  : size(capacity), capacity(capacity), items(elements) {}

template <typename T>
List<T>::List() : List(INIT_CAPACITY) {
  items = std::shared_ptr<T[]>(new T[capacity], std::default_delete<T[]>());
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
  std::shared_ptr<T[]> newItems(new T[newCapacity], std::default_delete<T[]>());
  std::shared_ptr<T[]> oldItems = items;
  items = newItems;
  for (Index i = 0; i < size; i++) {
    items[i] = oldItems[i];
  }
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
  for (Index i = index; i < size - 1; i++) {
    items[i] = items[i + 1];
  }
  size--;
}

template <typename T>
void List<T>::Insert(Index index, T item) {
  if (Full()) {
    Expand();
  }
  if (!ValidIndex(index)) {
    throw std::runtime_error("Insert::Index out of range");
  }
  size++;
  for (Index i = size; i > index; i--) {
    items[i] = items[i - 1];
  }
  items[index] = item;
}

template <typename T>
Index List<T>::RemainingCapacity() {
  return capacity - size;
}

template <typename T>
void List<T>::Add(const List<T>& list) {
  if (RemainingCapacity() < list.Size()) {
    Expand(size + list.Size());
  }
  size += list.Size();
  for (Index i = 0; i < list.Size(); i++) {
    items[size - list.Size() + i] = list.Get(i);
  }
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
  for (Index i = size; i > index; i--) {
    items[i + list.Size() - 1] = items[i - 1];
  }
  for (Index i = 0; i < list.Size(); i++) {
    items[index + i] = list.Get(i);
  }
  size += list.Size();
}

template <typename T>
void List<T>::Remove(Index start, Index end) {
  if (start >= size || end > size || start > end) {
    throw std::runtime_error("Remove::Index out of range");
  }
  for (Index i = 0; i < size - end; i++) {
    items[start + i] = items[end + i];
  }
  size -= end - start;
}

template <typename T>
void List<T>::Reverse() {
  for (Index i = 0; i < size / 2; i++) {
    T temp = items[i];
    items[i] = items[size - i - 1];
    items[size - i - 1] = temp;
  }
}

template <typename T>
void List<T>::TrimExcess() {
  if (size < capacity) {
    std::shared_ptr<T[]> newItems(new T[size], std::default_delete<T[]>());
    for (Index i = 0; i < size; i++) {
      newItems[i] = items[i];
    }
    items = newItems;
    capacity = size;
  }
}

template <typename T>
void List<T>::Fill(T value) {
  for (Index i = 0; i < size; i++) {
    items[i] = value;
  }
  for (Index i = size; i < capacity; i++) {
    Add(value);
  }
}

template <typename T>
List<T> List<T>::Copy() const {
  List<T> list(size);
  for (Index i = 0; i < size; i++) {
    list.Add(items[i]);
  }
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

// extern template class MapEntry<String, String>;

// template class List<MapEntry<String, String>>;

// template class List<int>;

// template class List<std::shared_ptr<int>>;

// template class List<Byte>;

// template class List<object::PyObjPtr>;

// template class List<object::PyStrPtr>;
}  // namespace torchlight::collections