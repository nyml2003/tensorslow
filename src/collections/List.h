#ifndef TORCHLIGHT_COLLECTIONS_LIST_H
#define TORCHLIGHT_COLLECTIONS_LIST_H

#include "collections/common.h"

#include <initializer_list>
#include <memory>

namespace torchlight::collections {
const Index INIT_CAPACITY = 10;

template <typename T>
class List {
 private:
  /**
   * 当前列表中元素的个数
   */
  Index size;
  /**
   * 列表的容量，即列表中最多可以存放的元素个数
   * 内存分配时，会分配capacity个元素的空间
   */
  Index capacity;

  /**
   * 列表中的元素
   */
  std::unique_ptr<T[]> elements;

  /**
   * @brief 扩容
   * @details 默认扩容为原来的两倍
   */
  void Expand();

  void Expand(Index newCapacity);

 public:
  /**
   * 构造函数
   * @param capacity 列表的初始容量，默认为 INIT_CAPACITY
   */
  explicit List(Index capacity = INIT_CAPACITY);

  explicit List(Index count, const T* stream);

  explicit List(Index count, T element);

  List(std::initializer_list<T> list);

  List(const List<T>& other);

  List(List<T>&& other) noexcept;

  List<T>& operator=(const List<T>& other);

  List<T>& operator=(List<T>&& other) noexcept;

  /**
   * 析构函数
   */
  ~List();

  /**
   * 获取列表中元素的个数
   * @return 元素个数
   */
  [[nodiscard]] Index Size() const;

  /**
   * 获取列表的容量
   * @return 容量
   */
  [[nodiscard]] Index Capacity() const;

  T* Data();

  /**
   * @brief 返回列表末尾的元素
   * @return 第一个元素
   */
  T First() const;

  /**
   * @brief 移除列表首元素
   * @return 被移除的元素
   */
  T Shift();

  /**
   * @brief 在列表前端添加元素
   * @param element 要添加的元素
   */
  void Unshift(T element);

  /**
   * @brief 返回列表末尾的元素
   * @return 最后一个元素
   */
  T Last() const;

  /**
   * @brief 在列表末端添加元素
   * @param element 要添加的元素
   */
  void Push(T element);

  /**
   * @brief 移除列表末尾的元素
   * @return 被移除的元素
   */
  T Pop();

  /**
   * @brief 合并列表
   * @details 本身列表不会改变，返回一个新的列表
   * @param list 要合并的列表
   * @return 合并后的新列表
   */
  List<T> Add(const List<T>& list);

  /**
   * @brief 将新的列表拷贝添加到列表末尾
   * @param list 要添加的列表
   */
  void Concat(const List<T>& list);

  /**
   * @brief 清空列表
   */
  void Clear();

  /**
   * @brief 返回列表的切片, 是浅拷贝
   * @param start 切片的起始索引（包含）
   * @param end 切片的结束索引（不包含）
   * @return 列表在 [start, end) 之间的元素组成的列表
   */
  List<T> Slice(Index start, Index end) const;

  /**
   * @brief 移除指定位置的元素
   * @param index 要移除的元素的索引
   */
  void RemoveAt(Index index);

  /**
   * @brief 移除指定区间[start, end)的元素
   * @param start 移除区间的起始索引（包含）
   * @param end 移除区间的结束索引（不包含）
   */
  void RemoveRange(Index start, Index end);

  /**
   * @brief 反转列表
   */
  void Reverse();

  /**
   * @brief 减小列表的容量以匹配其元素数量
   */
  void TrimExcess();

  /**
   * @brief 列表是否为空
   * @return 如果列表为空，则为 true; 否则为 false
   */
  [[nodiscard]] bool Empty() const noexcept;

  /**
   * @brief 列表是否已满
   * @return 如果列表已满，则为 true; 否则为 false
   */
  [[nodiscard]] bool Full() const noexcept;

  /**
   * @brief 判断索引是否有效
   * @param index 要检查的索引
   * @return 如果索引有效，则为 true; 否则为 false
   */
  [[nodiscard]] bool ValidIndex(Index index) const noexcept;

  /**
   * @brief 获取指定位置的元素
   * @param index 要获取的元素的索引
   * @return 指定位置的元素
   */
  [[nodiscard]] T Get(Index index) const;

  T& operator[](Index index);

  const T& operator[](Index index) const;

  /**
   * @brief 设置指定位置的元素
   * @param index 要设置的元素的索引
   * @param element 要设置的新元素
   */
  void Set(Index index, T element);

  /**
   * @brief 填充列表为指定元素，
   * @details 保证执行完后列表是一个size大小的元素全为element的列表
   * @param element 要填充的元素
   */
  void Fill(T element);

  /**
   * @brief 深拷贝当前列表
   * @return 深拷贝后的列表
   */
  List<T> Copy() const;
};

}  // namespace torchlight::collections

#endif  // TORCHLIGHT_COLLECTIONS_LIST_H