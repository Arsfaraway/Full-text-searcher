#include <CLI/CLI.hpp>

#include <iostream>

#include <libparser/parser.h>

#include <fstream>

#include <nlohmann/json.hpp>

#include <string>

#include <unordered_set>

using json = nlohmann::json;

std::unordered_set<std::string> loadStopWords(const json& j) {
  std::unordered_set<std::string> stop_words;
  for (const auto& word : j) {
    stop_words.insert(word);
  }
  return stop_words;
}

int main(int argc, char** argv) {
  CLI::App app{"Text parser"};

  std::string configPath = "config.json";
  app.add_option("--config", configPath, "Path to the config file")
      ->check(CLI::ExistingFile);

  CLI11_PARSE(app, argc, argv);

  std::ifstream configFile(configPath);
  if (!configFile.is_open()) {
    std::cerr << "Could not open config file: " << configPath << std::endl;
    return 1;
  }

  json config;
  configFile >> config;

  const int min_ngram_length = config["parser"]["ngram_min_length"];
  const int max_ngram_length = config["parser"]["ngram_max_length"];
  auto stop_words = loadStopWords(config["parser"]["stop_words"]);

  const Parser parser(min_ngram_length, stop_words, max_ngram_length);

  const std::string text = "vvv vvv hfhf hfhff";

  auto ngrams = parser.parseText(text);
  for (const auto& ngram : ngrams) {
    std::cout << ngram.first << " " << ngram.second << std::endl;
  }

  return 0;
}
