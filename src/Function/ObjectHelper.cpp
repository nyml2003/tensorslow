#include "Function/ObjectHelper.h"
#include "Collections/Integer/IntegerHelper.h"
#include "Object/Container/PyDictionary.h"
#include "Object/Container/PyList.h"
#include "Object/Core/PyBoolean.h"
#include "Object/Core/PyNone.h"
#include "Object/Core/PyObject.h"
#include "Object/Core/PyType.h"
#include "Object/Function/PyFunction.h"
#include "Object/Function/PyIife.h"
#include "Object/Function/PyMethod.h"
#include "Object/Function/PyNativeFunction.h"
#include "Object/Iterator/Iterator.h"
#include "Object/Number/PyFloat.h"
#include "Object/Number/PyInteger.h"
#include "Object/Object.h"
#include "Object/PyMatrix.h"
#include "Object/String/PyString.h"
#include "Runtime/Interpreter.h"

#include <iostream>
#include <random>
#include <thread>
namespace torchlight::Function {

Object::PyObjPtr Identity(const Object::PyObjPtr& args) {
  CheckNativeFunctionArgumentsWithExpectedLength(args, 1);
  auto obj = args->as<Object::PyList>()->GetItem(0);
  return Object::CreatePyString(
    Collections::CreateIntegerWithU64(reinterpret_cast<uint64_t>(obj.get()))
      .ToHexString()
  );
}

void DebugPrint(const Object::PyObjPtr& obj) {
  if (obj->is<Object::PyString>()) {
    std::cout << obj->as<Object::PyString>()->ToCppString() << std::endl;
    return;
  }
  std::cout << obj->str()->as<Object::PyString>()->ToCppString() << std::endl;
}

Object::PyObjPtr Print(const Object::PyObjPtr& args) {
  CheckNativeFunctionArguments(args);
  auto argList = args->as<Object::PyList>();
  for (Index i = 0; i < argList->Length(); i++) {
    auto arg = argList->GetItem(i);
    arg->str()->as<Object::PyString>()->Print();
    if (i < argList->Length() - 1) {
      Object::CreatePyString(" ")->as<Object::PyString>()->Print();
    }
  }
  Object::CreatePyString("\n")->as<Object::PyString>()->Print();
  return Object::CreatePyNone();
}

Object::PyObjPtr Len(const Object::PyObjPtr& args) {
  CheckNativeFunctionArgumentsWithExpectedLength(args, 1);
  auto value = args->as<Object::PyList>()->GetItem(0);
  return value->len();
}

Object::PyObjPtr Next(const Object::PyObjPtr& args) {
  CheckNativeFunctionArgumentsWithExpectedLength(args, 1);
  auto value = args->as<Object::PyList>()->GetItem(0);
  return value->next();
}

Object::PyObjPtr RandInt(const Object::PyObjPtr& args) {
  CheckNativeFunctionArgumentsWithExpectedLength(args, 2);
  auto argList = args->as<Object::PyList>();
  auto left = argList->GetItem(0)->as<Object::PyInteger>();
  auto right = argList->GetItem(1)->as<Object::PyInteger>();
  if (IsTrue(left->ge(Object::CreatePyInteger(0x7fffffff))) ||
      IsTrue(right->ge(Object::CreatePyInteger(0x7fffffff))) ||
      IsTrue(left->ge(right))) {
    left->str()->as<Object::PyString>()->PrintLine();
    right->str()->as<Object::PyString>()->PrintLine();
    throw std::runtime_error(
      "RandInt function need left argument less than right argument"
    );
  }
  auto cppLeft = left->ToU64();
  auto cppRight = right->ToU64();
  std::random_device rd;   // 随机数设备，用于生成种子
  std::mt19937 gen(rd());  // 使用 Mersenne Twister 算法生成随机数
  std::uniform_int_distribution<>
    dis(  // 生成 [cppLeft, cppRight] 之间的均匀分布
      static_cast<std::mt19937::result_type>(cppLeft),
      static_cast<std::mt19937::result_type>(cppRight)
    );

  auto result = dis(gen);
  return Object::CreatePyInteger(result);
}

Object::PyObjPtr Sleep(const Object::PyObjPtr& args) {
  CheckNativeFunctionArgumentsWithExpectedLength(args, 1);
  auto seconds =
    args->as<Object::PyList>()->GetItem(0)->as<Object::PyInteger>();
  if (IsTrue(seconds->lt(Object::CreatePyInteger(0)))) {
    seconds->str()->as<Object::PyString>()->PrintLine();
    throw std::runtime_error("Sleep function need non-negative argument");
  }
  auto secondsValue = seconds->ToU64();
  std::this_thread::sleep_for(std::chrono::seconds(secondsValue));
  return Object::CreatePyNone();
}
Object::PyObjPtr Normal(const Object::PyObjPtr& args) {
  CheckNativeFunctionArgumentsWithExpectedLength(args, 3);
  auto argList = args->as<Object::PyList>();
  auto loc = argList->GetItem(0)->as<Object::PyFloat>()->Value();
  auto scale = argList->GetItem(1)->as<Object::PyFloat>()->Value();
  std::random_device randomDevice;
  std::mt19937 gen(randomDevice());
  std::normal_distribution<> dis(loc, scale);
  auto size = argList->GetItem(2);
  if (size->is<Object::PyInteger>()) {
    auto sizeValue = size->as<Object::PyInteger>()->ToU64();
    auto result = Object::CreatePyList(sizeValue)->as<Object::PyList>();
    for (Index i = 0; i < sizeValue; i++) {
      result->SetItem(i, Object::CreatePyFloat(dis(gen)));
    }
    return result;
  }
  if (size->is<Object::PyList>()) {
    auto sizeList = size->as<Object::PyList>();
    auto row = sizeList->GetItem(0)->as<Object::PyInteger>()->ToU64();
    auto col = sizeList->GetItem(1)->as<Object::PyInteger>()->ToU64();
    auto sizeValue = row * col;
    Collections::List<double> result(sizeValue);
    for (Index i = 0; i < sizeValue; i++) {
      result.Push(dis(gen));
    }
    return Object::CreatePyMatrix(Collections::Matrix(row, col, result));
  }
  throw std::runtime_error("Normal function need integer or list argument");
}

Object::PyObjPtr Shuffle(const Object::PyObjPtr& args) {
  CheckNativeFunctionArgumentsWithExpectedLength(args, 1);
  auto argList = args->as<Object::PyList>();
  auto arg = argList->GetItem(0);
  if (arg->is<Object::PyList>()) {
    arg->as<Object::PyList>()->Shuffle();
    return Object::CreatePyNone();
  }
  if (arg->is<Object::PyMatrix>()) {
    arg->as<Object::PyMatrix>()->Shuffle();
    return Object::CreatePyNone();
  }
  throw std::runtime_error("Shuffle function need list or matrix argument");
}

Object::PyObjPtr Input(const Object::PyObjPtr& args) {
  CheckNativeFunctionArguments(args);
  if (args->as<Object::PyList>()->Length() == 1) {
    auto prompt = args->as<Object::PyList>()
                    ->GetItem(0)
                    ->as<Object::PyString>()
                    ->ToCppString();
    std::cout << prompt;
  }
  std::string input;
  std::cin >> input;
  return Object::CreatePyString(input);
}

Object::PyObjPtr Iter(const Object::PyObjPtr& args) {
  CheckNativeFunctionArgumentsWithExpectedLength(args, 1);
  auto obj = args->as<Object::PyList>()->GetItem(0);
  return obj->iter();
}

}  // namespace torchlight::Function