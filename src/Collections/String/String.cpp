#include "Collections/String/String.h"
#include <stdexcept>
#include "StringHelper.h"

namespace torchlight::Collections {

Unicode String::Get(Index index) const {
  return codePoints.Get(index);
}
Index String::Size() const {
  return codePoints.Size();
}
// List<String> String::Split(String& delimiter) const {
//   List<Unicode> str;
//   List<String> list;
//   for (Index i = 0; i < Size(); i++) {
//     if (Get(i) == delimiter.Get(0)) {
//       if (Find(delimiter, i) == i) {
//         list.Push(std::move(String(std::move(str))));
//         str.Clear();
//         i += delimiter.Size() - 1;
//         continue;
//       }
//     }
//     str.Push(Get(i));
//   }
//   list.Push(String(str));
//   return list;
// }
String String::Slice(Index start, Index end) const {
  return String(codePoints.Slice(start, end));
}
bool String::StartsWith(const String& prefix) const {
  if (prefix.Size() > Size()) {
    return false;
  }
  for (Index i = 0; i < prefix.Size(); i++) {
    if (Get(i) != prefix.Get(i)) {
      return false;
    }
  }
  return true;
}
bool String::EndsWith(const String& suffix) const {
  if (suffix.Size() > Size()) {
    return false;
  }
  for (Index i = 0; i < suffix.Size(); i++) {
    if (Get(Size() - suffix.Size() + i) != suffix.Get(i)) {
      return false;
    }
  }
  return true;
}
// Index String::Find(String& sub, Index start) const {
//   if (sub.Size() == 0) {
//     return 0;
//   }
//   if (start >= Size()) {
//     throw std::runtime_error("Start index out of range");
//   }
//   if (sub.Size() + start > Size()) {
//     throw std::runtime_error("Sub string is longer than the string");
//   }
//   List<Index> next(sub.Size());
//   next.Fill(0);
//   Index j = 0;
//   for (Index i = 1; i < sub.Size(); i++) {
//     while (j > 0 && sub.Get(i) != sub.Get(j)) {
//       j = next.Get(j - 1);
//     }
//     if (sub.Get(i) == sub.Get(j)) {
//       j++;
//     }
//     next.Set(i, j);
//   }
//   j = 0;
//   for (Index i = start; i < Size(); i++) {
//     while (j > 0 && Get(i) != sub.Get(j)) {
//       j = next.Get(j - 1);
//     }
//     if (Get(i) == sub.Get(j)) {
//       j++;
//     }
//     if (j == sub.Size()) {
//       return i - sub.Size() + 1;
//     }
//   }
//   throw std::runtime_error("Sub string not found");
// }
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
String String::Add(const String& rhs) {
  return String(codePoints.Add(rhs.codePoints));
}
bool String::operator==(const String& rhs) const {
  return Equal(rhs);
}
Unicode String::operator[](Index index) const {
  return codePoints[index];
}

String String::Upper() const {
  StringBuilder sb;
  for (Index i = 0; i < Size(); i++) {
    if (Get(i) >= 'a' && Get(i) <= 'z') {
      sb.Append(Get(i) - Unicode_Upper_Lower_Diff);
    } else {
      sb.Append(Get(i));
    }
  }
  return sb.ToString();
}

size_t String::Hash() {
  if (hashed) {
    return hashValue;
  }
  hashValue = std::hash<std::string>{}(ToCppString(*this));
  this->hashed = true;
  return hashValue;
}

void String::SetHash(size_t hash) {
  this->hashValue = hash;
  this->hashed = true;
}

}  // namespace torchlight::Collections