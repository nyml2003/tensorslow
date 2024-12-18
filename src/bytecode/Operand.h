#ifndef TORCHLIGHT_BYTECODE_OPERAND_H
#define TORCHLIGHT_BYTECODE_OPERAND_H

#include <string>
#include <variant>
namespace torchlight::bytecode {

using std::string;
using std::variant;

enum class CompareOp {
  EQUAL = 2,
  NOT_EQUAL = 3,
  LESS_THAN = 0,
  LESS_THAN_EQUAL = 1,
  GREATER_THAN = 4,
  GREATER_THAN_EQUAL = 5,
};

struct NoneType {};

using OperandKind = variant<CompareOp, string, uint32_t, NoneType>;
}  // namespace torchlight::bytecode
#endif  // TORCHLIGHT_BYTECODE_OPERAND_H