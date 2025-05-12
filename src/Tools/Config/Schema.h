//
// Created by venty on 2025/5/12.
//

#ifndef TENSORSLOW_CONFIG_SCHEMA_H
#define TENSORSLOW_CONFIG_SCHEMA_H

#include "OptionConvention.h"

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
    std::cout << "Usage: program [options]" << std::endl;
    std::cout << "Options:" << std::endl;

    // 遍历 Schema 中的参数并打印
    for (const auto& [name, param] : Instance().Parameters()) {
      std::cout << "  --" << name
                << "=<value>  (default: " << param.DefaultValue() << ")"
                << " tip: " << param.Tip() << std::endl;
    }

    // 打印默认参数
    std::cout << "  --help  Display this help message" << std::endl;
    std::cout << "  --version  Display version information" << std::endl;
  }

  static void HandleDefaultParameters(const std::string& option) {
    if (option == "help") {
      PrintUsage();
      exit(0);
    } else if (option == "version") {
      std::cout << "Version: 1.0.0" << std::endl;
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
