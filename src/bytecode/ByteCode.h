#ifndef TORCHLIGHT_BYTECODE_H
#define TORCHLIGHT_BYTECODE_H

#include "bytecode/Operand.h"
#include "collections/Bytes.h"
#include "collections/List.h"

#include <functional>
#include <memory>
#include <utility>

namespace torchlight::bytecode {
using collections::Bytes;
using std::function;
using std::make_shared;
using std::shared_ptr;

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

  PRINT = 0xFE,  // 临时字节码
  ERROR = 0xFF
};

struct ByteCodeInstruction {
  ByteCode code = ByteCode::ERROR;
  OperandKind operand = NoneType();
  function<Bytes()> ToString;

  ByteCodeInstruction(
    ByteCode c,
    OperandKind op,
    std::function<Bytes()> toStringFunc
  )
    : code(c), operand(std::move(op)), ToString(std::move(toStringFunc)) {}
};

using InstPtr = shared_ptr<ByteCodeInstruction>;

using InstStream = collections::List<InstPtr>;

InstPtr CreateLoadConst(Bytes value);

InstPtr CreateCompareOp(CompareOp op);

InstPtr CreatePopJumpIfFalse(uint32_t offset);

InstPtr CreateBinaryAdd();

InstPtr CreateBinarySubtract();

InstPtr CreateBinaryMultiply();

InstPtr CreateBinaryTrueDivide();

InstPtr CreateBinaryFloorDivide();

InstPtr CreateBinaryXor();

InstPtr CreateBinaryAnd();

InstPtr CreateBinaryOr();

InstPtr CreateBinaryPower();

InstPtr CreateBinaryModulo();

InstPtr CreateBinaryLShift();

InstPtr CreateBinaryRShift();

InstPtr CreatePrint();

}  // namespace torchlight::bytecode

#endif  // TORCHLIGHT_BYTECODE_H