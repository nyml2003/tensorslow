#ifndef TORCHLIGHT_BACKEND_TOOLS_H
#define TORCHLIGHT_BACKEND_TOOLS_H

#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <string>

namespace fs = std::filesystem;

namespace torchlight {

class Parameter {
 public:
  Parameter(
    std::string name,
    std::function<bool(const std::string&)> validator,
    std::string defaultValue = "true",
    std::string tip = ""
  );

  [[nodiscard]] std::string Name() const;
  [[nodiscard]] std::string DefaultValue() const;
  [[nodiscard]] bool validate(const std::string& value) const;
  [[nodiscard]] std::string Tip() const { return tip; }

 private:
  std::string name;
  std::function<bool(const std::string&)> validator;
  std::string defaultValue;
  std::string tip;
};

// 参数 Schema 类
class Schema {
 public:
  void Add(const Parameter& param);
  void Check(const std::string& option, const std::string& value) const;
  Parameter Find(const std::string& option);
  void PrintUsage() const;  // 打印使用说明
 private:
  std::map<std::string, Parameter> parameters;  // 参数存储
};

class ArgsHelper {
 public:
  static ArgsHelper& Instance();
  static void SetSchema(const Schema& schema);
  void Accept(int argc, char** argv);

  [[nodiscard]] static std::string Get(const std::string& option);
  [[nodiscard]] static bool Has(const std::string& option);
  static void PrintUsage();

 private:
  ArgsHelper() = default;                         // 私有构造函数
  Schema schema;                                  // 参数 Schema
  std::map<std::string, std::string> parameters;  // 参数存储

  void HandleDefaultParameters(const std::string& option
  ) const;  // 处理默认参数
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