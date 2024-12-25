#ifndef TORCHLIGHT_COLLECTIONS_STRING_H
#define TORCHLIGHT_COLLECTIONS_STRING_H

#include "collections/common.h"

#include "collections/List.h"

namespace torchlight::collections {

class String {
 private:
  static uint32_t UTF8ToUnicode(const char* str, Index& index);

  List<Unicode> codePoints;

 public:
  explicit String(const char* str);

  explicit String();

  explicit String(Index capacity);

  /**
   * 获取字符串的 UTF-8 编码
   * @return
   */
  [[nodiscard]] const char* ToUTF8() const;

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

  bool operator==(const String& rhs) const;

  void Add(Unicode codePoint);

  [[nodiscard]] String Concat(const String& rhs) const;

  void InplaceConcat(const String& rhs);

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
};

String DoubleToString(double value);

}  // namespace torchlight::collections
#endif  // TORCHLIGHT_COLLECTIONS_STRING_H
