#pragma once

#include <libparser/parser.h>
#include <CLI/CLI.hpp>
#include <string>

struct Result;

enum class CommandType {
  Index,
  Search
};

struct CommandOptions {
  CommandType type;
  std::string csvPath;
  std::string indexPath;
  std::string query;
  std::string configPath;
};

void configureCLI(CLI::App& app, CommandOptions& options);

void IndexCommand(const CommandOptions& options, const Parser& parser);

Result SearchCommand(const CommandOptions& options, const Parser& parser);

void CommandHelper();
