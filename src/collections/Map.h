#ifndef TORCHLIGHT_COLLECTIONS_MAP_H
#define TORCHLIGHT_COLLECTIONS_MAP_H

#include "collections/List.h"

#include <optional>

namespace torchlight::collections {

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

  std::optional<uint64_t> IndexOf(K key) noexcept;

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
}  // namespace torchlight::collections

#endif  // TORCHLIGHT_UTIL_MAP_H
