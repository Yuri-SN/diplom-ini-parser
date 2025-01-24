cmake_minimum_required(VERSION 3.16)

project(diplom-ini-parser LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(diplom-ini-parser
  main.cpp
  ini_parser.h
  ini_parser.cpp
)

include(GNUInstallDirs)

install(TARGETS diplom-ini-parser
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

set(SOURCE_FILE "${CMAKE_CURRENT_SOURCE_DIR}/example.ini")
set(DESTINATION_FILE "${CMAKE_CURRENT_BINARY_DIR}/example.ini")

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
  "${SOURCE_FILE}" "${DESTINATION_FILE}"
  COMMENT "Copying example.ini to the build directory if it does not exist"
)
