#include "Tools/Tools.h"
#include <iostream>
#include <stdexcept>
#include <utility>
namespace torchlight {

// Parameter 类实现
Parameter::Parameter(
  std::string name,
  std::function<bool(const std::string&)> validator,
  std::string defaultValue,
  std::string tip
)
  : name(std::move(name)),
    validator(std::move(validator)),
    defaultValue(std::move(defaultValue)),
    tip(std::move(tip)) {}

std::string Parameter::Name() const {
  return name;
}

std::string Parameter::DefaultValue() const {
  return defaultValue;
}

bool Parameter::validate(const std::string& value) const {
  try {
    return validator(value);
  } catch (...) {
    return false;
  }
}

// Schema 类实现
void Schema::Add(const Parameter& param) {
  parameters.insert_or_assign(param.Name(), param);
}

Parameter Schema::Find(const std::string& option) {
  auto parameter = parameters.find(option);
  if (parameter == parameters.end()) {
    PrintUsage();
    throw std::out_of_range("Invalid parameter name: " + option);
  }
  return parameter->second;
}

void Schema::Check(const std::string& option, const std::string& value) const {
  auto parameter = parameters.find(option);
  if (parameter == parameters.end()) {
    PrintUsage();
    throw std::out_of_range("Invalid parameter name: " + option);
  }
  const Parameter& param = parameter->second;
  if (!param.validate(value)) {
    throw std::invalid_argument("Invalid value for parameter: " + option);
  }
}

// ArgsHelper 类实现
ArgsHelper& ArgsHelper::Instance() {
  static ArgsHelper instance;
  return instance;
}

void ArgsHelper::SetSchema(const Schema& schema) {
  ArgsHelper::Instance().schema = schema;
}

void ArgsHelper::Accept(int argc, char** argv) {
  for (int i = 1; i < argc; ++i) {
    std::string token = argv[i];
    if (token.rfind("--", 0) != 0) {
      continue;
    }
    token = token.substr(2);
    HandleDefaultParameters(token);
    size_t equalPos = token.find('=');
    std::string option = token.substr(0, equalPos);
    std::string value;
    if (equalPos != std::string::npos) {
      value = token.substr(equalPos + 1);
    } else {
      value = schema.Find(option).DefaultValue();
    }
    schema.Check(option, value);
    Instance().parameters.insert_or_assign(option, value);
  }
}

void Schema::PrintUsage() const {
  std::cout << "Usage: program [options]" << std::endl;
  std::cout << "Options:" << std::endl;

  // 遍历 Schema 中的参数并打印
  for (const auto& [name, param] : parameters) {
    std::cout << "  --" << name
              << "=<value>  (default: " << param.DefaultValue() << ")"
              << " tip: " << param.Tip() << std::endl;
  }

  // 打印默认参数
  std::cout << "  --help  Display this help message" << std::endl;
  std::cout << "  --version  Display version information" << std::endl;
}

void ArgsHelper::HandleDefaultParameters(const std::string& option) const {
  if (option == "help") {
    schema.PrintUsage();
    exit(0);
  } else if (option == "version") {
    std::cout << "Version: 1.0.0" << std::endl;
    exit(0);
  }
}

std::string ArgsHelper::Get(const std::string& option) {
  auto& instance = ArgsHelper::Instance();
  auto it = instance.parameters.find(option);
  if (it == instance.parameters.end()) {
    try {
      return instance.schema.Find(option).DefaultValue();
    } catch (const std::out_of_range&) {
      throw std::invalid_argument("Parameter not found: " + option);
    }
  }
  return it->second;
}

bool ArgsHelper::Has(const std::string& option) {
  return ArgsHelper::Instance().parameters.find(option) !=
         ArgsHelper::Instance().parameters.end();
}

void ArgsHelper::PrintUsage() {
  ArgsHelper::Instance().schema.PrintUsage();
}

std::vector<fs::path> GetFilesInDirectory(
  const std::string& directoryPath,
  const std::string& extension
) {
  std::vector<fs::path> fileNames;
  if (fs::exists(directoryPath) && fs::is_directory(directoryPath)) {
    for (const auto& entry : fs::directory_iterator(directoryPath)) {
      if (fs::is_regular_file(entry.status()) && entry.path().extension() == extension) {
        fileNames.push_back(entry.path());
      }
    }
  } else {
    std::cerr << "The directory does not exist or is not a directory."
              << std::endl;
  }
  return fileNames;
}

RedirectCout::RedirectCout() : originalBuffer(std::cout.rdbuf()) {}

RedirectCout::~RedirectCout() {
  if (originalBuffer) {
    std::cout.rdbuf(originalBuffer);  // 恢复原始缓冲区
  }
}

void RedirectCout::redirectToFile(const std::string& filename) {
  if (file.is_open()) {
    file.close();  // 如果之前已经打开文件，先关闭
  }
  file.open(filename, std::ios::out);  // 打开文件
  std::cout.rdbuf(file.rdbuf());  // 将 std::cout 的缓冲区替换为文件的缓冲区
}

void RedirectCout::restore() {
  if (file.is_open()) {
    file.close();  // 关闭文件
  }
  std::cout.rdbuf(originalBuffer);  // 恢复 std::cout 的原始缓冲区
}

}  // namespace torchlight