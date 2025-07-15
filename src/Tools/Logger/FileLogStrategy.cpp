//
// Created by venty on 2025/5/12.
//
#include "ErrorLogger.h"
#include "LogStrategy.h"

namespace tensorslow {

FileLogStrategy::FileLogStrategy(const std::string& filename)
  : m_stream(
      filename,
      static_cast<std::ios::openmode>(
        static_cast<unsigned int>(std::ios::out) |
        static_cast<unsigned int>(std::ios::trunc)
      )
    ) {
  if (!m_stream.is_open()) {
    // 文件打开失败时，使用 ErrorLogger 记录错误
    ErrorLogger::getInstance().log("Failed to open log file: " + filename);
  }
}

}  // namespace tensorslow