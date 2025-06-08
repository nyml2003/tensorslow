//
// Created by venty on 2025/5/13.
//
#include "LogStrategy.h"
#include "Logger.h"
namespace tensorslow {
void ProxyLogStrategy::operator()(const std::string& msg) const {
  if (m_logger) {
    m_logger->log(msg);
  }
}
}  // namespace tensorslow