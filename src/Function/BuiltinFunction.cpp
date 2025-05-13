#include "Function/BuiltinFunction.h"
#include "Collections/Integer/IntegerHelper.h"
#include "Object/Container/PyList.h"
#include "Object/Core/PyBoolean.h"
#include "Object/Core/PyNone.h"
#include "Object/Core/PyType.h"
#include "Object/Function/PyFunction.h"
#include "Object/Function/PyNativeFunction.h"
#include "Object/Iterator/PyGenerator.h"
#include "Object/Matrix/PyMatrix.h"
#include "Object/Number/PyFloat.h"
#include "Object/Number/PyInteger.h"
#include "Object/Object.h"
#include "Object/String/PyString.h"
#include "Runtime/Interpreter.h"
#include "Tools/Logger/ConsoleLogger.h"

#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>
#include <thread>
namespace tensorslow::Function {

Object::PyObjPtr Identity(const Object::PyObjPtr& args) {
  CheckNativeFunctionArgumentsWithExpectedLength(args, 1);
  auto obj = args->as<Object::PyList>()->GetItem(0);
  return Object::CreatePyString(
    Collections::CreateIntegerWithU64(reinterpret_cast<uint64_t>(obj.get()))
      .ToHexString(),
    false
  );
}

void DebugPrint(const Object::PyObjPtr& obj) {
  tensorslow::ConsoleLogger::getInstance().log("[DEBUG] ");
  if (obj->is(Object::StringKlass::Self())) {
    tensorslow::ConsoleLogger::getInstance().log(
      obj->as<Object::PyString>()->ToCppString()
    );
  } else {
    tensorslow::ConsoleLogger::getInstance().log(
      obj->str()->as<Object::PyString>()->ToCppString()
    );
  }
  tensorslow::ConsoleLogger::getInstance().log("\n");
}

Object::PyObjPtr Print(const Object::PyObjPtr& args) {
  CheckNativeFunctionArguments(args);
  auto argList = args->as<Object::PyList>();
  if (argList->Length() == 0) {
    Object::CreatePyString("\n")->Print();
    return Object::CreatePyNone();
  }
  argList->GetItem(0)->str()->as<Object::PyString>()->Print();
  auto sep = Object::CreatePyString(" ")->as<Object::PyString>();
  for (Index i = 1; i < argList->Length(); i++) {
    sep->Print();
    auto arg = argList->GetItem(i);
    arg->str()->as<Object::PyString>()->Print();
  }
  Object::CreatePyString("\n")->Print();
  return Object::CreatePyNone();
}

Object::PyObjPtr Len(const Object::PyObjPtr& args) {
  CheckNativeFunctionArgumentsWithExpectedLength(args, 1);
  return args->as<Object::PyList>()->GetItem(0)->len();
}

Object::PyObjPtr Next(const Object::PyObjPtr& args) {
  CheckNativeFunctionArgumentsWithExpectedLength(args, 1);
  return args->as<Object::PyList>()->GetItem(0)->next();
}

Object::PyObjPtr RandInt(const Object::PyObjPtr& args) {
  CheckNativeFunctionArgumentsWithExpectedLength(args, 2);
  auto argList = args->as<Object::PyList>();
  auto left = argList->GetItem(0)->as<Object::PyInteger>();
  auto right = argList->GetItem(1)->as<Object::PyInteger>();
  if (IsTrue(left->ge(Object::CreatePyInteger(0x7fffffff))) ||
      IsTrue(right->ge(Object::CreatePyInteger(0x7fffffff))) ||
      IsTrue(left->ge(right))) {
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
    auto result = Object::CreatePyList(sizeValue);
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
  if (args->as<Object::PyList>()->Length() > 0) {
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
  return args->as<Object::PyList>()->GetItem(0)->iter();
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
#if defined(_WIN32) || defined(_WIN64)
  // Windows 平台使用 localtime_s
  localtime_s(&localTime, &nowTime);
#else
  // POSIX 平台使用 localtime_r
  localtime_r(&nowTime, &localTime);
#endif

  std::ostringstream oss;
  oss << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");
  oss << '.' << std::setfill('0') << std::setw(9) << ns;  // 显示纳秒，补零到9位

  tensorslow::ConsoleLogger::getInstance().log("Current time: ");
  tensorslow::ConsoleLogger::getInstance().log(oss.str());
  tensorslow::ConsoleLogger::getInstance().log("\n");
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
      }
      while (start > end) {
        auto value = Object::CreatePyInteger(start);
        start += step;
        if (start <= end) {
          generator->SetExhausted();
        }
        return value;
      }
      throw std::runtime_error("Range generator exhausted");
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
  auto name = argList->GetItem(1);
  auto bases = argList->GetItem(2)->as<Object::PyList>();

  // 创建执行环境
  auto globals = function->Globals();
  auto preFrame = Runtime::Interpreter::Instance().CurrentFrame();
  auto __name__ = globals->getitem(Object::CreatePyString("__name__"));
  // 保存当前帧
  // 创建新帧并执行类定义函数
  auto frame =
    Object::CreateFrameWithPyFunction(function, Object::CreatePyList());
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

auto LogisticLoss(const Object::PyObjPtr& args) noexcept -> Object::PyObjPtr {
  auto argList = args->as<Object::PyList>();
  auto matrix = argList->GetItem(0)->as<Object::PyMatrix>();
  const Collections::List<double>& values = matrix->Ravel();
  Collections::List<double> result(values.Size(), double(0));
  for (Index i = 0; i < values.Size(); i++) {
    double value = values[i];
    if (-value > 1e2) {
      result[i] = -value;
    }
    result[i] = std::log(1 + std::exp(-value));
  }
  return Object::CreatePyMatrix(
    Collections::Matrix(matrix->RowsIndex(), matrix->ColsIndex(), result)
  );
}

auto LogisticLossDerivative(const Object::PyObjPtr& args) noexcept
  -> Object::PyObjPtr {
  auto argList = args->as<Object::PyList>();
  auto matrix = argList->GetItem(0)->as<Object::PyMatrix>();
  const Collections::List<double>& values = matrix->Ravel();
  Collections::List<double> result(values.Size(), double(0));
  for (Index i = 0; i < values.Size(); i++) {
    double value = values[i];
    if (-value > 1e2) {
      result[i] = -value;
    }
    result[i] = -1 / (1 + std::exp(value));
  }
  return Object::CreatePyMatrix(
    Collections::Matrix(matrix->RowsIndex(), matrix->ColsIndex(), result)
  );
}

auto Sum(const Object::PyObjPtr& args) noexcept -> Object::PyObjPtr {
  auto argList = args->as<Object::PyList>();
  auto matrix = argList->GetItem(0)->as<Object::PyMatrix>();
  const Collections::List<double>& values = matrix->Ravel();
  double result = 0;
  for (Index i = 0; i < values.Size(); i++) {
    result += values[i];
  }
  return Object::CreatePyFloat(result);
}

auto Log(const Object::PyObjPtr& args) noexcept -> Object::PyObjPtr {
  auto argList = args->as<Object::PyList>();
  auto matrix = argList->GetItem(0)->as<Object::PyMatrix>();
  const Collections::List<double>& values = matrix->Ravel();
  Collections::List<double> result(values.Size(), double(0));
  for (Index i = 0; i < values.Size(); i++) {
    double value = values[i];
    result[i] = std::log(value);
  }
  return Object::CreatePyMatrix(
    Collections::Matrix(matrix->RowsIndex(), matrix->ColsIndex(), result)
  );
}

auto SoftMax(const Object::PyObjPtr& args) noexcept -> Object::PyObjPtr {
  auto argList = args->as<Object::PyList>();
  auto matrix = argList->GetItem(0)->as<Object::PyMatrix>();
  const Collections::List<double>& values = matrix->Ravel();
  Collections::List<double> result(values.Size(), double(0));
  double sum = 0;
  for (Index i = 0; i < values.Size(); i++) {
    double value = values[i];
    result[i] = std::exp(value);
    sum += result[i];
  }
  for (Index i = 0; i < values.Size(); i++) {
    result[i] /= sum;
  }
  return Object::CreatePyMatrix(
    Collections::Matrix(matrix->RowsIndex(), matrix->ColsIndex(), result)
  );
}

auto Max(const Object::PyObjPtr& args) noexcept -> Object::PyObjPtr {
  auto argList = args->as<Object::PyList>();
  auto matrix = argList->GetItem(0)->as<Object::PyMatrix>();
  const Collections::List<double>& values = matrix->Ravel();
  double maxValue = values[0];
  for (Index i = 1; i < values.Size(); i++) {
    if (values[i] > maxValue) {
      maxValue = values[i];
    }
  }
  return Object::CreatePyFloat(maxValue);
}

auto ArgMax(const Object::PyObjPtr& args) noexcept -> Object::PyObjPtr {
  auto argList = args->as<Object::PyList>();
  auto matrix = argList->GetItem(0)->as<Object::PyMatrix>();
  const Collections::List<double>& values = matrix->Ravel();
  double maxValue = values[0];
  Index maxIndex = 0;
  for (Index i = 1; i < values.Size(); i++) {
    if (values[i] > maxValue) {
      maxValue = values[i];
      maxIndex = i;
    }
  }
  return Object::CreatePyInteger(maxIndex);
}

auto Hash(const Object::PyObjPtr& args) noexcept -> Object::PyObjPtr {
  auto argList = args->as<Object::PyList>();
  auto arg = argList->GetItem(0);
  return arg->hash();
}

}  // namespace tensorslow::Function