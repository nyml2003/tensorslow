#ifndef TENSORSLOW_COMMON_H
#define TENSORSLOW_COMMON_H
#include <cstdint>
namespace tensorslow {
using Byte = uint8_t;      // 将无符号8位整数定义为Byte
using Unicode = uint32_t;  // 将无符号32位整数定义为Unicode
using Index = uint64_t;    // 所有索引默认为无符号64位整数
struct None {};            // None 类型是一个空结构体
const Byte Byte_0 = '0';   // Byte_0 是字符 '0'
// const Unicode Unicode_9 = 0x0039;  // Unicode_9 是字符 '9' 的 Unicode 编码
// const Unicode Unicode_A = 0x0041;  // Unicode_A 是字符 'A' 的 Unicode 编码
// const Unicode Unicode_F = 0x0046;  // Unicode_F 是字符 'F' 的 Unicode 编码
// const Unicode Unicode_a = 0x0061;  // Unicode_a 是字符 'a' 的 Unicode 编码
// const Unicode Unicode_f = 0x0066;  // Unicode_f 是字符 'f' 的 Unicode 编码
// const Unicode Unicode_X = 0x0058;  // Unicode_X 是字符 'X' 的 Unicode 编码
// const Unicode Unicode_x = 0x0078;  // Unicode_x 是字符 'x' 的 Unicode 编码
// const Unicode Unicode_Upper_Lower_Diff =
//   0x0020;  // Unicode_Upper_Lower_Diff 是大写字母和小写字母的 Unicode
//   编码差值
// const Unicode UnicodeMinus = 0x2D;  // UnicodeMinus 是字符 '-' 的 Unicode
// 编码 const Unicode UnicodePlus = 0x2B;  // UnicodePlus 是字符 '+' 的 Unicode
// 编码
const Byte Byte_9 = '9';                  // Byte_9 是字符 '9'
const Byte Byte_A = 'A';                  // Byte_A 是字符 'A'
const Byte Byte_F = 'F';                  // Byte_F 是字符 'F'
const Byte Byte_a = 'a';                  // Byte_a 是字符 'a'
const Byte Byte_f = 'f';                  // Byte_f 是字符 'f'
const Byte Byte_X = 'X';                  // Byte_X 是字符 'X'
const Byte Byte_x = 'x';                  // Byte_x 是字符 'x'
const Byte Byte_Upper_Lower_Diff = 0x20;  // 大写字母和小写字母的差值
const Byte ByteMinus = '-';               // Byte_0x2D 是字符 '-'
const Byte BytePlus = '+';                // Byte_0x2B 是字符 '+'
template <class... Ts>
struct overload : Ts... {
  using Ts::operator()...;
};
template <class... Ts>
overload(Ts...) -> overload<Ts...>;
}  // namespace tensorslow
#endif