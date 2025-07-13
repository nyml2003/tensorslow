//
// Created by venty on 2025/5/12.
//

#ifndef TENSORSLOW_VERBOSE_LOGGER_H
#define TENSORSLOW_VERBOSE_LOGGER_H

#include "LogStrategy.h"
#include "Logger.h"

namespace tensorslow {

class VerboseLogger : public Logger {
 public:
  static VerboseLogger& getInstance() {
    static VerboseLogger instance;
    return instance;
  }

  void log(const std::string& msg) override {
    if (m_callback) {
      for (int i = 0; i < indent; i++) {
        (*m_callback)("  ");
      }
      (*m_callback)(msg);
    }
  }

  static void IncreaseIndent() { getInstance().indent++; }
  static void DecreaseIndent() { getInstance().indent--; }

 private:
  VerboseLogger() = default;
  int indent = 0;
};

}  // namespace tensorslow

#endif  // TENSORSLOW_VERBOSE_LOGGER_H
