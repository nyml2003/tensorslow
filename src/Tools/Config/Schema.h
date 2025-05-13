//
// Created by venty on 2025/5/12.
//

#ifndef TENSORSLOW_CONFIG_SCHEMA_H
#define TENSORSLOW_CONFIG_SCHEMA_H

#include "OptionConvention.h"
#include "Tools/Logger/ConsoleLogger.h"

#include <iostream>
#include <map>
#include <stdexcept>

namespace tensorslow {

class Schema {
 public:
  static Schema& Instance() {
    static Schema instance;
    return instance;
  }
  static void Accept(std::initializer_list<OptionConvention> params) {
    std::map<std::string, OptionConvention> parameters;
    for (const auto& param : params) {
      parameters.insert_or_assign(param.Name(), param);
    }
    Instance().SetParameters(parameters);
  }

  [[nodiscard]] static const OptionConvention& Find(const std::string& option) {
    const auto& parameters = Instance().Parameters();
    auto parameter = parameters.find(option);
    if (parameter == parameters.end()) {
      PrintUsage();
      throw std::out_of_range("Invalid parameter name: " + option);
    }
    return parameter->second;
  }
  static void PrintUsage() {
    ConsoleLogger::getInstance().log(
      "Invalid parameters, please check the usage.\n"
    );
    ConsoleLogger::getInstance().log("Options:\n");
    for (const auto& [name, param] : Instance().Parameters()) {
      ConsoleLogger::getInstance().log("  --");
      ConsoleLogger::getInstance().log(name);
      ConsoleLogger::getInstance().log("=<value>  (default: ");
      ConsoleLogger::getInstance().log(param.DefaultValue());
      ConsoleLogger::getInstance().log(") tip: ");
      ConsoleLogger::getInstance().log(param.Tip());
      ConsoleLogger::getInstance().log("\n");
    }
    ConsoleLogger::getInstance().log("  --help  Display this help message\n");
    ConsoleLogger::getInstance().log(
      "  --version  Display version information\n"
    );
  }

  static void HandleDefaultParameters(const std::string& option) {
    if (option == "help") {
      PrintUsage();
      exit(0);
    } else if (option == "version") {
      ConsoleLogger::getInstance().log("Version: 1.0.0\n");
      exit(0);
    }
  }

 private:
  std::map<std::string, OptionConvention> m_parameters;  // 参数存储
  [[nodiscard]] const std::map<std::string, OptionConvention>& Parameters(
  ) const {
    return m_parameters;
  }
  void SetParameters(const std::map<std::string, OptionConvention>& parameters
  ) {
    m_parameters = parameters;
  }
};

}  // namespace tensorslow

#endif  // TENSORSLOW_CONFIG_SCHEMA_H
