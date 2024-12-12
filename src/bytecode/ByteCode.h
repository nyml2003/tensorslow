#ifndef TORCHLIGHT_BYTECODE_H
#define TORCHLIGHT_BYTECODE_H

#include <fstream>
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

void WriteByteCodeStoreInt(std::ofstream& stream, std::string value);

void WriteByteCodeStoreDouble(std::ofstream& stream, std::string value);

void WriteByteCodeOperatorAdd(std::ofstream& stream);

void WriteByteCodeOperatorSub(std::ofstream& stream);

void WriteByteCodeOperatorMul(std::ofstream& stream);

void WriteByteCodeOperatorDiv(std::ofstream& stream);

void WriteByteCodePrint(std::ofstream& stream);

}  // namespace torchlight::bytecode

#endif  // TORCHLIGHT_BYTECODE_H