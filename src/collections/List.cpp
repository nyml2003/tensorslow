#include "collections/Decimal.h"
#include "collections/Integer.h"
#include "collections/List.h"
#include "collections/Map.h"
#include "collections/String.h"
#include "object/PyObject.h"


#include <algorithm>
#include <stdexcept>

namespace torchlight::collections {

template <typename T>
List<T>::~List() = default;

template <typename T>
List<T>::List(Index capacity) : size(0), capacity(capacity) {
  if (capacity > 0) {
    elements = std::make_unique<T[]>(capacity);
  }
}

template <typename T>
List<T>::List(Index count, const T* stream) : size(count) {
  if (count == 0) {
    throw std::runtime_error("List::List: count is 0");
  }
  capacity = count;
  elements = std::make_unique<T[]>(count);
  std::copy(stream, stream + count, elements.get());
}

template <typename T>
List<T>::List(Index count, T element) : size(count) {
  if (count == 0) {
    throw std::runtime_error("List::List: count is 0");
  }
  capacity = count;
  elements = std::make_unique<T[]>(count);
  std::fill(elements.get(), elements.get() + count, element);
}

template <typename T>
List<T>::List(std::initializer_list<T> list)
  : size(list.size()),
    capacity(list.size()),
    elements(std::make_unique<T[]>(list.size())) {
  std::copy(list.begin(), list.end(), elements.get());
}

template <typename T>
List<T>::List(const List<T>& other)
  : size(other.size),
    capacity(other.capacity),
    elements(std::make_unique<T[]>(other.capacity)) {
  std::copy(other.elements.get(), other.elements.get() + size, elements.get());
}

template <typename T>
List<T>::List(List<T>&& other) noexcept
  : size(other.size),
    capacity(other.capacity),
    elements(std::move(other.elements)) {
  other.size = 0;
  other.capacity = 0;
}

template <typename T>
List<T>& List<T>::operator=(List<T>&& other) noexcept {
  if (this != &other) {
    size = other.size;
    capacity = other.capacity;
    elements = std::move(other.elements);
    other.size = 0;
    other.capacity = 0;
  }
  return *this;
}

template <typename T>
List<T>& List<T>::operator=(const List<T>& other) {
  if (this != &other) {
    size = other.size;
    capacity = other.capacity;
    elements = std::make_unique<T[]>(other.capacity);
    std::copy(
      other.elements.get(), other.elements.get() + size, elements.get()
    );
  }
  return *this;
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
T List<T>::First() const {
  if (Empty()) {
    throw std::runtime_error("List::First: List is empty");
  }
  return elements[0];
}

template <typename T>
T List<T>::Shift() {
  if (Empty()) {
    throw std::runtime_error("List::Shift: List is empty");
  }
  T element = elements[0];
  std::move(elements.get() + 1, elements.get() + size, elements.get());
  size--;
  return element;
}

template <typename T>
void List<T>::Unshift(T element) {
  if (Full()) {
    Expand();
  }
  std::move(elements.get(), elements.get() + size, elements.get() + 1);
  elements[0] = element;
  size++;
}

template <typename T>
T List<T>::Last() const {
  if (Empty()) {
    throw std::runtime_error("List::Last: List is empty");
  }
  return elements[size - 1];
}

template <typename T>
void List<T>::Push(T element) {
  if (Full()) {
    Expand();
  }
  elements[size] = element;
  size++;
}

template <typename T>
T List<T>::Pop() {
  if (Empty()) {
    throw std::runtime_error("List::Pop: List is empty");
  }
  size--;
  return elements[size];
}

template <typename T>
List<T> List<T>::Add(const List<T>& list) {
  List<T> newList(size + list.size);
  std::copy(elements.get(), elements.get() + size, newList.elements.get());
  std::copy(
    list.elements.get(), list.elements.get() + list.size,
    newList.elements.get() + size
  );
  newList.size = size + list.size;
  return newList;
}

template <typename T>
void List<T>::Concat(const List<T>& list) {
  if (size + list.size > capacity) {
    Expand(size + list.size);
  }
  std::copy(
    list.elements.get(), list.elements.get() + list.size, elements.get() + size
  );
  size += list.size;
}

template <typename T>
void List<T>::Clear() {
  size = 0;
}

template <typename T>
List<T> List<T>::Slice(Index start, Index end) const {
  if (start >= size || end > size || start >= end) {
    throw std::runtime_error("List::Slice::Index out of range");
  }
  List<T> list(end - start);
  std::copy(elements.get() + start, elements.get() + end, list.elements.get());
  list.size = end - start;
  return list;
}

template <typename T>
void List<T>::RemoveAt(Index index) {
  if (!ValidIndex(index)) {
    throw std::runtime_error("List::RemoveAt::Index out of range");
  }
  std::move(
    elements.get() + index + 1, elements.get() + size, elements.get() + index
  );
  size--;
}

template <typename T>
void List<T>::RemoveRange(Index start, Index end) {
  if (start >= size || end > size || start > end) {
    throw std::runtime_error("List::RemoveRange::Index out of range");
  }
  std::move(
    elements.get() + end, elements.get() + size, elements.get() + start
  );
  size -= (end - start);
}

template <typename T>
void List<T>::Reverse() {
  std::reverse(elements.get(), elements.get() + size);
}

template <typename T>
void List<T>::TrimExcess() {
  if (size == 0) {
    capacity = 0;
    elements.reset();
    return;
  }
  if (size == capacity) {
    return;
  }
  std::unique_ptr<T[]> newElements = std::make_unique<T[]>(size);
  std::copy(elements.get(), elements.get() + size, newElements.get());
  elements = std::move(newElements);
  capacity = size;
}

template <typename T>
bool List<T>::Empty() const noexcept {
  return size == 0;
}

template <typename T>
bool List<T>::ValidIndex(Index index) const noexcept {
  return size > 0 && index < size;
}

template <typename T>
bool List<T>::Full() const noexcept {
  return size >= capacity;
}

template <typename T>
T List<T>::Get(Index index) const {
  if (!ValidIndex(index)) {
    throw std::out_of_range("List::Get: Index out of range");
  }
  return elements[index];
}

template <typename T>
T& List<T>::operator[](Index index) {
  if (!ValidIndex(index)) {
    throw std::out_of_range("List::operator[]: Index out of range");
  }
  return elements[index];
}

template <typename T>
const T& List<T>::operator[](Index index) const {
  if (!ValidIndex(index)) {
    throw std::out_of_range("List::operator[]: Index out of range");
  }
  return elements[index];
}

template <typename T>
void List<T>::Set(Index index, T element) {
  if (!ValidIndex(index)) {
    throw std::runtime_error("List::Set::Index out of range");
  }
  elements[index] = element;
}

template <typename T>
void List<T>::Expand() {
  Index newCapacity = std::max(capacity * 2, INIT_CAPACITY);
  std::unique_ptr<T[]> newElements = std::make_unique<T[]>(newCapacity);
  std::copy(elements.get(), elements.get() + size, newElements.get());
  elements = std::move(newElements);
  capacity = newCapacity;
}

template <typename T>
void List<T>::Expand(Index newCapacity) {
  std::unique_ptr<T[]> newElements = std::make_unique<T[]>(newCapacity);
  std::copy(elements.get(), elements.get() + size, newElements.get());
  elements = std::move(newElements);
  capacity = newCapacity;
}

template <typename T>
void List<T>::Fill(T element) {
  if (capacity == 0) {
    throw std::runtime_error("List::Fill: List is empty");
  }
  std::fill(elements.get(), elements.get() + capacity, element);
  size = capacity;
}

template <typename T>
List<T> List<T>::Copy() const {
  List<T> newList(size);
  std::copy(elements.get(), elements.get() + size, newList.elements.get());
  newList.size = size;
  return newList;
}

template <typename T>
T* List<T>::Data() {
  return elements.get();
}

template class List<Index>;

template class List<String>;

template class List<Unicode>;

template class List<Byte>;

template class List<int32_t>;

template class List<Decimal>;

template class List<Integer>;

extern template class MapEntry<object::PyObjPtr, object::PyObjPtr>;

template class List<MapEntry<object::PyObjPtr, object::PyObjPtr>>;

template class List<object::PyObjPtr>;

// template class List<double>;

// template class List<int*>;

}  // namespace torchlight::collections