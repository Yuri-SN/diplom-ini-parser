#pragma once

#include <map>
#include <string>

class IniParser {
public:
  IniParser(const std::string& fileName);

  template <typename T>
  T getValue(const std::string& key);

private:
  void parse(const std::string& fileName);

  std::string trim(const std::string& str);

  template <typename T>
  T convert(const std::string& value);

  template <>
  std::string convert<std::string>(const std::string& value);

  std::map<std::string, std::map<std::string, std::string>> m_data;
};
