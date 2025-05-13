//
// Created by venty on 2025/5/12.
//

#ifndef TENSORSLOW_CONFIG_CONFIG_H
#define TENSORSLOW_CONFIG_CONFIG_H

#include "Schema.h"

namespace tensorslow {
class Config {
 public:
  static Config& Instance() {
    static Config instance;
    return instance;
  }
  static void Accept(int argc, char** argv) {
    std::map<std::string, std::string> parameters;
    for (int i = 1; i < argc; ++i) {
      std::string token = argv[i];
      if (token.rfind("--", 0) != 0) {
        continue;
      }
      token = token.substr(2);
      Schema::HandleDefaultParameters(token);
      size_t equalPos = token.find('=');
      std::string option = token.substr(0, equalPos);
      std::string value;
      const auto& param = Schema::Find(option);
      if (equalPos != std::string::npos) {
        value = token.substr(equalPos + 1);
      } else {
        value = param.DefaultValue();
      }
      if (!param.validate(value)) {
        throw std::invalid_argument("Invalid value for parameter: " + option);
      }
      parameters.insert_or_assign(option, value);
    }
    Instance().SetParameters(parameters);
  }

  static void Accept(const std::map<std::string, std::string>& parameters) {
    for (const auto& [option, value] : parameters) {
      const auto& param = Schema::Find(option);
      if (!param.validate(value)) {
        throw std::invalid_argument("Invalid value for parameter: " + option);
      }
    }
    Instance().SetParameters(parameters);
  }

  static std::string Get(const std::string& option) {
    const auto& parameters = Config::Instance().Parameters();
    auto it = parameters.find(option);
    if (it == parameters.end()) {
      try {
        return Schema::Find(option).DefaultValue();
      } catch (const std::out_of_range&) {
        throw std::invalid_argument("OptionConvention not found: " + option);
      }
    }
    return it->second;
  }

  static bool Has(const std::string& option) {
    return Instance().Parameters().find(option) !=
           Instance().Parameters().end();
  }

 private:
  std::map<std::string, std::string> m_parameters;  // 参数存储
  [[nodiscard]] const std::map<std::string, std::string>& Parameters() const {
    return m_parameters;
  }
  void SetParameters(const std::map<std::string, std::string>& parameters) {
    m_parameters = parameters;
  }
};
}  // namespace tensorslow
#endif  // TENSORSLOW_CONFIG_CONFIG_H
