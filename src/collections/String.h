#ifndef TORCHLIGHT_COLLECTIONS_STRING_H
#define TORCHLIGHT_COLLECTIONS_STRING_H

#include "collections/Bytes.h"
#include "collections/List.h"
#include "collections/common.h"

namespace torchlight::collections {

class String {
 private:
  List<Unicode> codePoints;

 public:
  explicit String(const List<Unicode>& codePoints);
  explicit String() = default;

  [[nodiscard]] List<Unicode> Data() const;

  /**
   * 用于将字符串数组连接起来
   * @param j
   * @return
   */
  [[nodiscard]] String Join(String& joiner) const;

  /**
   * 用于将字符串分割成多个子串
   * @param d
   * @return
   */
  [[nodiscard]] List<String> Split(String& delimiter) const;

  /**
   * 找到start开始的第一个String的位置
   * @param sub
   * @return
   */
  [[nodiscard]] Index Find(String& sub, Index start = 0) const;

  [[nodiscard]] String Concat(const String& rhs) const;

  String InplaceConcat(const String& rhs);

  [[nodiscard]] String Copy() const;

  [[nodiscard]] Unicode Get(Index index) const;

  [[nodiscard]] Index Size() const;

  void Insert(Index index, Unicode codePoint);

  void RemoveAt(Index index);

  void Clear();

  [[nodiscard]] String Slice(Index start, Index end) const;

  void Reverse();

  [[nodiscard]] bool Equal(const String& rhs) const;

  [[nodiscard]] bool GreaterThan(const String& rhs) const;

  [[nodiscard]] bool LessThan(const String& rhs) const;

  [[nodiscard]] bool GreaterThanOrEqual(const String& rhs) const;

  [[nodiscard]] bool LessThanOrEqual(const String& rhs) const;

  [[nodiscard]] bool NotEqual(const String& rhs) const;

  bool operator==(const String& rhs) const;
};

}  // namespace torchlight::collections

#endif  // TORCHLIGHT_COLLECTIONS_STRING_H
