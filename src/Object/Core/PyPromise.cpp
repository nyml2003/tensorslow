#include "Object/Core/PyPromise.h"
#include "Object/Container/PyList.h"
#include "Object/Core/CoreHelper.h"
#include "Object/Core/PyNone.h"
#include "Object/Function/PyNativeFunction.h"
#include "Object/Iterator/IteratorHelper.h"
#include "Object/Object.h"
#include "Object/String/PyString.h"
#include "Runtime/EventLoop.h"

namespace tensorslow::Object {

PyPromise::PyPromise(const PyNativeFunctionPtr& executor)
  : PyObject(PromiseKlass::Self()),
    state(State::PENDING),
    value(CreatePyNone()),
    onFulfilledCallbacks(CreatePyList()),
    onRejectedCallbacks(CreatePyList()) {
  auto resolve = CreatePyNativeFunction([this](const PyObjPtr& args) {
    auto val = args->as<PyList>()->GetItem(0);
    if (state == State::PENDING) {
      this->state = State::FULFILLED;
      this->value = val;
      ForEach(onFulfilledCallbacks, [this](const PyObjPtr& callback) {
        Runtime::EventLoop::Instance().EnqueueMicroTask(
          CreatePyNativeFunction([=](const PyObjPtr&) {
            auto nativeCallback = callback->as<PyNativeFunction>();
            nativeCallback->Call(CreatePyList({value}));
            return CreatePyNone();
          })
        );
      });
    }
    return CreatePyNone();
  });
  auto reject = CreatePyNativeFunction([this](const PyObjPtr& args) {
    auto reason = args->as<PyList>()->GetItem(0);
    if (state == State::PENDING) {
      this->state = State::REJECTED;
      this->value = reason;
      ForEach(onRejectedCallbacks, [this](const PyObjPtr& callback) {
        Runtime::EventLoop::Instance().EnqueueMicroTask(
          CreatePyNativeFunction([=](const PyObjPtr&) {
            auto nativeCallback = callback->as<PyNativeFunction>();
            nativeCallback->Call(CreatePyList({value}));
            return CreatePyNone();
          })
        );
      });
    }
    return CreatePyNone();
  });

  try {
    executor->Call(CreatePyList({resolve, reject}));
  } catch (const std::exception& e) {
    reject->Call(CreatePyList({CreatePyString(e.what())}));
  }
}

PyPromisePtr PyPromise::Then(const PyNativeFunctionPtr& onFulfilled) {
  auto executor = CreatePyNativeFunction([=](const PyObjPtr& args) {
    auto argList = args->as<PyList>();
    auto resolve = argList->GetItem(0)->as<PyNativeFunction>();
    auto reject = argList->GetItem(1)->as<PyNativeFunction>();
    auto callback = CreatePyNativeFunction([=](const PyObjPtr&) {
      try {
        auto result = onFulfilled->Call(CreatePyList({value}));
        resolve->Call(CreatePyList({result}));
        return CreatePyNone();
      } catch (const std::exception& e) {
        reject->Call(CreatePyList({CreatePyString(e.what())}));
        return CreatePyNone();
      }
    });
    if (state == State::FULFILLED) {
      Runtime::EventLoop::Instance().EnqueueMicroTask(callback);
    } else {
      onFulfilledCallbacks->Append(callback);
    }
    return CreatePyNone();
  });
  return CreatePyPromise(executor);
}

PyPromisePtr PyPromise::Catch(const PyNativeFunctionPtr& onRejected) {
  auto executor = CreatePyNativeFunction([=](const PyObjPtr& args) {
    auto argList = args->as<PyList>();
    auto reject = argList->GetItem(1)->as<PyNativeFunction>();
    auto callback = CreatePyNativeFunction([=](const PyObjPtr&) {
      auto result = onRejected->Call(CreatePyList({value}));
      reject->Call(CreatePyList({result}));
      return CreatePyNone();
    });
    if (state == State::REJECTED) {
      Runtime::EventLoop::Instance().EnqueueMicroTask(callback);
    } else {
      onRejectedCallbacks->Append(callback);
    }
    return CreatePyNone();
  });
  return CreatePyPromise(executor);
}

KlassPtr PromiseKlass::Self() {
  static KlassPtr instance = std::make_shared<PromiseKlass>();
  return instance;
}

void PromiseKlass::Initialize() {
  if (isInitialized) {
    return;
  }
  InitKlass(CreatePyString("Promise")->as<PyString>(), Self());

  AddAttribute(
    CreatePyString("then"),
    CreatePyNativeFunction([](const PyObjPtr& args) -> PyObjPtr {
      auto argList = args->as<PyList>();
      auto promise = argList->GetItem(0)->as<PyPromise>();
      auto onFulfilled = argList->GetItem(1)->as<PyNativeFunction>();
      return promise->Then(onFulfilled);
    })
  );
  AddAttribute(
    CreatePyString("catch"),
    CreatePyNativeFunction([](const PyObjPtr& args) -> PyObjPtr {
      auto argList = args->as<PyList>();
      auto promise = argList->GetItem(0)->as<PyPromise>();
      auto onRejected = argList->GetItem(1)->as<PyNativeFunction>();
      return promise->Catch(onRejected);
    })
  );
  isInitialized = true;
}

}  // namespace tensorslow::Object