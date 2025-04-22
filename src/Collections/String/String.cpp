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