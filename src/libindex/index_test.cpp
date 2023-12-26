#include <gtest/gtest.h>
#include <libindex/index.h>
#include <libparser/parser.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

TEST(IndexBuilderTest, HashTerm) {
  Parser parser(2, {"the", "and"}, 3);
  IndexBuilder indexBuilder(parser);

  std::string hashedTerm = indexBuilder.hashTerm("example_term");
  std::string expectedHash = "ad288e";

  ASSERT_EQ(hashedTerm.size(), 6);
  ASSERT_EQ(hashedTerm, expectedHash);
}

TEST(IndexBuilderTest, GetIndex) {
  Parser parser(2, {"the", "and"}, 3);
  IndexBuilder indexBuilder(parser);

  indexBuilder.addDocument("doc1", "This is document 1.");
  indexBuilder.addDocument("doc2", "Another document.");

  Index index = indexBuilder.getIndex();

  ASSERT_EQ(index.docs.size(), 2);

  ASSERT_EQ(index.docs[0].first, "doc1");
  ASSERT_EQ(index.docs[0].second, "This is document 1.");
  ASSERT_EQ(index.docs[1].first, "doc2");
  ASSERT_EQ(index.docs[1].second, "Another document.");

  Index modifiedIndex = indexBuilder.getIndex();
  modifiedIndex.docs.clear();

  ASSERT_EQ(index.docs.size(), 2);
}

TEST(IndexBuilderTest, AddDocument) {
  Parser parser(2, {"the", "and", "is"}, 3);
  IndexBuilder indexBuilder(parser);

  indexBuilder.addDocument("doc1", "This is a test this.");
  indexBuilder.addDocument("doc2", "This is a test test.");

  Index index = indexBuilder.getIndex();

  ASSERT_EQ(index.docs.size(), 2);

  ASSERT_EQ(index.docs[0].first, "doc1");
  ASSERT_EQ(index.docs[0].second, "This is a test this.");

  ASSERT_EQ(index.docs[1].first, "doc2");
  ASSERT_EQ(index.docs[1].second, "This is a test test.");

  ASSERT_EQ(index.entries.size(), 4);

  ASSERT_EQ(index.entries["th"]["doc1"].size(), 2);
  ASSERT_EQ(index.entries["th"]["doc1"][0], 0);
  ASSERT_EQ(index.entries["th"]["doc1"][1], 2);

  ASSERT_EQ(index.entries["th"]["doc2"].size(), 1);
  ASSERT_EQ(index.entries["th"]["doc2"][0], 0);

  ASSERT_EQ(index.entries["thi"]["doc1"].size(), 2);
  ASSERT_EQ(index.entries["thi"]["doc1"][0], 0);
  ASSERT_EQ(index.entries["thi"]["doc1"][1], 2);

  ASSERT_EQ(index.entries["thi"]["doc2"].size(), 1);
  ASSERT_EQ(index.entries["thi"]["doc2"][0], 0);

  ASSERT_EQ(index.entries["tes"]["doc1"].size(), 1);
  ASSERT_EQ(index.entries["tes"]["doc1"][0], 1);

  ASSERT_EQ(index.entries["tes"]["doc2"].size(), 2);
  ASSERT_EQ(index.entries["tes"]["doc2"][0], 1);
  ASSERT_EQ(index.entries["tes"]["doc2"][1], 2);

  ASSERT_EQ(index.entries["tes"]["doc1"].size(), 1);
  ASSERT_EQ(index.entries["tes"]["doc1"][0], 1);

  ASSERT_EQ(index.entries["tes"]["doc2"].size(), 2);
  ASSERT_EQ(index.entries["tes"]["doc2"][0], 1);
  ASSERT_EQ(index.entries["tes"]["doc2"][1], 2);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}