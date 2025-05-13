//
// Created by venty on 2025/5/12.
//

#ifndef TENSORSLOW_LOGGER_H
#define TENSORSLOW_LOGGER_H

#include "LogStrategy.h"

#include <mutex>
#include <utility>

namespace tensorslow {
class Logger {
 public:
  virtual ~Logger() = default;

  // 设置自定义回调
  void setCallback(std::shared_ptr<LogStrategy> callback) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_callback = std::move(callback);
  }

  // 每个 Logger 都要实现自己的 log()
  virtual void log(const std::string& msg) = 0;

 protected:
  explicit Logger();
  explicit Logger(std::shared_ptr<LogStrategy> callback)
    : m_callback(std::move(callback)) {}

  std::mutex m_mutex;
  std::shared_ptr<LogStrategy> m_callback;
};
}  // namespace tensorslow

#endif  // TENSORSLOW_LOGGER_H
