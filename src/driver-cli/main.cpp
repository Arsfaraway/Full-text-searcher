#include <iostream>

#include <unordered_set>

#include <CLI/CLI.hpp>

#include <libparser/parser.h>

#include <libindex/index.h>

#include <libindexaccessor/indexaccessor.h>

#include <libdriver/driver.h>

#include <nlohmann/json.hpp>

#include <fstream>

#include <string>

using json = nlohmann::json;

void printResult(const TextIndexAccessor& text, const Result& result) {
  bool foundResult = false;

  for (const auto& doc : result.found) {
    if (doc.score > 0) {
      std::cout << "Document ID: " << doc.id << ", Score: " << doc.score
                << std::endl;
      std::cout << "Content: " << text.load_document(doc.id) << std::endl;
      foundResult = true;
    } else {
      break;
    }
  }

  if (!foundResult) {
    std::cout << "Nothing was found for your query!" << std::endl;
  }
}

std::unordered_set<std::string> loadStopWords(const json& j) {
  std::unordered_set<std::string> stop_words;
  for (const auto& word : j) {
    stop_words.insert(word);
  }
  return stop_words;
}

Parser loadParserConfig(const std::string& configPath) {
  std::ifstream configFile(configPath);
  if (!configFile.is_open()) {
    std::cerr << "The configuration file could not be opened." << std::endl;
    std::cerr << "The default configuration was used." << std::endl
              << std::endl;
    return Parser(5, {"the", "and", "is"}, 5);
  }

  json config;
  configFile >> config;

  const int minNgramLength = config["parser"]["ngram_min_length"];
  const int maxNgramLength = config["parser"]["ngram_max_length"];
  auto stopWords = loadStopWords(config["parser"]["stop_words"]);

  return {minNgramLength, stopWords, maxNgramLength};
}

int main(int argc, char** argv) {
  CLI::App app{"Full-Text Search Application"};
  CommandOptions options;

  configureCLI(app, options);
  CLI11_PARSE(app, argc, argv);

  if (app.got_subcommand("index") || app.got_subcommand("search")) {
    const Parser parser = loadParserConfig(options.configPath);

    if (options.type == CommandType::Index) {
      std::cerr << "You have entered the 'Index' subcommand." << std::endl
                << std::endl;
      IndexCommand(options, parser);
    } else if (options.type == CommandType::Search) {
      std::cerr << "You have entered the 'Search' subcommand." << std::endl
                << std::endl;
      auto res = SearchCommand(options, parser);
      if (!res.found.empty()) {
        const TextIndexAccessor text("../../../src/index - files/", parser);
        printResult(text, res);
      } else {
        CommandHelper();
      }
    }
  } else {
    std::cerr << "No subcommand was provided." << std::endl;
    CommandHelper();
    return 1;
  }

  return 0;
}