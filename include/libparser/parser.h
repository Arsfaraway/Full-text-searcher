#pragma once

#include <string>

#include <unordered_set>

#include <vector>

class Parser {
 public:
  Parser(
      int min_ngram_length,
      const std::unordered_set<std::string>& stop_words,
      int max_ngram_length);
  std::vector<std::pair<std::string, int>> parseText(
      const std::string& text) const;

 private:
  int min_ngram_length;
  std::unordered_set<std::string> stop_words;
  int max_ngram_length;

  std::vector<std::pair<std::string, int>> generateNGrams(
      const std::vector<std::string>& words) const;
};
