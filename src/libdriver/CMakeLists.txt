set(target_name driver)

add_library(${target_name} STATIC 
  driver.cpp
)

set_compile_options(${target_name})

target_include_directories(
  ${target_name}

  PUBLIC
  ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(
  driver
  PRIVATE
  indexaccessor
  index
  parser
  picosha2
  CLI11
)
