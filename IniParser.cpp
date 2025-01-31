#include "IniParser.h"

#include <fstream>
#include <stdexcept>

IniParser::IniParser(const std::string& fileName) {
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

    isFileHasContent = true;  // В этом месте понятно, что в файле есть данные

    if (line[0] == '[' && line[line.size() - 1] == ']') {  // Если строка - это объявлении секции
      currentSection = line.substr(1, line.size() - 2);
      currentSection = trim(currentSection);
    } else {  // Строка - это ключ со значением
      size_t equalsPosition = line.find('=');

      if (equalsPosition == std::string::npos) {
        throw std::runtime_error("Syntax error on line " + std::to_string(lineNumber) + ": missing '='.");
      }

      std::string variable = trim(line.substr(0, equalsPosition));
      std::string value = trim(line.substr(equalsPosition + 1));

      if (variable.empty()) {
        throw std::runtime_error("Syntax error in file on line " + std::to_string(lineNumber) +
                                 ": variable name is empty.");
      }

      m_data[currentSection][variable] = value;
    }
  }

  if (!isFileHasContent) {
    throw std::runtime_error("The file is empty or contains only comments and empty lines.");
  }
}

// Private

std::string IniParser::trim(const std::string& str) {
  const char* whiteSpace{" \t\n\r"};
  const char commentChar{';'};

  size_t first = str.find_first_not_of(whiteSpace);
  if (first == std::string::npos) {
    return "";
  }

  // Находим позицию символа комментария
  size_t commentPosition = str.find(commentChar, first);
  size_t last;

  if (commentPosition != std::string::npos) {
    // Если комментарий найден, обрезаем строку до комментария
    last = str.find_last_not_of(whiteSpace, commentPosition - 1);
  } else {
    // Если комментарий не найден, обрезаем пробелы с конца
    last = str.find_last_not_of(whiteSpace);
  }

  return str.substr(first, last - first + 1);
}
