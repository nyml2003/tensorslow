//
// Created by venty on 2025/5/12.
//

#ifndef TENSORSLOW_FILE_LOGGER_H
#define TENSORSLOW_FILE_LOGGER_H

#include "ConsoleLogger.h"
#include "Logger.h"

#include <fstream>
#include <memory>
#include <mutex>
#include <string>

namespace tensorslow {

class FileLogger : public Logger {
 public:
  static FileLogger& getInstance() {
    static FileLogger instance;
    return instance;
  }

  // 打开日志文件
  bool openFile(const std::string& filename) {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_fileStream.is_open()) {
      return false;  // 文件已打开
    }

    m_fileStream.open(filename, std::ios::out | std::ios::trunc);
    if (!m_fileStream.is_open()) {
      return false;  // 打开失败
    }

    // 设置文件写入回调
    setCallback(std::make_shared<FileLogStrategy>(m_fileStream));
    return true;
  }

  // 关闭文件并恢复默认回调
  void closeFile() {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_fileStream.is_open()) {
      m_fileStream.close();
    }
    setCallback(std::make_shared<DefaultLogStrategy>());  // 恢复控制台输出
  }

  // 写入日志（带自动初始化判断）
  void log(const std::string& msg) override {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_callback) {
      (*m_callback)(msg);
    }
  }

 private:
  FileLogger() = default;

  ~FileLogger() override {
    if (m_fileStream.is_open()) {
      m_fileStream.close();
    }
  }

  FileLogger(const FileLogger&) = delete;
  FileLogger& operator=(const FileLogger&) = delete;

  std::ofstream m_fileStream;
};

}  // namespace tensorslow

#endif  // TENSORSLOW_FILE_LOGGER_H