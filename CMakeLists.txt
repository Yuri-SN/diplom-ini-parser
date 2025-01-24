cmake_minimum_required(VERSION 3.16)

project(diplom-ini-parser LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(diplom-ini-parser
  main.cpp
)

include(GNUInstallDirs)

install(TARGETS diplom-ini-parser
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
