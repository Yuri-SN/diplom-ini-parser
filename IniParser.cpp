#include "IniParser.h"

#include <fstream>

IniParser::IniParser(const std::string& fileName) {
  parse(fileName);
}

// Private

void IniParser::parse(const std::string& fileName) {
  std::ifstream file(fileName);
  if (!file.is_open()) {
    throw std::runtime_error("Could not open file: " + fileName);
  }

  std::string line;
  std::string currentSection;
  int lineNumber{0};
  bool hasContent{false};
}
