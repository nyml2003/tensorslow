#include "collections/String.h"

#include <cstring>
#include <stdexcept>

namespace torchlight::collections {
extern template class List<Unicode>;

extern template class List<String>;

extern template class List<Index>;

Unicode String::UTF8ToUnicode(const char* str, Index& index) {
  Byte leadByte = str[index];
  int sequenceLength = 0;
  if ((leadByte & 0x80) == 0) {
    sequenceLength = 1;
  } else if ((leadByte & 0xE0) == 0xC0) {
    sequenceLength = 2;
  } else if ((leadByte & 0xF0) == 0xE0) {
    sequenceLength = 3;
  } else if ((leadByte & 0xF8) == 0xF0) {
    sequenceLength = 4;
  } else {
    throw std::runtime_error("Invalid UTF-8 sequence");
  }
  if (index + sequenceLength > strlen(str)) {
    throw std::runtime_error("Invalid UTF-8 sequence");
  }
  Unicode codePoint = 0;
  switch (sequenceLength) {
    case 1:
      codePoint = leadByte;
      break;
    case 2:
      codePoint = (leadByte & 0x1F) << 6;
      codePoint |= str[index + 1] & 0x3F;
      break;
    case 3:
      codePoint = (leadByte & 0x0F) << 12;
      codePoint |= (str[index + 1] & 0x3F) << 6;
      codePoint |= str[index + 2] & 0x3F;
      break;
    case 4:
      codePoint = (leadByte & 0x07) << 18;
      codePoint |= (str[index + 1] & 0x3F) << 12;
      codePoint |= (str[index + 2] & 0x3F) << 6;
      codePoint |= str[index + 3] & 0x3F;
      break;
    default:
      throw std::runtime_error("Invalid UTF-8 sequence");
  }
  index += sequenceLength;
  return codePoint;
}

String::String(const char* str) {
  size_t length = strlen(str);
  size_t index = 0;
  while (index < length) {
    Unicode codePoint = UTF8ToUnicode(str, index);
    Add(codePoint);
  }
}

String::String() = default;

String::String(Index capacity) {
  codePoints = List<Unicode>(capacity);
}

void String::Add(Unicode codePoint) {
  codePoints.Add(codePoint);
}

String String::Concat(const String& rhs) const {
  String str = Copy();
  for (Index i = 0; i < rhs.Size(); i++) {
    str.Add(rhs.Get(i));
  }
  return str;
}

String String::Copy() const {
  String str;
  for (Index i = 0; i < Size(); i++) {
    str.Add(Get(i));
  }
  return str;
}

Unicode String::Get(Index index) const {
  return codePoints.Get(index);
}

Index String::Size() const {
  return codePoints.Size();
}

void String::Insert(Index index, Unicode codePoint) {
  codePoints.Insert(index, codePoint);
}

void String::RemoveAt(Index index) {
  codePoints.RemoveAt(index);
}

void String::Clear() {
  codePoints.Clear();
  codePoints.TrimExcess();
}

const char* String::ToUTF8() const {
  // 假设Size()返回字符串的长度
  size_t size = Size();
  if (size == 0) {
    return "";
  }

  char* str = new char[size * 4 + 1];  // 分配足够的内存
  size_t i = 0;
  for (size_t idx = 0; idx < size; ++idx) {
    Unicode codePoint = Get(idx);
    if (codePoint < 0x80) {
      str[i++] = static_cast<char>(codePoint);
    } else if (codePoint < 0x800) {
      str[i++] = static_cast<char>(0xC0 | (codePoint >> 6));
      str[i++] = static_cast<char>(0x80 | (codePoint & 0x3F));
    } else if (codePoint < 0x10000) {
      str[i++] = static_cast<char>(0xE0 | (codePoint >> 12));
      str[i++] = static_cast<char>(0x80 | ((codePoint >> 6) & 0x3F));
      str[i++] = static_cast<char>(0x80 | (codePoint & 0x3F));
    } else if (codePoint <= 0x10FFFF) {
      str[i++] = static_cast<char>(0xF0 | (codePoint >> 18));
      str[i++] = static_cast<char>(0x80 | ((codePoint >> 12) & 0x3F));
      str[i++] = static_cast<char>(0x80 | ((codePoint >> 6) & 0x3F));
      str[i++] = static_cast<char>(0x80 | (codePoint & 0x3F));
    } else {
      delete[] str;
      return "";
    }
  }
  str[i] = '\0';  // 确保字符串以空字符结尾
  char* newStr = new char[i + 1];
  strcpy(newStr, str);
  delete[] str;
  return newStr;  // 注意：调用者需要负责释放内存
}

String String::Join(String& joiner) const {
  String str;
  for (Index i = 0; i < Size(); i++) {
    str.Add(Get(i));
    if (i < Size() - 1) {
      for (Index j = 0; j < joiner.Size(); j++) {
        str.Add(joiner.Get(j));
      }
    }
  }
  return str;
}

List<String> String::Split(String& delimiter) const {
  List<String> list;
  String str;
  for (Index i = 0; i < Size(); i++) {
    if (Get(i) == delimiter.Get(0)) {
      if (Find(delimiter, i) == i) {
        list.Add(str);
        str.Clear();
        i += delimiter.Size() - 1;
        continue;
      }
    }
    str.Add(Get(i));
  }
  list.Add(str);
  return list;
}

String String::Slice(Index start, Index end) const {
  if (start >= Size() || end > Size() || start > end) {
    throw std::runtime_error("Index out of range");
  }
  String str;
  for (Index i = start; i < end; i++) {
    str.Add(Get(i));
  }
  return str;
}

Index String::Find(String& sub, Index start) const {
  if (sub.Size() == 0) {
    return 0;
  }
  if (sub.Size() + start > Size()) {
    throw std::runtime_error("Sub string is longer than the string");
  }
  if (start >= Size()) {
    throw std::runtime_error("Start index out of range");
  }
  List<Index> next(sub.Size());
  for (Index i = 0; i < sub.Size(); i++) {
    next.Add(0);
  }
  next.Set(0, 0);
  Index j = 0;
  for (Index i = 1; i < sub.Size(); i++) {
    while (j > 0 && sub.Get(i) != sub.Get(j)) {
      j = next.Get(j - 1);
    }
    if (sub.Get(i) == sub.Get(j)) {
      j++;
    }
    next.Set(i, j);
  }
  j = 0;
  for (Index i = start; i < Size(); i++) {
    while (j > 0 && Get(i) != sub.Get(j)) {
      j = next.Get(j - 1);
    }
    if (Get(i) == sub.Get(j)) {
      j++;
    }
    if (j == sub.Size()) {
      return i - sub.Size() + 1;
    }
  }
  throw std::runtime_error("Sub string not found");
}

bool String::operator==(const String& rhs) const {
  if (Size() != rhs.Size()) {
    return false;
  }
  for (Index i = 0; i < Size(); i++) {
    if (Get(i) != rhs.Get(i)) {
      return false;
    }
  }
  return true;
}

bool String::Equal(const String& rhs) const {
  if (Size() != rhs.Size()) {
    return false;
  }
  for (Index i = 0; i < Size(); i++) {
    if (Get(i) != rhs.Get(i)) {
      return false;
    }
  }
  return true;
}

bool String::GreaterThan(const String& rhs) const {
  for (Index i = 0; i < Size(); i++) {
    if (i >= rhs.Size()) {
      return true;
    }
    if (Get(i) > rhs.Get(i)) {
      return true;
    }
    if (Get(i) < rhs.Get(i)) {
      return false;
    }
  }
  return false;
}

bool String::LessThan(const String& rhs) const {
  return !Equal(rhs) && !GreaterThan(rhs);
}

bool String::GreaterThanOrEqual(const String& rhs) const {
  return Equal(rhs) || GreaterThan(rhs);
}

bool String::LessThanOrEqual(const String& rhs) const {
  return Equal(rhs) || LessThan(rhs);
}

bool String::NotEqual(const String& rhs) const {
  return !Equal(rhs);
}

void String::Reverse() {
  codePoints.Reverse();
}

}  // namespace torchlight::collections