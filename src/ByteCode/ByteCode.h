#ifndef TORCHLIGHT_BYTECODE_H
#define TORCHLIGHT_BYTECODE_H

#include "Collections/Bytes.h"
#include "Collections/String.h"

#include <map>
#include <variant>

namespace torchlight::Object {

enum class ByteCode {
  POP_TOP = 0,
  NOP = 9,
  UNARY_POSITIVE = 10,  // 一元运算符 +
  UNARY_NEGATIVE = 11,  // 一元运算符 -
  UNARY_NOT = 12,       // 一元运算符 not

  UNARY_INVERT = 15,             // 一元运算符 ~
  BINARY_MATRIX_MULTIPLY = 16,   // 矩阵乘法 @
  INPLACE_MATRIX_MULTIPLY = 17,  // 矩阵乘法 @=

  BINARY_POWER = 19,     // 二元运算符 **
  BINARY_MULTIPLY = 20,  // 二元运算符 *

  BINARY_MODULO = 22,        // 二元运算符 %
  BINARY_ADD = 23,           // 二元运算符 +
  BINARY_SUBTRACT = 24,      // 二元运算符 -
  BINARY_SUBSCR = 25,        // 二元运算符 []
  BINARY_FLOOR_DIVIDE = 26,  // 二元运算符 //
  BINARY_TRUE_DIVIDE = 27,   // 二元运算符 /
  INPLACE_FLOOR_DIVIDE = 28, /* //= */
  INPLACE_TRUE_DIVIDE = 29,  /* /= */
  GET_LEN = 30,
  INPLACE_ADD = 55,       // +=
  INPLACE_SUBTRACT = 56,  // -=
  INPLACE_MULTIPLY = 57,  /* *= */
  INPLACE_MODULO = 59,    // %=
  STORE_SUBSCR = 60,
  DELETE_SUBSCR = 61,
  BINARY_LSHIFT = 62,
  BINARY_RSHIFT = 63,
  BINARY_AND = 64,
  BINARY_XOR = 65,
  BINARY_OR = 66,
  INPLACE_POWER = 67,
  GET_ITER = 68,

  INPLACE_LSHIFT = 75,
  INPLACE_RSHIFT = 76,
  INPLACE_AND = 77,
  INPLACE_XOR = 78,
  INPLACE_OR = 79,

  RETURN_VALUE = 83,
  STORE_NAME = 90,
  DELETE_NAME = 91,
  UNPACK_SEQUENCE = 92,
  FOR_ITER = 93,
  STORE_ATTR = 95,
  DELETE_ATTR = 96,
  STORE_GLOBAL = 97,
  DELETE_GLOBAL = 98,

  LOAD_CONST = 100,
  LOAD_NAME = 101,
  BUILD_TUPLE = 102,
  BUILD_LIST = 103,
  BUILD_SET = 104,
  BUILD_MAP = 105,
  LOAD_ATTR = 106,

  COMPARE_OP = 107,
  IMPORT_NAME = 108,
  IMPORT_FROM = 109,
  JUMP_FORWARD = 110,
  JUMP_IF_FALSE_OR_POP = 111,
  JUMP_IF_TRUE_OR_POP = 112,
  JUMP_ABSOLUTE = 113,
  POP_JUMP_IF_FALSE = 114,
  POP_JUMP_IF_TRUE = 115,
  LOAD_GLOBAL = 116,

  BINARY_OP = 122,
  LOAD_FAST = 124,
  STORE_FAST = 125,
  DELETE_FAST = 126,

  MAKE_FUNCTION = 132,
  BUILD_SLICE = 133,
  LOAD_CLOSURE = 135,

  CALL_FUNCTION = 142,
  LOAD_METHOD = 160,
  CALL_METHOD = 161,

  ERROR = 0xFF
};

enum class CompareOp {
  EQUAL = 2,
  NOT_EQUAL = 3,
  LESS_THAN = 0,
  LESS_THAN_EQUAL = 1,
  GREATER_THAN = 4,
  GREATER_THAN_EQUAL = 5,
  IS = 8,
  IS_NOT = 9,
  IN = 6,
  NOT_IN = 7,
};

using OperandKind = std::variant<CompareOp, None, Index, int64_t>;

enum class Literal {
  INTEGER,
  ZERO,
  FLOAT,
  STRING,
  NONE,
  TRUE,
  FALSE,
  LIST,
  CODE,
  BYTES,
};

extern std::map<ByteCode, const char*> ByteCodeNames;

}  // namespace torchlight::Object
namespace torchlight::Collections {
String ToString(None kind);
String ToString(Object::CompareOp kind);
String ToString(Object::ByteCode code);
String ToString(Object::Literal kind);
Bytes Serialize(None kind);
Bytes Serialize(Object::CompareOp kind);
Bytes Serialize(Object::ByteCode code);
Bytes Serialize(Object::Literal kind);
}  // namespace torchlight::Collections
#endif  // TORCHLIGHT_BYTECODE_H