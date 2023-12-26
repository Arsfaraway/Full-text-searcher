#pragma once

#include <libparser/parser.h>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

struct Index {
  std::vector<std::pair<std::string, std::string>> docs;
  std::unordered_map<
      std::string,
      std::unordered_map<std::string, std::vector<int>>>
      entries;
};

class IndexBuilder {
 private:
  Index index;
  const Parser& parser;

 public:
  IndexBuilder(Parser& parser);
  IndexBuilder(const Parser& parser) : parser(parser){};
  void addDocument(const std::string& document_id, const std::string& text);
  Index getIndex() const;
  void writeToDirectory(const std::string& directoryPath) const;
  static std::string hashTerm(const std::string& term);
};