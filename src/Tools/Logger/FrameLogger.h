#ifndef TENSORSLOW_FRAME_LOGGER_H
#define TENSORSLOW_FRAME_LOGGER_H

#include "Logger.h"

namespace tensorslow {

class FrameLogger : public Logger {
 public:
  static FrameLogger& getInstance() {
    static FrameLogger instance;
    return instance;
  }

  void log(const std::string& msg) override {
    if (m_callback) {
      (*m_callback)(msg);
    }
  }

 private:
  FrameLogger() = default;
};

}  // namespace tensorslow

#endif  // TENSORSLOW_FRAME_LOGGER_H