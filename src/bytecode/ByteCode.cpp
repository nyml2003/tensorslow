#include "bytecode/ByteCode.h"

#include "bytecode/utils.h"

namespace torchlight::bytecode {

InstPtr CreateLoadConst(Bytes value) {
  return make_shared<ByteCodeInstruction>(
    ByteCode::LOAD_CONST, value,
    [value]() -> Bytes {
      auto value_size_list = SerializeUInt64(value.Size());
      List<Byte> result;
      result.Add(SerializeByteCode(ByteCode::LOAD_CONST));
      for (collections::Index i = 0; i < value_size_list.Size(); ++i) {
        result.Add(value_size_list.Get(i));
      }
      return Bytes(result).Concat(value);
    }
  );
}

InstPtr CreateCompareOp(CompareOp op) {
  return make_shared<ByteCodeInstruction>(
    ByteCode::COMPARE_OP, op,
    [op]() -> Bytes {
      List<Byte> result;
      result.Add(SerializeByteCode(ByteCode::COMPARE_OP));
      result.Add(static_cast<Byte>(op));
      return Bytes(result);
    }
  );
}

InstPtr CreatePopJumpIfFalse(uint32_t offset) {
  return make_shared<ByteCodeInstruction>(
    ByteCode::POP_JUMP_IF_FALSE, offset,
    [offset]() -> Bytes {
      auto offset_list = SerializeUInt32(offset);
      List<Byte> result;
      result.Add(SerializeByteCode(ByteCode::POP_JUMP_IF_FALSE));
      for (collections::Index i = 0; i < offset_list.Size(); ++i) {
        result.Add(offset_list.Get(i));
      }
      return Bytes(result);
    }
  );
}

InstPtr CreateBinaryAdd() {
  return make_shared<ByteCodeInstruction>(
    ByteCode::BINARY_ADD, NoneType(),
    []() -> Bytes {
      List<Byte> result;
      result.Add(SerializeByteCode(ByteCode::BINARY_ADD));
      return Bytes(result);
    }
  );
}

InstPtr CreateBinarySubtract() {
  return make_shared<ByteCodeInstruction>(
    ByteCode::BINARY_SUBTRACT, NoneType(),
    []() -> Bytes {
      List<Byte> result;
      result.Add(SerializeByteCode(ByteCode::BINARY_SUBTRACT));
      return Bytes(result);
    }
  );
}

InstPtr CreateBinaryMultiply() {
  return make_shared<ByteCodeInstruction>(
    ByteCode::BINARY_MULTIPLY, NoneType(),
    []() -> Bytes {
      List<Byte> result;
      result.Add(SerializeByteCode(ByteCode::BINARY_MULTIPLY));
      return Bytes(result);
    }
  );
}

InstPtr CreateBinaryTrueDivide() {
  return make_shared<ByteCodeInstruction>(
    ByteCode::BINARY_TRUE_DIVIDE, NoneType(),
    []() -> Bytes {
      List<Byte> result;
      result.Add(SerializeByteCode(ByteCode::BINARY_TRUE_DIVIDE));
      return Bytes(result);
    }
  );
}

InstPtr CreateBinaryFloorDivide() {
  return make_shared<ByteCodeInstruction>(
    ByteCode::BINARY_FLOOR_DIVIDE, NoneType(),
    []() -> Bytes {
      List<Byte> result;
      result.Add(SerializeByteCode(ByteCode::BINARY_FLOOR_DIVIDE));
      return Bytes(result);
    }
  );
}

InstPtr CreateBinaryXor() {
  return make_shared<ByteCodeInstruction>(
    ByteCode::BINARY_XOR, NoneType(),
    []() -> Bytes {
      List<Byte> result;
      result.Add(SerializeByteCode(ByteCode::BINARY_XOR));
      return Bytes(result);
    }
  );
}

InstPtr CreateBinaryAnd() {
  return make_shared<ByteCodeInstruction>(
    ByteCode::BINARY_AND, NoneType(),
    []() -> Bytes {
      List<Byte> result;
      result.Add(SerializeByteCode(ByteCode::BINARY_AND));
      return Bytes(result);
    }
  );
}

InstPtr CreateBinaryOr() {
  return make_shared<ByteCodeInstruction>(
    ByteCode::BINARY_OR, NoneType(),
    []() -> Bytes {
      List<Byte> result;
      result.Add(SerializeByteCode(ByteCode::BINARY_OR));
      return Bytes(result);
    }
  );
}

InstPtr CreateBinaryPower() {
  return make_shared<ByteCodeInstruction>(
    ByteCode::BINARY_POWER, NoneType(),
    []() -> Bytes {
      List<Byte> result;
      result.Add(SerializeByteCode(ByteCode::BINARY_POWER));
      return Bytes(result);
    }
  );
}

InstPtr CreateBinaryModulo() {
  return make_shared<ByteCodeInstruction>(
    ByteCode::BINARY_MODULO, NoneType(),
    []() -> Bytes {
      List<Byte> result;
      result.Add(SerializeByteCode(ByteCode::BINARY_MODULO));
      return Bytes(result);
    }
  );
}

InstPtr CreateBinaryLShift() {
  return make_shared<ByteCodeInstruction>(
    ByteCode::BINARY_LSHIFT, NoneType(),
    []() -> Bytes {
      List<Byte> result;
      result.Add(SerializeByteCode(ByteCode::BINARY_LSHIFT));
      return Bytes(result);
    }
  );
}

InstPtr CreateBinaryRShift() {
  return make_shared<ByteCodeInstruction>(
    ByteCode::BINARY_RSHIFT, NoneType(),
    []() -> Bytes {
      List<Byte> result;
      result.Add(SerializeByteCode(ByteCode::BINARY_RSHIFT));
      return Bytes(result);
    }
  );
}

InstPtr CreatePrint() {
  return make_shared<ByteCodeInstruction>(
    ByteCode::PRINT, NoneType(),
    []() -> Bytes {
      List<Byte> result;
      result.Add(SerializeByteCode(ByteCode::PRINT));
      return Bytes(result);
    }
  );
}

}  // namespace torchlight::bytecode