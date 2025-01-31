#pragma once

#include <algorithm>
#include <map>
#include <stdexcept>
#include <string>

class IniParser {
public:
  IniParser(const std::string& fileName);

  template <typename T>
  T getValue(const std::string& key) {
    size_t dotPosition = key.find('.');
    if (dotPosition == std::string::npos) {
      throw std::invalid_argument("Invalid key format. Expected 'section.key'.");
    }

    std::string section = key.substr(0, dotPosition);
    std::string variable = key.substr(dotPosition + 1);

    if (m_data.find(section) == m_data.end() || m_data[section].find(variable) == m_data[section].end()) {
      std::string message = "Key '" + key + "' not found.";

      if (m_data.find(section) != m_data.end()) {
        message += " Available variables in section '" + section + "': ";
        for (const auto& var : m_data[section]) {
          message += var.first + ", ";
        }
        message = message.substr(0, message.size() - 2);  // Удаляет запятую и пробел в конце.
      }
      throw std::out_of_range(message);
    }

    std::string value = m_data[section][variable];

    return convert<T>(value);
  }

private:
  std::map<std::string, std::map<std::string, std::string>> m_data;

  std::string trim(const std::string& str);

  // Специализация шаблонов для разных типов
  template <typename T>
  T convert(const std::string& value) {
    static_assert(sizeof(T) == 0, "Unsupported type for conversion.");
  }

  template <>
  int convert<int>(const std::string& value) {
    try {
      return std::stoi(value);
    } catch (const std::invalid_argument&) {
      throw std::runtime_error("Failed to convert value '" + value + "' to int.");
    }
  }

  template <>
  double convert<double>(const std::string& value) {
    try {
      return std::stod(value);
    } catch (const std::invalid_argument&) {
      throw std::runtime_error("Failed to convert value '" + value + "' to double.");
    }
  }

  template <>
  float convert<float>(const std::string& value) {
    try {
      return std::stof(value);
    } catch (const std::invalid_argument&) {
      throw std::runtime_error("Failed to convert value '" + value + "' to float.");
    }
  }

  template <>
  bool convert<bool>(const std::string& value) {
    std::string lower_value = value;
    std::transform(lower_value.begin(), lower_value.end(), lower_value.begin(), ::tolower);

    if (lower_value == "true" || lower_value == "1") {
      return true;
    } else if (lower_value == "false" || lower_value == "0") {
      return false;
    } else {
      throw std::runtime_error("Failed to convert value '" + value + "' to bool.");
    }
  }

  template <>
  std::string convert<std::string>(const std::string& value) {
    return value;  // Для строки просто возвращаем значение
  }
};
