#include <functional>

#include "bytecode/ByteCode.h"
#include "bytecode/utils.h"

using torchlight::bytecode::InstStream;
using torchlight::bytecode::SerializeInstStream;
using torchlight::collections::Byte;
using torchlight::collections::Bytes;
using torchlight::collections::List;
using torchlight::collections::String;

void createTask(
  const String& name,
  const std::function<void(const String&)>& task
) {
  task(name);
}

int main() {
  createTask(String("Add_1_2"), [](const String& name) {
    InstStream stream;
    stream.Add(torchlight::bytecode::CreateLoadConst(Bytes("1")));
    stream.Add(torchlight::bytecode::CreateLoadConst(Bytes("2")));
    stream.Add(torchlight::bytecode::CreateBinaryAdd());
    stream.Add(torchlight::bytecode::CreatePrint());
    SerializeInstStream(stream, name);
  });

  createTask(String("Compare_1_2"), [](const String& name) {
    InstStream stream;
    stream.Add(torchlight::bytecode::CreateLoadConst(Bytes("1")));
    stream.Add(torchlight::bytecode::CreateLoadConst(Bytes("2")));
    stream.Add(torchlight::bytecode::CreateCompareOp(
      torchlight::bytecode::CompareOp::GREATER_THAN
    ));
    stream.Add(torchlight::bytecode::CreatePopJumpIfFalse(2));
    stream.Add(torchlight::bytecode::CreateLoadConst(Bytes("2")));
    stream.Add(torchlight::bytecode::CreatePrint());

    stream.Add(torchlight::bytecode::CreateLoadConst(Bytes("1")));
    stream.Add(torchlight::bytecode::CreatePrint());
    SerializeInstStream(stream, name);
  });

  createTask(String("Compare_2_1"), [](const String& name) {
    InstStream stream;
    stream.Add(torchlight::bytecode::CreateLoadConst(Bytes("2")));
    stream.Add(torchlight::bytecode::CreateLoadConst(Bytes("1")));
    stream.Add(torchlight::bytecode::CreateCompareOp(
      torchlight::bytecode::CompareOp::GREATER_THAN
    ));
    stream.Add(torchlight::bytecode::CreatePopJumpIfFalse(2));
    stream.Add(torchlight::bytecode::CreateLoadConst(Bytes("2")));
    stream.Add(torchlight::bytecode::CreatePrint());

    stream.Add(torchlight::bytecode::CreateLoadConst(Bytes("1")));
    stream.Add(torchlight::bytecode::CreatePrint());
    SerializeInstStream(stream, name);
  });
  return 0;
}
