#include "ByteCode/ByteCode.h"
#include "Collections/String/Bytes.h"
#include "Collections/String/StringHelper.h"

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
  return Collections::CreateStringWithCString(Object::ByteCodeNames.at(code));
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
  return Collections::Bytes(Collections::List({static_cast<Byte>(kind)}));
}

Collections::Bytes Serialize(Object::ByteCode code) {
  return Collections::Bytes(Collections::List({static_cast<Byte>(code)}));
}

Collections::Bytes Serialize(Object::Literal kind) {
  return Collections::Bytes(Collections::List({static_cast<Byte>(kind)}));
}

}  // namespace torchlight::Collections
