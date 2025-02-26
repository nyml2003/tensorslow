#include "ByteCode/ByteCode.h"
#include "Collections/Bytes.h"
#include "Collections/StringHelper.h"

namespace torchlight::Object {

std::map<ByteCode, const char*> ByteCodeNames = {
  {ByteCode::POP_TOP, "POP_TOP"},
  {ByteCode::NOP, "NOP"},
  {ByteCode::UNARY_POSITIVE, "UNARY_POSITIVE"},
  {ByteCode::UNARY_NEGATIVE, "UNARY_NEGATIVE"},
  {ByteCode::UNARY_NOT, "UNARY_NOT"},
  {ByteCode::UNARY_INVERT, "UNARY_INVERT"},
  {ByteCode::BINARY_MATRIX_MULTIPLY, "BINARY_MATRIX_MULTIPLY"},
  {ByteCode::INPLACE_MATRIX_MULTIPLY, "INPLACE_MATRIX_MULTIPLY"},
  {ByteCode::BINARY_POWER, "BINARY_POWER"},
  {ByteCode::BINARY_MULTIPLY, "BINARY_MULTIPLY"},
  {ByteCode::BINARY_MODULO, "BINARY_MODULO"},
  {ByteCode::BINARY_ADD, "BINARY_ADD"},
  {ByteCode::BINARY_SUBTRACT, "BINARY_SUBTRACT"},
  {ByteCode::BINARY_SUBSCR, "BINARY_SUBSCR"},
  {ByteCode::BINARY_FLOOR_DIVIDE, "BINARY_FLOOR_DIVIDE"},
  {ByteCode::BINARY_TRUE_DIVIDE, "BINARY_TRUE_DIVIDE"},
  {ByteCode::INPLACE_FLOOR_DIVIDE, "INPLACE_FLOOR_DIVIDE"},
  {ByteCode::INPLACE_TRUE_DIVIDE, "INPLACE_TRUE_DIVIDE"},
  {ByteCode::GET_LEN, "GET_LEN"},
  {ByteCode::INPLACE_ADD, "INPLACE_ADD"},
  {ByteCode::INPLACE_SUBTRACT, "INPLACE_SUBTRACT"},
  {ByteCode::INPLACE_MULTIPLY, "INPLACE_MULTIPLY"},
  {ByteCode::INPLACE_MODULO, "INPLACE_MODULO"},
  {ByteCode::STORE_SUBSCR, "STORE_SUBSCR"},
  {ByteCode::DELETE_SUBSCR, "DELETE_SUBSCR"},
  {ByteCode::BINARY_LSHIFT, "BINARY_LSHIFT"},
  {ByteCode::BINARY_RSHIFT, "BINARY_RSHIFT"},
  {ByteCode::BINARY_AND, "BINARY_AND"},
  {ByteCode::BINARY_XOR, "BINARY_XOR"},
  {ByteCode::BINARY_OR, "BINARY_OR"},
  {ByteCode::INPLACE_POWER, "INPLACE_POWER"},
  {ByteCode::GET_ITER, "GET_ITER"},
  {ByteCode::LOAD_BUILD_CLASS, "LOAD_BUILD_CLASS"},
  {ByteCode::INPLACE_LSHIFT, "INPLACE_LSHIFT"},
  {ByteCode::INPLACE_RSHIFT, "INPLACE_RSHIFT"},
  {ByteCode::INPLACE_AND, "INPLACE_AND"},
  {ByteCode::INPLACE_XOR, "INPLACE_XOR"},
  {ByteCode::INPLACE_OR, "INPLACE_OR"},
  {ByteCode::RETURN_VALUE, "RETURN_VALUE"},
  {ByteCode::STORE_NAME, "STORE_NAME"},
  {ByteCode::DELETE_NAME, "DELETE_NAME"},
  {ByteCode::UNPACK_SEQUENCE, "UNPACK_SEQUENCE"},
  {ByteCode::FOR_ITER, "FOR_ITER"},
  {ByteCode::STORE_ATTR, "STORE_ATTR"},
  {ByteCode::DELETE_ATTR, "DELETE_ATTR"},
  {ByteCode::STORE_GLOBAL, "STORE_GLOBAL"},
  {ByteCode::DELETE_GLOBAL, "DELETE_GLOBAL"},
  {ByteCode::LOAD_CONST, "LOAD_CONST"},
  {ByteCode::LOAD_NAME, "LOAD_NAME"},
  {ByteCode::BUILD_TUPLE, "BUILD_TUPLE"},
  {ByteCode::BUILD_LIST, "BUILD_LIST"},
  {ByteCode::BUILD_SET, "BUILD_SET"},
  {ByteCode::BUILD_MAP, "BUILD_MAP"},
  {ByteCode::LOAD_ATTR, "LOAD_ATTR"},
  {ByteCode::COMPARE_OP, "COMPARE_OP"},
  {ByteCode::IMPORT_NAME, "IMPORT_NAME"},
  {ByteCode::IMPORT_FROM, "IMPORT_FROM"},
  {ByteCode::JUMP_FORWARD, "JUMP_FORWARD"},
  {ByteCode::JUMP_IF_FALSE_OR_POP, "JUMP_IF_FALSE_OR_POP"},
  {ByteCode::JUMP_IF_TRUE_OR_POP, "JUMP_IF_TRUE_OR_POP"},
  {ByteCode::JUMP_ABSOLUTE, "JUMP_ABSOLUTE"},
  {ByteCode::POP_JUMP_IF_FALSE, "POP_JUMP_IF_FALSE"},
  {ByteCode::POP_JUMP_IF_TRUE, "POP_JUMP_IF_TRUE"},
  {ByteCode::LOAD_GLOBAL, "LOAD_GLOBAL"},
  {ByteCode::BINARY_OP, "BINARY_OP"},
  {ByteCode::LOAD_FAST, "LOAD_FAST"},
  {ByteCode::STORE_FAST, "STORE_FAST"},
  {ByteCode::DELETE_FAST, "DELETE_FAST"},
  {ByteCode::MAKE_FUNCTION, "MAKE_FUNCTION"},
  {ByteCode::BUILD_SLICE, "BUILD_SLICE"},
  {ByteCode::LOAD_CLOSURE, "LOAD_CLOSURE"},
  {ByteCode::CALL_FUNCTION, "CALL_FUNCTION"},
  {ByteCode::LOAD_METHOD, "LOAD_METHOD"},
  {ByteCode::CALL_METHOD, "CALL_METHOD"},
  {ByteCode::ERROR, "ERROR"},
};

}

