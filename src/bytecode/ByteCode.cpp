#include <iostream>
#include "bytecode/ByteCode.h"
namespace torchlight::bytecode {

void WriteByteCodeStoreInt(std::ofstream& stream, std::string value) {
  std::cout << "StoreInt: " << value << std::endl;
  stream.put(static_cast<char>(ByteCode::StoreInt));
  auto size = value.size();
  stream.write(reinterpret_cast<const char*>(&size), sizeof(size));
  stream.write(value.c_str(), static_cast<std::streamsize>(size));
}

void WriteByteCodeStoreDouble(std::ofstream& stream, std::string value) {
  std::cout << "StoreDouble: " << value << std::endl;
  stream.put(static_cast<char>(ByteCode::StoreDouble));
  double doubleValue = std::stod(value);
  stream.write(
    reinterpret_cast<const char*>(&doubleValue), sizeof(doubleValue)
  );
}

void WriteByteCodeOperatorAdd(std::ofstream& stream) {
  std::cout << "OperatorAdd" << std::endl;
  stream.put(static_cast<char>(ByteCode::OperatorAdd));
}

void WriteByteCodeOperatorSub(std::ofstream& stream) {
  std::cout << "OperatorSub" << std::endl;
  stream.put(static_cast<char>(ByteCode::OperatorSub));
}

void WriteByteCodeOperatorMul(std::ofstream& stream) {
  std::cout << "OperatorMul" << std::endl;
  stream.put(static_cast<char>(ByteCode::OperatorMul));
}

void WriteByteCodeOperatorDiv(std::ofstream& stream) {
  std::cout << "OperatorDiv" << std::endl;
  stream.put(static_cast<char>(ByteCode::OperatorDiv));
}

void WriteByteCodePrint(std::ofstream& stream) {
  std::cout << "Print" << std::endl;
  stream.put(static_cast<char>(ByteCode::Print));
}

}  // namespace torchlight::bytecode