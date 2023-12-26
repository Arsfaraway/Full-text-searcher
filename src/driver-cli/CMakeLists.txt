set(target_name driver-cli)

add_executable(${target_name} main.cpp)

target_link_libraries(
  ${target_name}
  PRIVATE
  CLI11
  driver
  indexaccessor
  index
  parser
  nlohmann_json
)

set_compile_options(${target_name})