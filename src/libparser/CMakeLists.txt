set(target_name parser)

add_library(${target_name} STATIC 
  parser.cpp
)

set_compile_options(${target_name})

target_include_directories(
  ${target_name}

  PUBLIC
  ${PROJECT_SOURCE_DIR}/include
)

add_executable(
  parser_test
  parser_test.cpp
)

target_link_libraries(
  parser_test
  PRIVATE
  parser
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(parser_test)
