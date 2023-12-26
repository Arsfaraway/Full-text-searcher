#include <libparser/parser.h>

#include <algorithm>

#include <cctype>

#include <sstream>

namespace {
std::string cleanWord(const std::string& word) {
  std::string cleaned;
  std::copy_if(
      word.begin(), word.end(), std::back_inserter(cleaned), [](char c) {
        return std::ispunct(c) == 0;
      });
  std::transform(cleaned.begin(), cleaned.end(), cleaned.begin(), [](char c) {
    return static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
  });
  return cleaned;
}

std::vector<std::string> splitText(const std::string& text) {
  std::istringstream stream(text);
  std::vector<std::string> words;
  std::string word;
  while (stream >> word) {
    words.push_back(cleanWord(word));
  }
  return words;
}
}  // namespace

Parser::Parser(
    int min_ngram_length,
    const std::unordered_set<std::string>& stop_words,
    int max_ngram_length)
    : min_ngram_length(min_ngram_length),
      stop_words(stop_words),
      max_ngram_length(max_ngram_length) {
}

std::vector<std::pair<std::string, int>> Parser::generateNGrams(
    const std::vector<std::string>& words) const {
  int counter = 0;
  bool flag = false;
  std::vector<std::pair<std::string, int>> ngrams;

  for (const auto& word : words) {
    if (stop_words.find(word) == stop_words.end()) {
      for (int n = min_ngram_length; n <= max_ngram_length; ++n) {
        if (static_cast<size_t>(n) <= word.length()) {
          ngrams.emplace_back(word.substr(0, n), static_cast<int>(counter));
          flag = true;
        }
      }
      if (flag) {
        counter++;
        flag = false;
      }
    }
  }
  return ngrams;
}

std::vector<std::pair<std::string, int>> Parser::parseText(
    const std::string& text) const {
  auto words = splitText(text);
  return generateNGrams(words);
}
