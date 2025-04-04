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
#include "Object/Iterator/PyGenerator.h"
#include "Object/Number/PyFloat.h"
#include "Object/Number/PyInteger.h"
#include "Object/Object.h"
#include "Object/PyMatrix.h"
#include "Object/String/PyString.h"
#include "Runtime/Interpreter.h"

#include <iomanip>
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
  if (obj->is(Object::StringKlass::Self())) {
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
  if (size->is(Object::IntegerKlass::Self())) {
    auto sizeValue = size->as<Object::PyInteger>()->ToU64();
    auto result = Object::CreatePyList(sizeValue)->as<Object::PyList>();
    for (Index i = 0; i < sizeValue; i++) {
      result->SetItem(i, Object::CreatePyFloat(dis(gen)));
    }
    return result;
  }
  if (size->is(Object::ListKlass::Self())) {
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
  if (arg->is(Object::ListKlass::Self())) {
    arg->as<Object::PyList>()->Shuffle();
    return Object::CreatePyNone();
  }
  if (arg->is(Object::MatrixKlass::Self())) {
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

Object::PyObjPtr Time(const Object::PyObjPtr& args) {
  CheckNativeFunctionArgumentsWithExpectedLength(args, 0);
  auto now = std::chrono::system_clock::now();

  // 分解时间点为秒和纳秒部分
  auto sec = now.time_since_epoch();
  auto sec_count = std::chrono::duration_cast<std::chrono::seconds>(sec);
  auto ns =
    std::chrono::duration_cast<std::chrono::nanoseconds>(sec - sec_count)
      .count();

  time_t nowTime = std::chrono::system_clock::to_time_t(now);
  tm localTime;
  localtime_s(&localTime, &nowTime);  // 使用线程安全的localtime_s

  std::ostringstream oss;
  oss << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");
  oss << '.' << std::setfill('0') << std::setw(9) << ns;  // 显示纳秒，补零到9位

  std::cout << "Current time: " << oss.str() << std::endl;
  return Object::CreatePyNone();
}
/*
 * def range(start, end, step):
if step == 0 or step is None:
    step = 1
if end is None:
    end = start
    start = 0
if step > 0:
    while start < end:
        yield start
        start += step
else:
    while start > end:
        yield start
        start += step
 * */
Object::PyObjPtr Range(const Object::PyObjPtr& args) {
  auto argList = args->as<Object::PyList>();
  int64_t start = 0;
  int64_t end = 0;
  int64_t step = 1;
  if (argList->Length() == 1) {
    end = argList->GetItem(0)->as<Object::PyInteger>()->ToI64();
  } else if (argList->Length() == 2) {
    start = argList->GetItem(0)->as<Object::PyInteger>()->ToI64();
    end = argList->GetItem(1)->as<Object::PyInteger>()->ToI64();
  } else if (argList->Length() == 3) {
    start = argList->GetItem(0)->as<Object::PyInteger>()->ToI64();
    end = argList->GetItem(1)->as<Object::PyInteger>()->ToI64();
    step = argList->GetItem(2)->as<Object::PyInteger>()->ToI64();
  }
  if (step == 0) {
    throw std::runtime_error("Step cannot be zero");
  }
  return Object::CreatePyGenerator(
    [start, end, step](const Object::PyGeneratorPtr& generator) mutable {
      if (step > 0) {
        while (start < end) {
          auto value = Object::CreatePyInteger(start);
          start += step;
          if (start >= end) {
            generator->SetExhausted();
          }
          return value;
        }
      } else {
        while (start > end) {
          auto value = Object::CreatePyInteger(start);
          start += step;
          if (start <= end) {
            generator->SetExhausted();
          }
          return value;
        }
      }
      generator->SetExhausted();
      return Object::CreatePyNone();
    }
  );
}

Object::PyObjPtr Type(const Object::PyObjPtr& args) {
  CheckNativeFunctionArgumentsWithExpectedLength(args, 1);
  auto obj = args->getitem(Object::CreatePyInteger(0));
  return obj->Klass()->Type();
}

Object::PyObjPtr BuildClass(const Object::PyObjPtr& args) {
  auto argList = args->as<Object::PyList>();
  // 解析参数：函数、类名和基类
  auto function = argList->GetItem(0)->as<Object::PyFunction>();
  auto name = argList->GetItem(1)->as<Object::PyString>();
  auto bases = argList->GetItem(2)->as<Object::PyList>();

  // 创建执行环境
  auto globals = function->Globals();
  auto preFrame = Runtime::Interpreter::Instance().CurrentFrame();
  auto __name__ = globals->getitem(Object::CreatePyString("__name__"));
  // 保存当前帧
  // 创建新帧并执行类定义函数
  auto frame = Object::CreateFrameWithPyFunction(
    function, Object::CreatePyList({})->as<Object::PyList>()
  );
  auto result = frame->Eval();
  Runtime::Interpreter::Instance().BackToParentFrame();
  if (!result->is(Object::NoneKlass::Self())) {
    throw std::runtime_error("Class definition failed");
  }
  // 获取执行结果
  auto classDict = frame->CurrentLocals();
  // 创建新的类型对象
  auto typeName =
    StringConcat(
      Object::CreatePyList({__name__, Object::CreatePyString("."), name})
    )
      ->as<Object::PyString>();
  auto klass = Object::CreatePyKlass(typeName, classDict, bases);
  auto type = Object::CreatePyType(klass);
  return type;
}

}  // namespace torchlight::Function