#pragma once

#include <libindex/index.h>
#include <libparser/parser.h>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

struct document {
  std::string id;
  double score;
};

struct Result {
  std::vector<document> found;
};

using TermInfos = std::unordered_map<
    std::string,
    std::unordered_map<std::string, std::vector<int>>>;

class IndexAccessor {
 public:
  virtual ~IndexAccessor() = default;
  virtual const Parser& config() const = 0;
  virtual TermInfos get_term_infos(const std::string& term) const = 0;
  virtual std::string load_document(const std::string& document_id) const = 0;
  virtual size_t total_docs() const = 0;
};

class TextIndexAccessor : public IndexAccessor {
 private:
  std::string path;
  const Parser& parser;

 public:
  TextIndexAccessor(const std::string& path, const Parser& parser)
      : path(path), parser(parser) {
  }
  const Parser& config() const override;
  TermInfos get_term_infos(const std::string& term) const override;
  std::string load_document(const std::string& document_id) const override;
  size_t total_docs() const override;
  std::string RetPath() const;
};

bool compareDocuments(const document& a, const document& b);
Result search(const std::string& query, TextIndexAccessor& index_accessor);
