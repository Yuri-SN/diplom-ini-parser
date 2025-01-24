#pragma once

#include <map>
#include <string>

class IniParser {
public:
  IniParser(const std::string& fileName);

private:
  void parse(const std::string& fileName);
  std::string trim(const std::string& str);

  std::map<std::string, std::map<std::string, std::string>> m_data;
};
