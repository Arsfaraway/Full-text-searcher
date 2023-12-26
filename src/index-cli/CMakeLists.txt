set(target_name index-cli)

add_executable(${target_name} main.cpp)

target_link_libraries(
  ${target_name}
  PRIVATE
  CLI11
  index
  parser
)

set_compile_options(${target_name})