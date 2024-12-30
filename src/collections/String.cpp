#include "collections/String.h"
#include "collections/impl/Bytes.h"
#include "collections/impl/String.h"

#include <cstring>
#include <stdexcept>
#include <iostream>

namespace torchlight::collections {
extern template class List<Unicode>;

extern template class List<String>;

extern template class List<Index>;

Unicode GetUnicode(
  Index& index,
  const std::function<Byte(Index)>& GetByte,
  const std::function<bool(Index)>& IsValid
) {
  Byte leadByte = GetByte(index);
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
  if (!IsValid(index + sequenceLength - 1)) {
    throw std::runtime_error("Invalid UTF-8 sequence");
  }
  Unicode codePoint = 0;
  switch (sequenceLength) {
    case 1:
      codePoint = leadByte;
      break;
    case 2:
      codePoint = (leadByte & 0x1F) << 6;
      codePoint |= GetByte(index + 1) & 0x3F;
      break;
    case 3:
      codePoint = (leadByte & 0x0F) << 12;
      codePoint |= (GetByte(index + 1) & 0x3F) << 6;
      codePoint |= GetByte(index + 2) & 0x3F;
      break;
    case 4:
      codePoint = (leadByte & 0x07) << 18;
      codePoint |= (GetByte(index + 1) & 0x3F) << 12;
      codePoint |= (GetByte(index + 2) & 0x3F) << 6;
      codePoint |= GetByte(index + 3) & 0x3F;
      break;
    default:
      throw std::runtime_error("Invalid UTF-8 sequence");
  }
  index += sequenceLength;
  return codePoint;
}

String CreateEmptyString() {
  List<Unicode> codePoints;
  return String(codePoints);
}

String CreateStringWithCString(const char* str) {
  List<Unicode> codePoints;
  size_t length = strlen(str);
  size_t index = 0;
  while (index < length) {
    Unicode codePoint = GetUnicode(
      index,
      [str](Index index) -> Byte { return static_cast<Byte>(str[index]); },
      [length](Index index) -> bool { return index < length; }
    );
    codePoints.Add(codePoint);
  }
  return String(codePoints);
}

String CreateStringWithBytes(const Bytes& bytes) {
  std::cout << ToCString(bytes).get() << std::endl;
  List<Unicode> codePoints;
  size_t length = bytes.Size();
  size_t index = 0;
  while (index < length) {
    Unicode codePoint = GetUnicode(
      index, [bytes](Index index) -> Byte { return bytes.Get(index); },
      [length](Index index) -> bool { return index < length; }
    );
    codePoints.Add(codePoint);
  }
  return String(codePoints);
}

String::String(const List<Unicode>& codePoints) : codePoints(codePoints) {}

String String::Concat(const String& rhs) const {
  return Copy().InplaceConcat(rhs);
}

List<Unicode> String::Data() const {
  return codePoints;
}

String String::Copy() const {
  return String(codePoints.Copy());
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

std::unique_ptr<char[]> ToCString(const String& str) {
  return ToCString(ToBytes(str));
}

String String::Join(String& joiner) const {
  List<Unicode> str;
  for (Index i = 0; i < Size(); i++) {
    str.Add(Get(i));
    if (i < Size() - 1) {
      str.Add(joiner.Data());
    }
  }
  return String(str);
}

List<String> String::Split(String& delimiter) const {
  List<String> list;
  List<Unicode> str;
  for (Index i = 0; i < Size(); i++) {
    if (Get(i) == delimiter.Get(0)) {
      if (Find(delimiter, i) == i) {
        list.Add(String(str));
        str.Clear();
        i += delimiter.Size() - 1;
        continue;
      }
    }
    str.Add(Get(i));
  }
  list.Add(String(str));
  return list;
}

String String::Slice(Index start, Index end) const {
  if (start >= Size() || end > Size() || start > end) {
    throw std::runtime_error("Index out of range");
  }
  return String(codePoints.Slice(start, end));
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
  next.Fill(0);
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

String ToString(double value) {
  char buffer[32];
  snprintf(buffer, sizeof(buffer), "%.6f", value);
  return CreateStringWithCString(buffer);
}

String ToString(int32_t value) {
  char buffer[32];
  snprintf(buffer, sizeof(buffer), "%d", value);
  return CreateStringWithCString(buffer);
}

String ToString(uint64_t value) {
  char buffer[32];
  snprintf(buffer, sizeof(buffer), "%lu", value);
  return CreateStringWithCString(buffer);
}

String ToString(uint32_t value) {
  char buffer[32];
  snprintf(buffer, sizeof(buffer), "%u", value);
  return CreateStringWithCString(buffer);
}
String String::InplaceConcat(const String& rhs) {
  codePoints.Add(rhs.codePoints);
  return *this;
}

bool String::operator==(const String& rhs) const {
  return Equal(rhs);
}
}  // namespace torchlight::collections