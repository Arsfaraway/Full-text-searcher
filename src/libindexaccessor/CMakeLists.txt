set(target_name indexaccessor)

add_library(${target_name} STATIC 
  indexaccessor.cpp
)

set_compile_options(${target_name})

target_include_directories(
  ${target_name}

  PUBLIC
  ${PROJECT_SOURCE_DIR}/include
)

add_executable(
  indexaccessor_test
  indexaccessor_test.cpp
)

target_link_libraries(
  indexaccessor
  PRIVATE
  index
  parser
  picosha2
)

target_link_libraries(

  indexaccessor_test
  PRIVATE
  indexaccessor
  index
  parser
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(indexaccessor_test)