#include <iostream>
#include <ostream>

#include "IniParser.h"

int main() {
  try {
    IniParser parser("example.ini");
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
  return 0;
}
