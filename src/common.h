#ifndef TORCHLIGHT_COMMON_H
#define TORCHLIGHT_COMMON_H
#include <cstdint>
namespace torchlight {
using Byte = uint8_t;              // 将无符号8位整数定义为Byte
using Unicode = uint32_t;          // 将无符号32位整数定义为Unicode
using Index = uint64_t;            // 所有索引默认为无符号64位整数
struct None {};                    // None 类型是一个空结构体
const Unicode Unicode_0 = 0x0030;  // Unicode_0 是字符 '0' 的 Unicode 编码
const Unicode Unicode_9 = 0x0039;  // Unicode_9 是字符 '9' 的 Unicode 编码
const Unicode Unicode_A = 0x0041;  // Unicode_A 是字符 'A' 的 Unicode 编码
const Unicode Unicode_F = 0x0046;  // Unicode_F 是字符 'F' 的 Unicode 编码
const Unicode Unicode_a = 0x0061;  // Unicode_a 是字符 'a' 的 Unicode 编码
const Unicode Unicode_f = 0x0066;  // Unicode_f 是字符 'f' 的 Unicode 编码
const Unicode Unicode_X = 0x0058;  // Unicode_X 是字符 'X' 的 Unicode 编码
const Unicode Unicode_x = 0x0078;  // Unicode_x 是字符 'x' 的 Unicode 编码
const Unicode Unicode_Upper_Lower_Diff =
  0x0020;  // Unicode_Upper_Lower_Diff 是大写字母和小写字母的 Unicode 编码差值
const Unicode UnicodeMinus = 0x2D;  // UnicodeMinus 是字符 '-' 的 Unicode 编码
const Unicode UnicodePlus = 0x2B;  // UnicodePlus 是字符 '+' 的 Unicode 编码
template <class... Ts>
struct overload : Ts... {
  using Ts::operator()...;
};
template <class... Ts>
overload(Ts...) -> overload<Ts...>;
}  // namespace torchlight
#endif