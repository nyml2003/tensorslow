#ifndef TORCHLIGHT_BYTECODE_H
#define TORCHLIGHT_BYTECODE_H

#include "Collections/Bytes.h"
#include "Collections/String.h"

#include <map>
#include <variant>

namespace torchlight::Object {

enum class ByteCode {
  POP_TOP = 1,
  NOP = 9,
  UNARY_POSITIVE = 10,          // 一元运算符 +
  UNARY_NEGATIVE = 11,          // 一元运算符 -
  UNARY_NOT = 12,               // 一元运算符 not
  UNARY_INVERT = 15,            // 一元运算符 ~
  BINARY_MATRIX_MULTIPLY = 16,  // 矩阵乘法 @
  BINARY_POWER = 19,            // 二元运算符 **
  BINARY_MULTIPLY = 20,         // 二元运算符 *
  BINARY_MODULO = 22,           // 二元运算符 %
  BINARY_ADD = 23,              // 二元运算符 +
  BINARY_SUBTRACT = 24,         // 二元运算符 -
  BINARY_SUBSCR = 25,           // 二元运算符 []
  BINARY_FLOOR_DIVIDE = 26,     // 二元运算符 //
  BINARY_TRUE_DIVIDE = 27,      // 二元运算符 /
  STORE_SUBSCR = 60,
  BINARY_LSHIFT = 62,
  BINARY_RSHIFT = 63,
  BINARY_AND = 64,
  BINARY_XOR = 65,
  BINARY_OR = 66,
  GET_ITER = 68,
  GET_YIELD_FROM_ITER = 69,
  LOAD_BUILD_CLASS = 71,
  RETURN_VALUE = 83,
  YIELD_VALUE = 86,
  
  STORE_NAME = 90,
  FOR_ITER = 93,
  STORE_ATTR = 95,
  STORE_GLOBAL = 97,
  LOAD_CONST = 100,
  LOAD_NAME = 101,
  BUILD_LIST = 103,
  BUILD_MAP = 105,
  LOAD_ATTR = 106,
  COMPARE_OP = 107,
  JUMP_FORWARD = 110,
  JUMP_IF_FALSE_OR_POP = 111,
  JUMP_IF_TRUE_OR_POP = 112,
  JUMP_ABSOLUTE = 113,
  POP_JUMP_IF_FALSE = 114,
  POP_JUMP_IF_TRUE = 115,
  LOAD_GLOBAL = 116,
  LOAD_FAST = 124,
  STORE_FAST = 125,
  MAKE_FUNCTION = 132,
  BUILD_SLICE = 133,
  CALL_FUNCTION = 142,

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

static const std::map<ByteCode, const char*> ByteCodeNames = {
  {ByteCode::POP_TOP, "POP_TOP"},
  {ByteCode::NOP, "NOP"},
  {ByteCode::UNARY_POSITIVE, "UNARY_POSITIVE"},
  {ByteCode::UNARY_NEGATIVE, "UNARY_NEGATIVE"},
  {ByteCode::UNARY_NOT, "UNARY_NOT"},
  {ByteCode::UNARY_INVERT, "UNARY_INVERT"},
  {ByteCode::BINARY_MATRIX_MULTIPLY, "BINARY_MATRIX_MULTIPLY"},
  {ByteCode::BINARY_POWER, "BINARY_POWER"},
  {ByteCode::BINARY_MULTIPLY, "BINARY_MULTIPLY"},
  {ByteCode::BINARY_MODULO, "BINARY_MODULO"},
  {ByteCode::BINARY_ADD, "BINARY_ADD"},
  {ByteCode::BINARY_SUBTRACT, "BINARY_SUBTRACT"},
  {ByteCode::BINARY_SUBSCR, "BINARY_SUBSCR"},
  {ByteCode::BINARY_FLOOR_DIVIDE, "BINARY_FLOOR_DIVIDE"},
  {ByteCode::BINARY_TRUE_DIVIDE, "BINARY_TRUE_DIVIDE"},
  {ByteCode::STORE_SUBSCR, "STORE_SUBSCR"},
  {ByteCode::BINARY_LSHIFT, "BINARY_LSHIFT"},
  {ByteCode::BINARY_RSHIFT, "BINARY_RSHIFT"},
  {ByteCode::BINARY_AND, "BINARY_AND"},
  {ByteCode::BINARY_XOR, "BINARY_XOR"},
  {ByteCode::BINARY_OR, "BINARY_OR"},
  {ByteCode::GET_ITER, "GET_ITER"},
  {ByteCode::LOAD_BUILD_CLASS, "LOAD_BUILD_CLASS"},
  {ByteCode::RETURN_VALUE, "RETURN_VALUE"},
  {ByteCode::STORE_NAME, "STORE_NAME"},
  {ByteCode::FOR_ITER, "FOR_ITER"},
  {ByteCode::STORE_ATTR, "STORE_ATTR"},
  {ByteCode::STORE_GLOBAL, "STORE_GLOBAL"},
  {ByteCode::LOAD_CONST, "LOAD_CONST"},
  {ByteCode::LOAD_NAME, "LOAD_NAME"},
  {ByteCode::BUILD_LIST, "BUILD_LIST"},
  {ByteCode::BUILD_MAP, "BUILD_MAP"},
  {ByteCode::LOAD_ATTR, "LOAD_ATTR"},
  {ByteCode::COMPARE_OP, "COMPARE_OP"},
  {ByteCode::JUMP_FORWARD, "JUMP_FORWARD"},
  {ByteCode::JUMP_IF_FALSE_OR_POP, "JUMP_IF_FALSE_OR_POP"},
  {ByteCode::JUMP_IF_TRUE_OR_POP, "JUMP_IF_TRUE_OR_POP"},
  {ByteCode::JUMP_ABSOLUTE, "JUMP_ABSOLUTE"},
  {ByteCode::POP_JUMP_IF_FALSE, "POP_JUMP_IF_FALSE"},
  {ByteCode::POP_JUMP_IF_TRUE, "POP_JUMP_IF_TRUE"},
  {ByteCode::LOAD_GLOBAL, "LOAD_GLOBAL"},
  {ByteCode::LOAD_FAST, "LOAD_FAST"},
  {ByteCode::STORE_FAST, "STORE_FAST"},
  {ByteCode::MAKE_FUNCTION, "MAKE_FUNCTION"},
  {ByteCode::BUILD_SLICE, "BUILD_SLICE"},
  {ByteCode::CALL_FUNCTION, "CALL_FUNCTION"},
  {ByteCode::GET_YIELD_FROM_ITER, "GET_YIELD_FROM_ITER"},
  {ByteCode::YIELD_VALUE, "YIELD_VALUE"},
  {ByteCode::ERROR, "ERROR"},
};

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