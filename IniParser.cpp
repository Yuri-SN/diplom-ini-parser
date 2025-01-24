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
  bool isFileHasContent{false};

  while (std::getline(file, line)) {
    ++lineNumber;
    line = trim(line);

    if (line.empty() || line[0] == ';') {
      continue;  // Пропускаем пустые строки и комментарии
    }

    isFileHasContent = true;  // Если дошли сюда, значит, в файле есть содержимое
  }

  if (!isFileHasContent) {
    throw std::runtime_error("The file is empty or contains only comments and empty lines.");
  }
}

std::string IniParser::trim(const std::string& str) {
  const char* whiteSpace = " \t\n\r";
  size_t first = str.find_first_not_of(whiteSpace);
  if (first == std::string::npos) {
    return "";
  }
  size_t last = str.find_last_not_of(whiteSpace);

  return str.substr(first, last - first + 1);
}
