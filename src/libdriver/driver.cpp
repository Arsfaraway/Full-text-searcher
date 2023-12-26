#include <libindex/index.h>

#include <libdriver/driver.h>

#include <libindexaccessor/indexaccessor.h>

#include <libparser/parser.h>

#include <picosha2.h>

#include <CLI/CLI.hpp>

#include <algorithm>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

void CommandHelper() {
  std::cerr << std::endl;

  std::cerr << "Use the following commands by default:" << std::endl;
  std::cerr << "driver-cli.exe index" << std::endl;
  std::cerr << "driver-cli.exe search" << std::endl;
  std::cerr << std::endl;
  std::cerr << "Or use the following full commands as an example:" << std::endl;
  std::cerr
      << "driver-cli.exe index --csv ../../../books.csv --index ../../../src/ "
         "--config ../../../src/driver-cli/config.json"
      << std::endl;
  std::cerr << "driver-cli.exe search --index ../../../src/ --config "
               "../../../src/driver-cli/config.json --query harry"
            << std::endl;
  std::cerr << std::endl;
}

void configureCLI(CLI::App& app, CommandOptions& options) {
  auto* index = app.add_subcommand("index", "Build an index");
  index->add_option("--csv", options.csvPath, "Path to the CSV file")
      ->default_val("../../../books.csv");

  index->add_option("--index", options.indexPath, "Path to the index directory")
      ->default_val("../../../src/");

  index
      ->add_option(
          "--config", options.configPath, "Path to the configuration file")
      ->default_val("../../../src/driver-cli/config.json");

  index->callback([&options]() { options.type = CommandType::Index; });

  auto* search = app.add_subcommand("search", "Search the index");
  search
      ->add_option("--index", options.indexPath, "Path to the index directory")
      ->default_val("../../../src/");

  search->add_option("--query", options.query, "Query text for search");

  search
      ->add_option(
          "--config", options.configPath, "Path to the configuration file")
      ->default_val("../../../src/driver-cli/config.json");

  search->callback([&options]() { options.type = CommandType::Search; });
}

void IndexCommand(const CommandOptions& options, const Parser& parser) {
  IndexBuilder indexBuilder(parser);

  std::ifstream csvFile(options.csvPath);
  if (!csvFile.is_open()) {
    std::cerr << "Error: The CSV file could not be opened." << std::endl;
    std::cerr << "Please specify the correct path to the CSV file."
              << std::endl;
    CommandHelper();
    return;
  }

  if (options.indexPath.empty()) {
    std::cerr << "Error: Use the correct indexPath!" << std::endl;
    CommandHelper();
    return;
  }

  std::string line;
  bool flag_line = false;
  while (std::getline(csvFile, line)) {
    if (flag_line) {
      std::istringstream iss(line);
      std::string id;
      std::string title;

      std::getline(iss, id, ',');
      std::getline(iss, title, ',');
      indexBuilder.addDocument(id, title);
    }
    flag_line = true;
  }

  csvFile.close();

  const Index index = indexBuilder.getIndex();
  indexBuilder.writeToDirectory(options.indexPath);
}

Result SearchCommand(const CommandOptions& options, const Parser& parser) {
  std::string searchQuery = options.query;
  if (options.indexPath.empty()) {
    std::cerr << "Error: Use the correct indexPath!" << std::endl;
    CommandHelper();
    return Result{};
  }

  if (options.query.empty()) {
    while (searchQuery.empty()) {
      std::cout << "Please enter the search query: ";
      std::cin >> searchQuery;
    }
  }

  TextIndexAccessor text(options.indexPath + "/index - files/", parser);
  Result result = search(searchQuery, text);
  return result;
}
