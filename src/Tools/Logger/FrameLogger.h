#ifndef TENSORSLOW_FRAME_LOGGER_H
#define TENSORSLOW_FRAME_LOGGER_H

#include "ConsoleLogger.h"

namespace tensorslow {

class FrameLogger : public Logger {
 public:
  static FrameLogger& getInstance() {
    static FrameLogger instance;
    return instance;
  }

  void log(const std::string& msg) override {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_callback) {
      (*m_callback)(msg);
    }
  }
  FrameLogger(const FrameLogger&) = delete;
  FrameLogger& operator=(const FrameLogger&) = delete;

 private:
  FrameLogger() = default;
};

}  // namespace tensorslow

#endif  // TENSORSLOW_FRAME_LOGGER_H