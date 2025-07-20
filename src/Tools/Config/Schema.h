//
// Created by venty on 2025/5/12.
//

#ifndef TENSORSLOW_CONFIG_SCHEMA_H
#define TENSORSLOW_CONFIG_SCHEMA_H

#include "OptionConvention.h"
#include "Tools/Terminal/Terminal.h"

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
      std::cout << "Invalid parameter name: " << option;
      throw std::invalid_argument("Invalid parameter name");
    }
    return parameter->second;
  }
  static void PrintUsage() {
    ConsoleTerminal::get_instance().info(
      "Invalid parameters, please check the usage."
    );
    ConsoleTerminal::get_instance().info("Options:");
    for (const auto& [name, param] : Instance().Parameters()) {
      ConsoleTerminal::get_instance().info("  --");
      ConsoleTerminal::get_instance().info(name);
      ConsoleTerminal::get_instance().info("=<value>  (default: ");
      ConsoleTerminal::get_instance().info(param.DefaultValue());
      ConsoleTerminal::get_instance().info(") tip: ");
      ConsoleTerminal::get_instance().info(param.Tip());
    }
    ConsoleTerminal::get_instance().info("  --help  Display this help message");
    ConsoleTerminal::get_instance().info(
      "  --version  Display version information"
    );
  }

  static void HandleDefaultParameters(const std::string& option) {
    if (option == "help") {
      PrintUsage();
      exit(0);
    } else if (option == "version") {
      ConsoleTerminal::get_instance().info("Version: 1.0.0");
      exit(0);
    }
  }

 private:
  std::map<std::string, OptionConvention> m_parameters;  // 参数存储
  [[nodiscard]] const std::map<std::string, OptionConvention>& Parameters(
  ) const {
    return m_parameters;
  }
  void SetParameters(
    const std::map<std::string, OptionConvention>& parameters
  ) {
    m_parameters = parameters;
  }
};

}  // namespace tensorslow

#endif  // TENSORSLOW_CONFIG_SCHEMA_H
