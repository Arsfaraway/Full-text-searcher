cmake_minimum_required(VERSION 3.22)

include(FetchContent)

FetchContent_Declare(
  CLI11
  GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
  GIT_TAG v2.3.2
  GIT_SHALLOW TRUE
  PREFIX ${CMAKE_CURRENT_BINARY_DIR}

)
FetchContent_MakeAvailable(CLI11)