namespace torchlight::Collections {

Collections::String ToString(None /*kind*/) {
  return Collections::CreateStringWithCString("None");
}

Collections::String ToString(Object::CompareOp kind) {
  switch (kind) {
    case Object::CompareOp::LESS_THAN:
      return Collections::CreateStringWithCString("<");
    case Object::CompareOp::LESS_THAN_EQUAL:
      return Collections::CreateStringWithCString("<=");
    case Object::CompareOp::EQUAL:
      return Collections::CreateStringWithCString("==");
    case Object::CompareOp::NOT_EQUAL:
      return Collections::CreateStringWithCString("!=");
    case Object::CompareOp::GREATER_THAN:
      return Collections::CreateStringWithCString(">");
    case Object::CompareOp::GREATER_THAN_EQUAL:
      return Collections::CreateStringWithCString(">=");
    case Object::CompareOp::IN:
      return Collections::CreateStringWithCString("IN");
    case Object::CompareOp::NOT_IN:
      return Collections::CreateStringWithCString("NOT IN");
    case Object::CompareOp::IS:
      return Collections::CreateStringWithCString("IS");
    case Object::CompareOp::IS_NOT:
      return Collections::CreateStringWithCString("IS NOT");
  }
  return Collections::CreateStringWithCString("UNKNOWN");
}

Collections::String ToString(Object::ByteCode code) {
  return Collections::CreateStringWithCString(Object::ByteCodeNames[code]);
}

Collections::String ToString(Object::Literal kind) {
  switch (kind) {
    case Object::Literal::INTEGER:
      return Collections::CreateStringWithCString("INTEGER");
    case Object::Literal::ZERO:
      return Collections::CreateStringWithCString("ZERO");
    case Object::Literal::FLOAT:
      return Collections::CreateStringWithCString("FLOAT");
    case Object::Literal::STRING:
      return Collections::CreateStringWithCString("STRING");
    case Object::Literal::NONE:
      return Collections::CreateStringWithCString("NONE");
    case Object::Literal::TRUE:
      return Collections::CreateStringWithCString("TRUE");
    case Object::Literal::FALSE:
      return Collections::CreateStringWithCString("FALSE");
    case Object::Literal::LIST:
      return Collections::CreateStringWithCString("LIST");
    case Object::Literal::CODE:
      return Collections::CreateStringWithCString("CODE");
    case Object::Literal::BYTES:
      return Collections::CreateStringWithCString("BYTES");
  }
  return Collections::CreateStringWithCString("UNKNOWN");
}

Collections::Bytes Serialize(None /*kind*/) {
  return Collections::Bytes();
}

Collections::Bytes Serialize(Object::CompareOp kind) {
  return Collections::Bytes({static_cast<Byte>(kind)});
}

Collections::Bytes Serialize(Object::ByteCode code) {
  return Collections::Bytes({static_cast<Byte>(code)});
}

Collections::Bytes Serialize(Object::Literal kind) {
  return Collections::Bytes({static_cast<Byte>(kind)});
}

}  // namespace torchlight::Collections
