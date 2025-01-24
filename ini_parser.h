#pragma once

#include <map>
#include <string>

class ini_parser {
public:
  ini_parser(const std::string& filename);

private:
  std::map<std::string, std::map<std::string, std::string>> m_data;
};
