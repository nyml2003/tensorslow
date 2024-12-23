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
  LOAD_CONST = 0x80,
  COMPARE_OP,
  POP_JUMP_IF_FALSE,
  BINARY_ADD,
  BINARY_SUBTRACT,
  BINARY_MULTIPLY,
  BINARY_TRUE_DIVIDE,
  BINARY_FLOOR_DIVIDE,
  BINARY_XOR,
  BINARY_AND,
  BINARY_OR,
  BINARY_POWER,
  BINARY_MODULO,
  BINARY_LSHIFT,
  BINARY_RSHIFT,
  PRINT,  // 临时字节码
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