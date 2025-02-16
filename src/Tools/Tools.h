#ifndef TORCHLIGHT_BACKEND_TOOLS_H
#define TORCHLIGHT_BACKEND_TOOLS_H

#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <optional>
#include <ostream>
#include <string>
#include <variant>

namespace fs = std::filesystem;

namespace torchlight {

class Parameter {
 public:
  Parameter(
    std::string name,
    std::function<bool(const std::string&)> validator,
    std::string defaultValue = "true"
  );

  [[nodiscard]] std::string Name() const;
  [[nodiscard]] std::string DefaultValue() const;
  [[nodiscard]] bool validate(const std::string& value) const;

 private:
  std::string name;
  std::function<bool(const std::string&)> validator;
  std::string defaultValue;
};

// 参数 Schema 类
class Schema {
 public:
  void Add(const Parameter& param);
  void Check(std::string option, std::string value) const;
  Parameter Find(std::string option);

 private:
  std::map<std::string, Parameter> parameters;  // 参数存储
};

// 单例类
class ArgsHelper {
 public:
  static ArgsHelper& Instance();
  static void SetSchema(const Schema& schema);
  void Accept(int argc, char** argv);

  [[nodiscard]] std::string Get(const std::string& option) const;
  [[nodiscard]] bool Has(const std::string& option) const;

 private:
  ArgsHelper() = default;                         // 私有构造函数
  Schema schema;                                  // 参数 Schema
  std::map<std::string, std::string> parameters;  // 参数存储
};

std::vector<fs::path> GetFilesInDirectory(
  const std::string& directoryPath,
  const std::string& extension
);

class RedirectCout {
 public:
  RedirectCout();
  ~RedirectCout();

  void redirectToFile(const std::string& filename);
  void restore();

 private:
  std::streambuf* originalBuffer;  // 保存 std::cout 的原始缓冲区
  std::ofstream file;              // 用于文件输出的文件流
};

}  // namespace torchlight

#endif  // TORCHLIGHT_TOOLS_H