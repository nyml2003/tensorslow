#include "Runtime/RuntimeHelper.h"

#include "Object/MixinCollections.h"
#include "Object/PyInteger.h"
#include "Object/PyList.h"
#include "Object/PyNone.h"
#include "Object/PyString.h"

#include <iostream>
#include <random>
#include <thread>

namespace torchlight::Runtime {

Object::PyObjPtr RandInt(Object::PyObjPtr args) {
  if (args->Klass() != Object::ListKlass::Self()) {
    throw std::runtime_error("Cannot get argument from non-list object");
  }
  auto arguments = std::dynamic_pointer_cast<Object::PyList>(args);
  if (Object::ToU64(arguments->len()) != 2) {
    throw std::runtime_error("RandInt function need 2 argument");
  }
  auto left = std::dynamic_pointer_cast<Object::PyInteger>(
    arguments->getitem(Object::CreatePyInteger(0))
  );
  // if (left->ge(Object::CreatePyInteger(
  //       Collections::CreateIntegerWithCString("0x7fffffff")
  //     ))) {
  //   throw std::runtime_error(
  //     "RandInt function need left argument less than 0x7fffffff"
  //   );
  // }
  auto cppLeft = Object::ToU64(left);
  auto right = std::dynamic_pointer_cast<Object::PyInteger>(
    arguments->getitem(Object::CreatePyInteger(1))
  );
  // if (right->ge(Object::CreatePyInteger(
  //       Collections::CreateIntegerWithCString("0x7fffffff")
  //     ))) {
  //   throw std::runtime_error(
  //     "RandInt function need right argument less than 0x7fffffff"
  //   );
  // }
  auto cppRight = Object::ToU64(right);
  if (cppLeft >= cppRight) {
    throw std::runtime_error(
      "RandInt function need left argument less than right argument"
    );
  }
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

Object::PyObjPtr Sleep(Object::PyObjPtr args) {
  if (args->Klass() != Object::ListKlass::Self()) {
    throw std::runtime_error("Cannot get argument from non-list object");
  }
  auto arguments = std::dynamic_pointer_cast<Object::PyList>(args);
  if (Object::ToU64(arguments->len()) != 1) {
    throw std::runtime_error("Sleep function need 1 argument");
  }
  auto seconds = std::dynamic_pointer_cast<Object::PyInteger>(
    arguments->getitem(Object::CreatePyInteger(0))
  );
  // if (seconds->lt(Object::CreatePyInteger(0))) {
  //   throw std::runtime_error("Sleep function need non-negative argument");
  // }
  std::this_thread::sleep_for(std::chrono::seconds(Object::ToU64(seconds)));
  return Object::CreatePyNone();
}

Object::PyObjPtr Input(Object::PyObjPtr args) {
  if (args->Klass() != Object::ListKlass::Self()) {
    throw std::runtime_error("Cannot get argument from non-list object");
  }
  auto arguments = std::dynamic_pointer_cast<Object::PyList>(args);
  if (Object::ToU64(arguments->len()) != 1) {
    throw std::runtime_error("Input function need 1 argument");
  }
  auto prompt = std::dynamic_pointer_cast<Object::PyString>(
    arguments->getitem(Object::CreatePyInteger(0))
  );
  std::string input;
  std::cout << Collections::ToCppString(prompt);
  std::cin >> input;
  return Object::CreatePyString(input);
}

}  // namespace torchlight::Runtime
