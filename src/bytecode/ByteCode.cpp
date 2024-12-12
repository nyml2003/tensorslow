#include <array>
#include <cstring>
#include <iostream>
#include "bytecode/ByteCode.h"
namespace torchlight::bytecode {

void WriteByteCodeStoreInt(
  std::vector<std::string>& stream,
  std::string value
) {
  std::cout << "StoreInt: " << value << std::endl;
  std::string s;
  s.push_back(static_cast<char>(ByteCode::StoreInt));
  size_t size = value.size();
  s.append(reinterpret_cast<const char*>(&size), sizeof(size));
  s.append(value);
  stream.push_back(s);
}
void WriteByteCodeStoreDouble(
  std::vector<std::string>& stream,
  std::string value
) {}

void WriteByteCodeOperatorAdd(std::vector<std::string>& stream) {
  std::cout << "OperatorAdd" << std::endl;
  std::string s;
  s.push_back(static_cast<char>(ByteCode::OperatorAdd));
  stream.push_back(s);
}

void WriteByteCodeOperatorSub(std::vector<std::string>& stream) {
  std::cout << "OperatorSub" << std::endl;
  std::string s;
  s.push_back(static_cast<char>(ByteCode::OperatorSub));
  stream.push_back(s);
}

void WriteByteCodeOperatorMul(std::vector<std::string>& stream) {
  std::cout << "OperatorMul" << std::endl;
  std::string s;
  s.push_back(static_cast<char>(ByteCode::OperatorMul));
  stream.push_back(s);
}

void WriteByteCodeOperatorDiv(std::vector<std::string>& stream) {
  std::cout << "OperatorDiv" << std::endl;
  std::string s;
  s.push_back(static_cast<char>(ByteCode::OperatorDiv));
  stream.push_back(s);
}

void WriteByteCodePrint(std::vector<std::string>& stream) {
  std::cout << "Print" << std::endl;
  std::string s;
  s.push_back(static_cast<char>(ByteCode::Print));
  stream.push_back(s);
}

}  // namespace torchlight::bytecode