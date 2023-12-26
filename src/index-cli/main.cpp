#include <iostream>

#include <unordered_set>

#include <CLI/CLI.hpp>

#include <libparser/parser.h>

#include <libindex/index.h>

#include <fstream>

#include <string>

int main() {
  Parser parser(6, {"the", "and", "is"}, 8);
  IndexBuilder indexBuilder(parser);

  indexBuilder.addDocument("199903", "borrowed");
  indexBuilder.addDocument("200305", "trivia");

  const Index index = indexBuilder.getIndex();

  indexBuilder.writeToDirectory("../../../src/");

  return 0;
}