#ifndef TORCHLIGHT_COLLECTIONS_LIST_H
#define TORCHLIGHT_COLLECTIONS_LIST_H

#include "collections/common.h"

#include <memory>

namespace torchlight::collections {
const Index INIT_CAPACITY = 10;

template <typename T>
class List {
 private:
  /**
   * 当前列表中元素的个数
   */
  Index size{};
  /**
   * 列表的容量，即列表中最多可以存放的元素个数
   * 内存分配时，会分配capacity个元素的空间
   */
  Index capacity{};

  /**
   * 列表中的元素
   */
  std::shared_ptr<T[]> items;

  /**
   * @brief 计算已分配内存还能容纳的元素个数
   * @return 已分配内存还能容纳的元素个数
   */
  Index RemainingCapacity();

  /**
   * @brief 扩容
   */
  void Expand();

 public:
  /**
   * @brief 扩容
   * @param leastCapacity 这次扩容后，列表的容量至少为leastCapacity
   */
  void Expand(Index leastCapacity);

  /**
   * 构造函数
   * @param capacity 列表的容量
   */
  explicit List();

  /**
   * 构造函数
   * @param capacity 列表的容量
   */
  explicit List(Index capacity);

  /**
   * 构造函数
   * @param capacity 列表的容量, 传入elements的长度
   * @param elements 列表中的元素
   */
  explicit List(Index capacity, std::shared_ptr<T[]> elements);

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

  /**
   * @brief 将 item 添加到列表末尾
   * @param item
   */
  void Add(T item);

  /**
   * @brief 将集合添加到列表末尾
   * @param list
   */
  void Add(const List<T>& list);

  /**
   * @brief 清空列表
   */
  void Clear();

  /**
   * @brief 返回列表的切片
   * @param start
   * @param end
   * @return 列表在 [start, end) 之间的元素
   */
  List<T> Slice(Index start, Index end) const;

  /**
   * @brief 插入元素到指定位置
   * @param index
   * @param item
   */
  void Insert(Index index, T item);

  /**
   * @brief 插入集合到指定位置
   * @param index
   * @param list
   */
  void Insert(Index index, List<T>& list);

  /**
   * @brief 移除指定位置的元素
   * @param index
   */
  void RemoveAt(Index index);

  /**
   * @brief 移除指定区间[start, end)的元素
   * @param start
   * @param end
   */
  void Remove(Index start, Index end);

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
  bool Empty();

  /**
   * @brief 列表是否已满
   * @return 如果列表已满，则为 true; 否则为 false
   */
  bool Full();

  /**
   * @brief 判断索引是否有效
   * @param index
   * @return 如果索引有效，则为 true; 否则为 false
   */
  [[nodiscard]] bool ValidIndex(Index index) const;

  /**
   * @brief 获取指定位置的元素
   * @param index
   * @return
   */
  [[nodiscard]] T Get(Index index) const;

  /**
   * @brief 设置指定位置的元素
   * @param index
   * @param item
   */
  void Set(Index index, T item);

  /**
   * @brief 填充
   */
  void Fill(T item);

  List<T> Copy() const;

  void PopBack();

  class Iterator {
   private:
    const List<T>& list;
    Index index{};
    bool end{};
    bool order{};  // true: forward, false: backward

    explicit Iterator(const List<T>& _list) : list(_list) {}

    Iterator& SetIndex(Index _index) {
      this->index = _index;
      return *this;
    }

    Iterator& SetEnd(bool _end) {
      this->end = _end;
      return *this;
    }

    Iterator& SetOrder(bool _order) {
      this->order = _order;
      return *this;
    }

   public:
    Iterator(Iterator& it) : list(it.list), index(it.index), end(it.end) {}

    Iterator() = delete;

    Iterator& operator=(const Iterator& it) {
      if (this == &it) {
        return *this;
      }
      index = it.index;
      end = it.end;
      return *this;
    }

    T Get() { return list.Get(index); }

    Iterator& Next() {
      if (order) {
        if (index == list.Size() - 1) {
          end = true;
        } else {
          index++;
        }
      } else {
        if (index == 0) {
          end = true;
        } else {
          index--;
        }
      }
      return *this;
    }

    Index Index() { return index; }

    bool End() { return end; }

    static Iterator Begin(const List<T>& list) {
      Iterator it(list);
      it.SetIndex(0).SetOrder(true);
      if (list.Size() == 0) {
        it.SetEnd(true);
      } else {
        it.SetEnd(false);
      }
      return it;
    }

    static Iterator RBegin(const List<T>& list) {
      Iterator it(list);
      it.SetIndex(list.Size() - 1).SetOrder(false);
      if (list.Size() == 0) {
        it.SetEnd(true);
      } else {
        it.SetEnd(false);
      }
      return it;
    }
  };

  using IteratorPtr = std::shared_ptr<Iterator>;
};

}  // namespace torchlight::collections

#endif  // TORCHLIGHT_DATASTRUCTURE_LIST_H
