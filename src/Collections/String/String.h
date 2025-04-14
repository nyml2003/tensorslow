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
  static StringPool stringPool;

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
   * @param delimiter 分隔符
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
  String Add(const String& rhs);
  [[nodiscard]] String Copy() const;
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
  [[nodiscard]] size_t Hash() const;
};

class StringBuilder {
 private:
  List<Unicode> codePoints;

 public:
  explicit StringBuilder() = default;
  explicit StringBuilder(const String& str) : codePoints(str.codePoints) {}
  void Append(const String& str) { codePoints.Concat(str.codePoints); }
  void Append(const Unicode& codePoint) { codePoints.Push(codePoint); }
  [[nodiscard]] String ToString() const { return String(codePoints); }
  [[nodiscard]] Index Size() const { return codePoints.Size(); }
  void Clear() { codePoints.Clear(); }
};

class StringPool {
 private:
  std::unordered_map<size_t, std::unique_ptr<String>> pool;
  std::mutex poolMutex;

 public:
  // 禁止拷贝和赋值
  StringPool(const StringPool&) = delete;
  StringPool& operator=(const StringPool&) = delete;

  // 构造函数和析构函数
  StringPool() = default;
  ~StringPool() = default;  // unique_ptr 会自动释放资源，无需手动清理

  // 获取或创建字符串实例
  const String* Intern(const List<Unicode>& codePoints);
  bool Contains(const List<Unicode>& codePoints) const;
};

}  // namespace torchlight::Collections
#endif  // TORCHLIGHT_COLLECTIONS_STRING_H
