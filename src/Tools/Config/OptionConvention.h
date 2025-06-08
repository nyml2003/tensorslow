#ifndef TENSORSLOW_CONFIG_OPTION_CONVENTION_H
#define TENSORSLOW_CONFIG_OPTION_CONVENTION_H

#include <functional>
#include <string>

namespace tensorslow {
class OptionConvention {
 public:
  explicit OptionConvention(
    std::string name,
    const std::function<bool(const std::string&)>& validator,
    std::string defaultValue = "",
    std::string tip = ""
  )
    : name(std::move(name)),
      validator(validator),
      defaultValue(std::move(defaultValue)),
      tip(std::move(tip)) {}

  [[nodiscard]] std::string Name() const { return name; }
  [[nodiscard]] std::string DefaultValue() const { return defaultValue; }
  [[nodiscard]] bool validate(const std::string& value) const {
    try {
      return validator(value);
    } catch (...) {
      return false;
    }
  }
  [[nodiscard]] std::string Tip() const { return tip; }

 private:
  std::string name;
  std::function<bool(const std::string&)> validator;
  std::string defaultValue;
  std::string tip;
};

}  // namespace tensorslow

#endif  // TENSORSLOW_CONFIG_OPTION_CONVENTION_H
