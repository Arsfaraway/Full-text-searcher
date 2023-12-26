set(target_name parser-cli)

add_executable(${target_name} main.cpp)

target_link_libraries(
  ${target_name}
  PRIVATE
  CLI11
  parser
  nlohmann_json
)

set_compile_options(${target_name})
