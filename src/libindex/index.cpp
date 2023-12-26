#include <libindex/index.h>

#include <libparser/parser.h>

#include <picosha2.h>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

IndexBuilder::IndexBuilder(Parser& parser) : parser(parser) {
}

void IndexBuilder::addDocument(
    const std::string& document_id,
    const std::string& text) {
  index.docs.emplace_back(document_id, text);

  const auto ngrams = parser.parseText(text);

  for (const auto& ngram : ngrams) {
    index.entries[ngram.first][document_id].push_back(ngram.second);
  }
}

Index IndexBuilder::getIndex() const {
  return index;
}

std::string IndexBuilder::hashTerm(const std::string& term) {
  std::string hash_hex_str;
  picosha2::hash256_hex_string(term, hash_hex_str);
  return hash_hex_str.substr(0, 6);
}

void IndexBuilder::writeToDirectory(const std::string& directoryPath) const {
  const std::string docsDirectory = directoryPath + "/index - files/docs";
  std::filesystem::create_directories(docsDirectory);

  const std::string entriesDirectory = directoryPath + "/index - files/entries";
  std::filesystem::create_directories(entriesDirectory);

  std::unordered_set<std::string> writtenFiles;

  for (const auto& doc : index.docs) {
    std::ofstream docFile(docsDirectory + "/" + doc.first);
    docFile << doc.second << " ";
    docFile << "\n";
    docFile.close();
  }

  for (const auto& entry : index.entries) {
    const std::string hash = hashTerm(entry.first);

    std::string filePath = entriesDirectory;
    filePath.append("/").append(hash);
    std::ofstream docFile(filePath, std::ios::app);

    docFile << entry.first << " ";
    docFile << entry.second.size() << " ";

    for (const auto& doc : entry.second) {
      docFile << doc.first << " ";
      docFile << doc.second.size() << " ";
      for (const auto& vect : doc.second) {
        docFile << vect << " ";
      }
    }

    docFile << "\n";

    writtenFiles.insert(hash);

    docFile.close();
  }
}