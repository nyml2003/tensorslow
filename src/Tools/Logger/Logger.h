//
// Created by venty on 2025/5/12.
//

#ifndef TENSORSLOW_LOGGER_H
#define TENSORSLOW_LOGGER_H

#include "LogStrategy.h"

#include <memory>
#include <mutex>
#include <utility>

namespace tensorslow {
class Logger {
 public:
  virtual ~Logger() = default;

  // 设置自定义回调
  void setCallback(std::unique_ptr<LogStrategy> callback) {
    m_callback = std::move(callback);
  }

  // 每个 Logger 都要实现自己的 log()
  virtual void log(const std::string& msg) = 0;

 protected:
  explicit Logger();
  explicit Logger(std::unique_ptr<LogStrategy> callback)
    : m_callback(std::move(callback)) {}

  std::unique_ptr<LogStrategy> m_callback;
};
}  // namespace tensorslow

#endif  // TENSORSLOW_LOGGER_H
