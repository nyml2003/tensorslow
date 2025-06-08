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

namespace tensorslow {
class Logger;
class LogStrategy {
 public:
  virtual ~LogStrategy() = default;
  virtual void operator()(const std::string& msg) const = 0;  // 调用操作符重载
};

class DefaultLogStrategy : public LogStrategy {
 public:
  void operator()(const std::string& msg) const override { std::cout << msg; }
};

class FileLogStrategy : public LogStrategy {
 public:
  explicit FileLogStrategy(const std::string& filename);

  void operator()(const std::string& msg) const override {
    if (m_stream.is_open()) {
      m_stream << msg;
    }
    // 如果文件未成功打开，则静默忽略，不做任何输出
  }

 private:
  mutable std::ofstream m_stream;
};

class ErrorLogStrategy : public LogStrategy {
 public:
  void operator()(const std::string& msg) const override { std::cerr << msg; }
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
