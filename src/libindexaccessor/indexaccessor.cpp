#include <libindex/index.h>

#include <libindexaccessor/indexaccessor.h>

#include <libparser/parser.h>

#include <picosha2.h>

#include <algorithm>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

const Parser& TextIndexAccessor::config() const {
  return parser;
}

TermInfos TextIndexAccessor::get_term_infos(const std::string& term) const {
  TermInfos received;

  const std::string term_hash = IndexBuilder::hashTerm(term);

  const std::string full_path = path + "entries/" + term_hash;

  std::ifstream entry_file(full_path);

  if (!entry_file.is_open()) {
    std::cout << "Could not open the file for the term " << term << std::endl;
    return received;
  }

  std::string line;
  while (std::getline(entry_file, line)) {
    std::istringstream entry(line);

    std::string current_term;
    entry >> current_term;

    if (current_term == term) {
      size_t count_entries = 0;
      entry >> count_entries;

      for (size_t i = 0; i < count_entries; ++i) {
        std::string doc_id;
        entry >> doc_id;

        size_t count_pos = 0;
        entry >> count_pos;

        std::vector<int> positions;
        for (size_t j = 0; j < count_pos; ++j) {
          int pos = 0;
          entry >> pos;
          positions.push_back(pos);
        }
        received[term][doc_id] = positions;
      }
      break;
    }
  }
  entry_file.close();

  return received;
}

std::string TextIndexAccessor::load_document(
    const std::string& document_id) const {
  const std::string full_path = path + "docs/" + document_id;

  std::ifstream document_file(full_path);

  if (!document_file.is_open()) {
    std::cout << "Document could not be opened " << document_id << std::endl;
    return "";
  }

  std::string document_content(
      (std::istreambuf_iterator<char>(document_file)),
      std::istreambuf_iterator<char>());

  document_file.close();

  return document_content;
}

size_t TextIndexAccessor::total_docs() const {
  return std::distance(
      std::filesystem::directory_iterator(path + "/docs/"),
      std::filesystem::directory_iterator());
}

std::string TextIndexAccessor::RetPath() const {
  return path;
}

bool compareDocuments(const document& a, const document& b) {
  if (a.score != b.score) {
    return a.score > b.score;
  }
  return std::stoi(a.id) < std::stoi(b.id);
}

Result search(const std::string& query, TextIndexAccessor& index_accessor) {
  TermInfos term_content;
  Result issuing;
  auto ngrams = index_accessor.config().parseText(query);
  for (const auto& ngram : ngrams) {
    // term_content = index_accessor.get_term_infos(ngram.first);

    TermInfos current_info = index_accessor.get_term_infos(ngram.first);
    term_content.insert(current_info.begin(), current_info.end());
  }

  const auto N = static_cast<double>(index_accessor.total_docs());
  if (N == 0) {
    std::cout << "N is " << N << std::endl;
    return issuing;
  }

  for (const auto& entry : std::filesystem::directory_iterator(
           index_accessor.RetPath() + "docs/")) {
    const std::string document_id = entry.path().filename().string();
    double score = 0.0;

    for (const auto& term : term_content) {
      const auto df = static_cast<double>(term.second.size());
      double tf = 0;
      for (const auto& doc : term.second) {
        if (doc.first == document_id) {
          tf = static_cast<double>(doc.second.size());
          break;
        }
      }

      score = score + (tf * (log((N / df))));
    }
    issuing.found.push_back({document_id, score});
  }
  std::sort(issuing.found.begin(), issuing.found.end(), compareDocuments);
  return issuing;
}
