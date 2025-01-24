#include "IniParser.h"

#include <fstream>
#include <sstream>

IniParser::IniParser(const std::string& fileName) {
  parse(fileName);
}

template <typename T>
T IniParser::getValue(const std::string& key) {
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
      message = message.substr(0, message.size() - 2);  // Remove trailing comma and space
    }
    throw std::out_of_range(message);
  }

  std::string value = m_data[section][variable];

  return convert<T>(value);
}

// Private

// Явное инстанцирование шаблонной функции для нужных типов
template std::string IniParser::getValue<std::string>(const std::string& key);
// template int IniParser::getValue<int>(const std::string& key);
// template double IniParser::getValue<double>(const std::string& key);

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

    if (line[0] == '[' && line[line.size() - 1] == ']') {
      currentSection = line.substr(1, line.size() - 2);
      currentSection = trim(currentSection);
    } else {
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

std::string IniParser::trim(const std::string& str) {
  const char* whiteSpace = " \t\n\r";
  const char commentChar = ';';

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

template <typename T>
T IniParser::convert(const std::string& value) {
  std::istringstream iss(value);

  T result;
  if (!(iss >> result)) {
    throw std::runtime_error("Conversion error: cannot convert '" + value + "' to requested type.");
  }
  return result;
}

template <>
std::string IniParser::convert<std::string>(const std::string& value) {
  return value;
}
