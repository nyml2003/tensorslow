#ifndef TORCHLIGHT_COLLECTIONS_MAP_H
#define TORCHLIGHT_COLLECTIONS_MAP_H
#include "Collections/List.h"
namespace torchlight::Collections {
template <typename K, typename V>
class MapEntry {
 private:
  K key;
  V value;

 public:
  explicit MapEntry(K key, V value);
  explicit MapEntry();
  K Key() { return key; }
  V Value() { return value; }
};
template <typename K, typename V>
class Map {
 private:
  List<MapEntry<K, V>> entries;

  Index IndexOf(K key) const;

 public:
  explicit Map();
  /**
   * 获取键值对的个数
   * @return 键值对的个数
   */
  Index Size();
  /**
   * 判断是否为空
   * @return 是否为空
   */
  bool Empty();
  /**
   * 获取键对应的值
   * @param key 键
   * @return 值
   */
  V Get(K key);
  /**
   * 设置键对应的值
   * @param key 键
   * @param value 值
   */
  void Put(K key, V value) noexcept;
  /**
   * 删除键值对
   * @param key 键
   */
  void Remove(K key);
  /**
   * 判断是否包含某个键
   * @param key 键
   * @return 是否包含
   */
  bool Contains(K key) noexcept;
  /**
   * 清空map
   */
  void Clear();
  /**
   * 获取所有的键
   * @return 键的列表
   */
  List<K> Keys();
  /**
   * 获取所有的值
   * @return 值的列表
   */
  List<V> Values();
  /**
   * 获取所有的键值对
   * @return 键值对的列表
   */
  List<MapEntry<K, V>> Entries();
};

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
Index Map<K, V>::IndexOf(K key) const {
  for (Index i = 0; i < entries.Size(); i++) {
    if (entries.Get(i).Key() == key) {
      return i;
    }
  }
  throw std::runtime_error("Key not found");
}
template <typename K, typename V>
V Map<K, V>::Get(K key) {
  for (Index i = 0; i < entries.Size(); i++) {
    if (entries.Get(i).Key() == key) {
      return entries.Get(i).Value();
    }
  }
  throw std::runtime_error("Key not found");
}
template <typename K, typename V>
void Map<K, V>::Put(K key, V value) noexcept {
  for (Index i = 0; i < entries.Size(); i++) {
    if (entries.Get(i).Key() == key) {
      entries.Set(i, MapEntry<K, V>(key, value));
      return;
    }
  }
  entries.Push(MapEntry<K, V>(key, value));
}
template <typename K, typename V>
void Map<K, V>::Remove(K key) {
  entries.RemoveAt(IndexOf(key));
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
    keys.Push(entries.Get(i).Key());
  }
  return keys;
}
template <typename K, typename V>
List<V> Map<K, V>::Values() {
  List<V> values(entries.Size());
  for (Index i = 0; i < entries.Size(); i++) {
    values.Push(entries.Get(i).Value());
  }
  return values;
}
template <typename K, typename V>
List<MapEntry<K, V>> Map<K, V>::Entries() {
  return entries;
}
}  // namespace torchlight::Collections
#endif  // TORCHLIGHT_UTIL_MAP_H
