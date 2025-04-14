#ifndef TORCHLIGHT_COLLECTIONS_STRING_H
#define TORCHLIGHT_COLLECTIONS_STRING_H

#include <mutex>
#include "Collections/List.h"
namespace torchlight::Collections {
class StringPool;
class String {
  friend class StringBuilder;

 private:
  List<Unicode> codePoints;
  bool hashed = false;
  size_t hashValue = 0;

 public:
  explicit String(List<Unicode>&& codePoints)
    : codePoints(std::move(codePoints)) {}
  explicit String(List<Unicode>&& codePoints, size_t hashValue)
    : codePoints(std::move(codePoints)), hashValue(hashValue), hashed(true) {}
  String(const String& other) = default;
  String(String& other) = default;
  String(String&& other) noexcept = default;
  String& operator=(const String& other) = default;
  String& operator=(String&& other) noexcept = default;
  ~String() = default;
  //  /**
  //   * 用于将字符串分割成多个子串
  //   * @param delimiter 分隔符
  //   * @return
  //   */
  //  [[nodiscard]] List<String> Split(String& delimiter) const;
  //  /**
  //   * 找到start开始的第一个String的位置
  //   * @param sub
  //   * @return
  //   */
  //  [[nodiscard]] Index Find(String& sub, Index start = 0) const;
  [[nodiscard]] String Upper() const;
  String Add(const String& rhs);
  // [[nodiscard]] String Copy() const;
  size_t Hash();
  void SetHash(size_t hashValue);
  [[nodiscard]] Unicode Get(Index index) const;
  [[nodiscard]] Index Size() const;
  [[nodiscard]] String Slice(Index start, Index end) const;
  [[nodiscard]] bool StartsWith(const String& prefix) const;
  [[nodiscard]] bool EndsWith(const String& suffix) const;
  [[nodiscard]] bool Equal(const String& rhs) const;
  [[nodiscard]] bool GreaterThan(const String& rhs) const;
  [[nodiscard]] bool LessThan(const String& rhs) const;
  [[nodiscard]] bool GreaterThanOrEqual(const String& rhs) const;
  [[nodiscard]] bool LessThanOrEqual(const String& rhs) const;
  [[nodiscard]] bool NotEqual(const String& rhs) const;
  bool operator==(const String& rhs) const;
  Unicode operator[](Index index) const;
};

class StringBuilder {
 private:
  List<Unicode> codePoints;

 public:
  explicit StringBuilder() = default;
  explicit StringBuilder(const String& str) : codePoints(str.codePoints) {}
  void Append(const String& str) { codePoints.Concat(str.codePoints); }
  void Append(const Unicode& codePoint) { codePoints.Push(codePoint); }
  [[nodiscard]] String ToString() { return String(std::move(codePoints)); }
  [[nodiscard]] Index Size() const { return codePoints.Size(); }
  void Clear() { codePoints.Clear(); }
};

}  // namespace torchlight::Collections
#endif  // TORCHLIGHT_COLLECTIONS_STRING_H
