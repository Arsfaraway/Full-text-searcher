set(target_name index)

add_library(${target_name} STATIC 
  index.cpp
)

set_compile_options(${target_name})

target_include_directories(
  ${target_name}

  PUBLIC
  ${PROJECT_SOURCE_DIR}/include
)

add_executable(
  index_test
  index_test.cpp
)

target_link_libraries(
  index
  PRIVATE
  parser
  picosha2
)

target_link_libraries(

  index_test
  PRIVATE
  index
  parser
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(index_test)