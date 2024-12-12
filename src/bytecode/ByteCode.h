#ifndef TORCHLIGHT_BYTECODE_H
#define TORCHLIGHT_BYTECODE_H

#include <sstream>
#include <vector>
namespace torchlight::bytecode {
enum class ByteCode {
  StoreInt = 0x80,
  StoreDouble,
  OperatorAdd,
  OperatorSub,
  OperatorMul,
  OperatorDiv,
  Print,
};

void WriteByteCodeStoreInt(std::vector<std::string>& stream, std::string value);

void WriteByteCodeStoreDouble(
  std::vector<std::string>& stream,
  std::string value
);

void WriteByteCodeOperatorAdd(std::vector<std::string>& stream);

void WriteByteCodeOperatorSub(std::vector<std::string>& stream);

void WriteByteCodeOperatorMul(std::vector<std::string>& stream);

void WriteByteCodeOperatorDiv(std::vector<std::string>& stream);

void WriteByteCodePrint(std::vector<std::string>& stream);

}  // namespace torchlight::bytecode

#endif  // TORCHLIGHT_BYTECODE_H