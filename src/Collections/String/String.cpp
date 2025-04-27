#include "Collections/String/String.h"
#include <iostream>
#include <stdexcept>
#include "StringHelper.h"

namespace torchlight::Collections {

String String::Slice(Index start, Index end) {
  if (!~start || !~end || start >= end) {
    throw std::invalid_argument("String::Slice(): invalid index");
  }
  ParseCodePointAt(end);
  if (start > codePoints.Size() || end > codePoints.Size()) {
    throw std::out_of_range("String::Slice(): index out of range");
  }
  auto codeUnitStart = codePointIndices[start];
  auto codeUnitEnd = codePointIndices[end];
  return String(codeUnits.Slice(codeUnitStart, codeUnitEnd));
}

void String::ParseCodePoint() const noexcept {
  Byte leadByte = codeUnits.Get(unparsedCodeUnitOffset);
  uint8_t sequenceLength = utf8_sequence_length[leadByte];
  Unicode codePoint = 0;
  switch (sequenceLength) {
    case 1:
      codePoint = leadByte;
      break;
    case 2: {
      Byte byte1 = codeUnits.Get(unparsedCodeUnitOffset + 1);
      codePoint = (leadByte & 0x1F) << 6 | (byte1 & 0x3F);
      break;
    }
    case 3: {
      Byte byte1 = codeUnits.Get(unparsedCodeUnitOffset + 1);
      Byte byte2 = codeUnits.Get(unparsedCodeUnitOffset + 2);
      codePoint =
        (leadByte & 0x0F) << 12 | (byte1 & 0x3F) << 6 | (byte2 & 0x3F);
      break;
    }
    case 4: {
      Byte byte1 = codeUnits.Get(unparsedCodeUnitOffset + 1);
      Byte byte2 = codeUnits.Get(unparsedCodeUnitOffset + 2);
      Byte byte3 = codeUnits.Get(unparsedCodeUnitOffset + 3);
      codePoint = (leadByte & 0x07) << 18 | (byte1 & 0x3F) << 12 |
                  (byte2 & 0x3F) << 6 | (byte3 & 0x3F);
      break;
    }
    default:
      // 处理无效的序列（如返回0或错误值）
      break;
  }
  codePoints.Push(codePoint);
  codePointIndices.Push(unparsedCodeUnitOffset);
  unparsedCodeUnitOffset += sequenceLength;
}

void String::ParseCodePointAt(Index index) {
  while (codePoints.Size() <= index && !HasParsedAllCodePoints()) {
    ParseCodePoint();
  }
  if (HasParsedAllCodePoints() && codePoints.Size() <= index) {
    throw std::out_of_range("String::ParseCodePointAt(): index out of range");
  }
}

void String::ParseCodePoints() const noexcept {
  while (!HasParsedAllCodePoints()) {
    ParseCodePoint();
  }
}

bool String::StartsWith(const String& prefix) const {
  if (prefix.codeUnits.Size() > codeUnits.Size()) {
    return false;
  }
  for (Index i = 0; i < prefix.codeUnits.Size(); i++) {
    if (codeUnits.Get(i) != prefix.codeUnits.Get(i)) {
      return false;
    }
  }
  return true;
}
bool String::EndsWith(const String& suffix) const {
  if (suffix.codeUnits.Size() > codeUnits.Size()) {
    return false;
  }
  for (Index i = 0; i < suffix.codeUnits.Size(); i++) {
    if (codeUnits.Get(codeUnits.Size() - suffix.codeUnits.Size() + i) !=
                suffix.codeUnits.Get(i)) {
      return false;
    }
  }
  return true;
}
bool String::Equal(const String& rhs) noexcept {
  auto lhash = HashValue();
  auto rhash = rhs.HashValue();
  if (lhash != rhash) {
    return false;
  }
  if (codeUnits.Size() != rhs.codeUnits.Size()) {
    return false;
  }
  auto thisCodePointSize = this->GetCodePointCount();
  auto otherCodePointSize = rhs.GetCodePointCount();
  if (thisCodePointSize != otherCodePointSize) {
    return false;
  }
  for (Index i = 0; i < thisCodePointSize; i++) {
    if (codePoints.Get(i) != rhs.codePoints.Get(i)) {
      return false;
    }
  }
  return true;
}
bool String::GreaterThan(const String& rhs) noexcept {
  auto thisCodePointSize = this->GetCodePointCount();
  auto otherCodePointSize = rhs.GetCodePointCount();
  Index minSize = std::min(thisCodePointSize, otherCodePointSize);
  for (Index i = 0; i < minSize; i++) {
    auto thisCodePoint = codePoints.Get(i);
    auto otherCodePoint = rhs.codePoints.Get(i);

    if (thisCodePoint > otherCodePoint) {
      return true;  // 当前字符大于对方字符，返回 true
    } else if (thisCodePoint < otherCodePoint) {
      return false;  // 当前字符小于对方字符，返回 false
    }
  }

  // 如果前缀相等，比较长度
  return thisCodePointSize > otherCodePointSize;
}

std::string String::ToCppString() const {
  return std::string(
    reinterpret_cast<const char*>(codeUnits.Data()), codeUnits.Size()
  );
}

std::size_t String::HashValue() const {
  if (hashed) {
    return hashValue;
  }
  hashValue = Hash(codeUnits);
  hashed = true;
  return hashValue;
}

String String::Upper() {
  StringBuilder sb;
  ParseCodePoints();
  for (Index i = 0; i < codePoints.Size(); i++) {
    Unicode codePoint = codePoints.Get(i);
    if (codePoint >= 'a' && codePoint <= 'z') {
      codePoint -= ('a' - 'A');
    }
    sb.Append(codePoint);
  }
  return sb.ToString();
}

}  // namespace torchlight::Collections