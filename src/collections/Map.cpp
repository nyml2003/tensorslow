#include "collections/Map.h"
#include "collections/List.h"
#include "collections/String.h"
#include "object/PyObject.h"

#include <stdexcept>

namespace torchlight::collections {

extern template class List<MapEntry<String, object::PyObjPtr>>;

extern template class List<String>;

template <typename K, typename V>
MapEntry<K, V>::MapEntry(K key, V value) : key(key), value(value) {}

template <typename K, typename V>
MapEntry<K, V>::MapEntry() : key(K()), value(V()) {}

template <typename K, typename V>
Map<K, V>::Map() : entries() {}

template <typename K, typename V>

Index Map<K, V>::Size() {
  return entries.Size();
}

template <typename K, typename V>
bool Map<K, V>::Empty() {
  return entries.Empty();
}

template <typename K, typename V>
std::optional<Index> Map<K, V>::IndexOf(K key) noexcept {
  for (Index i = 0; i < entries.Size(); i++) {
    // TODO: key应该需要重载==运算符
    if (entries.Get(i).Key() == key) {
      return i;
    }
  }
  return std::nullopt;
}

template <typename K, typename V>
V Map<K, V>::Get(K key) {
  auto index = IndexOf(key);
  if (index == std::nullopt) {
    throw std::runtime_error("Key not found");
  }
  return entries.Get(index.value()).Value();
}

template <typename K, typename V>
void Map<K, V>::Put(K key, V value) noexcept {
  auto index = IndexOf(key);
  if (index == std::nullopt) {
    entries.Add(MapEntry<K, V>(key, value));
  } else {
    if (entries.Get(index.value()).Value() == value) {
      return;
    }
    entries.Set(index.value(), MapEntry<K, V>(key, value));
  }
}
template <typename K, typename V>
void Map<K, V>::Remove(K key) {
  auto index = IndexOf(key);
  if (index == std::nullopt) {
    throw std::runtime_error("Key not found");
  }
  entries.RemoveAt(index.value());
}

template <typename K, typename V>
void Map<K, V>::Clear() {
  entries.Clear();
}

template <typename K, typename V>
bool Map<K, V>::Contains(K key) noexcept {
  for (Index i = 0; i < entries.Size(); i++) {
    if (entries.Get(i).Key() == key) {
      return true;
    }
  }
  return false;
}

template <typename K, typename V>
List<K> Map<K, V>::Keys() {
  List<K> keys(entries.Size());
  for (Index i = 0; i < entries.Size(); i++) {
    keys.Add(entries.Get(i).Key());
  }
  return keys;
}

template <typename K, typename V>
List<V> Map<K, V>::Values() {
  List<V> values(entries.Size());
  for (Index i = 0; i < entries.Size(); i++) {
    values.Add(entries.Get(i).Value());
  }
  return values;
}

template <typename K, typename V>
List<MapEntry<K, V>> Map<K, V>::Entries() {
  return entries;
}

template class Map<String, object::PyObjPtr>;
template class MapEntry<String, object::PyObjPtr>;

}  // namespace torchlight::collections