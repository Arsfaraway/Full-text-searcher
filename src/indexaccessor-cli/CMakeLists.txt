set(target_name indexaccessor-cli)

add_executable(${target_name} main.cpp)

target_link_libraries(
  ${target_name}
  PRIVATE
  CLI11
  indexaccessor
  index
  parser
)

set_compile_options(${target_name})