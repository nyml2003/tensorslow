//
// Created by venty on 2025/5/13.
//
#include "Logger.h"
#include "ConsoleLogger.h"
#include "LogStrategy.h"

namespace tensorslow {

Logger::Logger()
  : m_callback(std::make_shared<ProxyLogStrategy>(&ConsoleLogger::getInstance())
    ) {}

}  // namespace tensorslow