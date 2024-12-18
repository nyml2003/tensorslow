

#include "bytecode/ByteCode.h"

#include <string>
#include "bytecode/utils.h"

namespace torchlight::bytecode {
using std::to_string;

InstPtr CreateLoadConst(string value) {
  return make_unique<ByteCodeInstruction>(
    ByteCode::LOAD_CONST, value,
    [value]() -> string {
      return to_string(SerializeByteCode(ByteCode::LOAD_CONST)) + value;
    }
  );
}

InstPtr CreateCompareOp(CompareOp op) {
  return make_unique<ByteCodeInstruction>(
    ByteCode::COMPARE_OP, op,
    [op]() -> string {
      return to_string(SerializeByteCode(ByteCode::COMPARE_OP)) +
             to_string(static_cast<uint8_t>(op));
    }
  );
}

InstPtr CreatePopJumpIfFalse(uint32_t offset) {
  return make_unique<ByteCodeInstruction>(
    ByteCode::POP_JUMP_IF_FALSE, offset,
    [offset]() -> string {
      const char* offset_str = reinterpret_cast<const char*>(&offset);
      string offset_str_str(offset_str, sizeof(uint32_t));
      return to_string(SerializeByteCode(ByteCode::POP_JUMP_IF_FALSE)) +
             offset_str_str;
    }
  );
}

InstPtr CreateBinaryAdd() {
  return make_unique<ByteCodeInstruction>(
    ByteCode::BINARY_ADD, NoneType(),
    []() -> string {
      return to_string(SerializeByteCode(ByteCode::BINARY_ADD));
    }
  );
}

InstPtr CreateBinarySubtract() {
  return make_unique<ByteCodeInstruction>(
    ByteCode::BINARY_SUBTRACT, NoneType(),
    []() -> string {
      return to_string(SerializeByteCode(ByteCode::BINARY_SUBTRACT));
    }
  );
}

InstPtr CreateBinaryMultiply() {
  return make_unique<ByteCodeInstruction>(
    ByteCode::BINARY_MULTIPLY, NoneType(),
    []() -> string {
      return to_string(SerializeByteCode(ByteCode::BINARY_MULTIPLY));
    }
  );
}

InstPtr CreateBinaryTrueDivide() {
  return make_unique<ByteCodeInstruction>(
    ByteCode::BINARY_TRUE_DIVIDE, NoneType(),
    []() -> string {
      return to_string(SerializeByteCode(ByteCode::BINARY_TRUE_DIVIDE));
    }
  );
}

InstPtr CreateBinaryFloorDivide() {
  return make_unique<ByteCodeInstruction>(
    ByteCode::BINARY_FLOOR_DIVIDE, NoneType(),
    []() -> string {
      return to_string(SerializeByteCode(ByteCode::BINARY_FLOOR_DIVIDE));
    }
  );
}

InstPtr CreateBinaryXor() {
  return make_unique<ByteCodeInstruction>(
    ByteCode::BINARY_XOR, NoneType(),
    []() -> string {
      return to_string(SerializeByteCode(ByteCode::BINARY_XOR));
    }
  );
}

InstPtr CreateBinaryAnd() {
  return make_unique<ByteCodeInstruction>(
    ByteCode::BINARY_AND, NoneType(),
    []() -> string {
      return to_string(SerializeByteCode(ByteCode::BINARY_AND));
    }
  );
}

InstPtr CreateBinaryOr() {
  return make_unique<ByteCodeInstruction>(
    ByteCode::BINARY_OR, NoneType(),
    []() -> string { return to_string(SerializeByteCode(ByteCode::BINARY_OR)); }
  );
}

InstPtr CreateBinaryPower() {
  return make_unique<ByteCodeInstruction>(
    ByteCode::BINARY_POWER, NoneType(),
    []() -> string {
      return to_string(SerializeByteCode(ByteCode::BINARY_POWER));
    }
  );
}

InstPtr CreateBinaryModulo() {
  return make_unique<ByteCodeInstruction>(
    ByteCode::BINARY_MODULO, NoneType(),
    []() -> string {
      return to_string(SerializeByteCode(ByteCode::BINARY_MODULO));
    }
  );
}

InstPtr CreateBinaryLShift() {
  return make_unique<ByteCodeInstruction>(
    ByteCode::BINARY_LSHIFT, NoneType(),
    []() -> string {
      return to_string(SerializeByteCode(ByteCode::BINARY_LSHIFT));
    }
  );
}

InstPtr CreateBinaryRShift() {
  return make_unique<ByteCodeInstruction>(
    ByteCode::BINARY_RSHIFT, NoneType(),
    []() -> string {
      return to_string(SerializeByteCode(ByteCode::BINARY_RSHIFT));
    }
  );
}

InstPtr CreatePrint() {
  return make_unique<ByteCodeInstruction>(
    ByteCode::PRINT, NoneType(),
    []() -> string { return to_string(SerializeByteCode(ByteCode::PRINT)); }
  );
}

}  // namespace torchlight::bytecode