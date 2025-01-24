#include <iostream>
#include <ostream>

#include "IniParser.h"

int main() {
  try {
    IniParser parser("example.ini");

    // auto value1 = parser.getValue<double>("Section1.var1");
    // std::cout << "Section1.var1 = " << value1 << std::endl;

    auto value2 = parser.getValue<std::string>("Section1.var2");
    std::cout << "Section1.var2 = " << value2 << std::endl;

    // auto value3 = parser.getValue<int>("Section2.var1");
    // std::cout << "Section2.var1 = " << value3 << std::endl;

    auto value4 = parser.getValue<std::string>("Section2.var2");
    std::cout << "Section2.var2 = " << value4 << std::endl;

    // auto value5 = parser.getValue<std::string>("Section4.Mode");
    // std::cout << "Section4.Mode = '" << value5 << "'" << std::endl;

    // Exception !!!
    // auto value6 = parser.getValue<int>("Section3.var1");
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }

  return 0;
}
