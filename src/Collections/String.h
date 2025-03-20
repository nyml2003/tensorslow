#ifndef TORCHLIGHT_COLLECTIONS_STRING_H
#define TORCHLIGHT_COLLECTIONS_STRING_H
#include "Collections/List.h"

namespace torchlight::Collections {
class String {
 private:
  List<Unicode> codePoints;

 public:
  explicit String(const List<Unicode>& codePoints);
  explicit String();
  String(const String& other);
  String(String& other);
  String(String&& other) noexcept;
  String& operator=(const String& other);
  String& operator=(String&& other) noexcept;
  ~String();
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
  [[nodiscard]] String Upper() const;
  void Concat(const String& rhs);
  String Add(const String& rhs);
  [[nodiscard]] String Copy() const;
  [[nodiscard]] Unicode Get(Index index) const;
  [[nodiscard]] Index Size() const;
  void RemoveAt(Index index);
  void Clear();
  [[nodiscard]] String Slice(Index start, Index end) const;
  [[nodiscard]] bool StartsWith(const String& prefix) const;
  [[nodiscard]] bool EndsWith(const String& suffix) const;
  void Reverse();
  void Push(Unicode codePoint);
  [[nodiscard]] bool Equal(const String& rhs) const;
  [[nodiscard]] bool GreaterThan(const String& rhs) const;
  [[nodiscard]] bool LessThan(const String& rhs) const;
  [[nodiscard]] bool GreaterThanOrEqual(const String& rhs) const;
  [[nodiscard]] bool LessThanOrEqual(const String& rhs) const;
  [[nodiscard]] bool NotEqual(const String& rhs) const;
  bool operator==(const String& rhs) const;
  Unicode operator[](Index index);
  Unicode operator[](Index index) const;
};

 // namespace std
}  // namespace torchlight::Collections
#endif  // TORCHLIGHT_COLLECTIONS_STRING_H
