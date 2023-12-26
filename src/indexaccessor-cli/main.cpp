#include <iostream>

#include <unordered_set>

#include <CLI/CLI.hpp>

#include <libparser/parser.h>

#include <libindex/index.h>

#include <libindexaccessor/indexaccessor.h>

#include <fstream>

#include <string>

void printTermInfos(const TermInfos& termInfos) {
  for (const auto& termEntry : termInfos) {
    const std::string& term = termEntry.first;
    const auto& docMap = termEntry.second;

    std::cout << "Term: " << term << std::endl;

    for (const auto& docEntry : docMap) {
      const std::string& docId = docEntry.first;
      const std::vector<int>& positions = docEntry.second;

      std::cout << "  DocID: " << docId << ", Positions: ";
      for (const int pos : positions) {
        std::cout << pos << " ";
      }
      std::cout << std::endl;
    }
  }
}

void printResult(const Result& result) {
  for (const auto& doc : result.found) {
    std::cout << "Document ID: " << doc.id << ", Score: " << doc.score
              << std::endl;
  }
}

int main() {
  const Parser parser(5, {"the", "and", "is"}, 5);
  IndexBuilder indexBuilder(parser);

  indexBuilder.addDocument("103", "Story Earth");
  indexBuilder.addDocument("101", "Hello Hello World");
  indexBuilder.addDocument("102", "Story Earth");

  const Index index = indexBuilder.getIndex();

  indexBuilder.writeToDirectory("../../../src/");

  TextIndexAccessor text("../../../src/index - files/", parser);

  const size_t count = text.total_docs();

  std::cout << "Number of documents in docs: " << count << std::endl;

  const std::string content_doc = text.load_document("103");

  std::cout << "The contents of document 103 " << content_doc << std::endl;

  const std::string e_term = "story";

  const TermInfos term_conten = text.get_term_infos(e_term);

  printTermInfos(term_conten);

  const std::string searching = "Hello World";

  const Result last = search(searching, text);

  printResult(last);

  return 0;
}