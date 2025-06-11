//
// Created by venty on 2025/5/12.
//

#ifndef TENSORSLOW_LOG_CALLBACK_H
#define TENSORSLOW_LOG_CALLBACK_H

#include <fstream>
#include <iostream>
#include <mutex>
#include <string>
#include <utility>
#include "Object/Core/PyNone.h"
#include "Object/Function/PyNativeFunction.h"
#include "Object/Object.h"
#include "Runtime/EventLoop.h"

namespace tensorslow {
class Logger;
class LogStrategy {
 public:
  virtual ~LogStrategy() = default;
  virtual void operator()(const std::string& msg) const = 0;  // 调用操作符重载
};

class DefaultLogStrategy : public LogStrategy {
 public:
  void operator()(const std::string& msg) const override {
    Runtime::EventLoop::Instance().EnqueueTask(
      Object::CreatePyNativeFunction([msg](const Object::PyObjPtr&) {
        std::cout << msg;
        return Object::CreatePyNone();
      })
    );
  }  // 将日志消息添加到事件循环的宏任务队列中
};

class FileLogStrategy : public LogStrategy {
 public:
  explicit FileLogStrategy(const std::string& filename);

  void operator()(const std::string& msg) const override {
    // 如果文件未成功打开，则静默忽略，不做任何输出
    Runtime::EventLoop::Instance().EnqueueTask(
      Object::CreatePyNativeFunction([=](const Object::PyObjPtr&) {
        if (m_stream.is_open()) {
          m_stream << msg;
        }
        return Object::CreatePyNone();
      })
    );
  }

 private:
  mutable std::ofstream m_stream;
};

class ErrorLogStrategy : public LogStrategy {
 public:
  void operator()(const std::string& msg) const override {
    Runtime::EventLoop::Instance().EnqueueTask(
      Object::CreatePyNativeFunction([msg](const Object::PyObjPtr&) {
        std::cerr << msg;
        return Object::CreatePyNone();
      })
    );
  }
};

class ProxyLogStrategy : public LogStrategy {
 public:
  explicit ProxyLogStrategy(Logger* logger) : m_logger(logger) {}

  void operator()(const std::string& msg) const override;

 private:
  Logger* m_logger;
};

}  // namespace tensorslow

#endif  // TENSORSLOW_LOG_CALLBACK_H
