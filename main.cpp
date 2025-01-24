#include <iostream>
#include <ostream>

#include "ini_parser.h"

int main() {
  try {
    ini_parser parser("example.ini");
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
  return 0;
}
