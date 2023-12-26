#include <gtest/gtest.h>
#include <libindex/index.h>
#include <libindexaccessor/indexaccessor.h>
#include <libparser/parser.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

TEST(TextIndexAccessorTest, Config) {
  Parser parser(2, {"the", "and"}, 3);

  TextIndexAccessor indexAccessor("your_path", parser);

  const Parser& resultParser = indexAccessor.config();

  ASSERT_EQ(&parser, &resultParser) << "Error: problems with the config.";
}

TEST(IndexAccessorTest, RetPath) {
  Parser parser(5, {"the", "and", "is"}, 5);

  TextIndexAccessor accessor("../../../src/index - files/", parser);

  EXPECT_EQ(accessor.RetPath(), "../../../src/index - files/")
      << "Error: problem with returning the path";
}

TEST(IndexAccessorTest, Get_Term_Infos) {
  Parser parser(5, {"the", "and", "is"}, 5);
  IndexBuilder indexBuilder(parser);

  indexBuilder.addDocument("103", "Story Earth");
  indexBuilder.addDocument("101", "Hello Hello World");
  indexBuilder.addDocument("102", "Story Earth");

  const Index index = indexBuilder.getIndex();

  indexBuilder.writeToDirectory("../../../");

  TextIndexAccessor text("../../../index - files/", parser);

  std::string e_term = "story";

  TermInfos res = text.get_term_infos(e_term);

  TermInfos exp = {{"story", {{"103", {0}}, {"102", {0}}}}};

  EXPECT_EQ(res.size(), exp.size())
      << "Error: problem with getting information about the term from the "
         "entries folder";

  for (auto it_res = res.begin(); it_res != res.end(); ++it_res) {
    const auto& term_res = it_res->first;
    const auto& docs_res = it_res->second;

    auto it_exp = exp.find(term_res);
    ASSERT_NE(it_exp, exp.end())
        << "Error: Terminfo content does not match expected";
    ASSERT_EQ(it_exp->second, docs_res)
        << "Error: Terminfo content does not match expected";
  }
}

TEST(IndexAccessorTest, Search) {
  Parser parser(5, {"the", "and", "is"}, 5);
  IndexBuilder indexBuilder(parser);

  indexBuilder.addDocument("103", "Story Earth");
  indexBuilder.addDocument("101", "Hello Hello World");
  indexBuilder.addDocument("102", "Story Earth");

  const Index index = indexBuilder.getIndex();

  indexBuilder.writeToDirectory("../../../");

  TextIndexAccessor text("../../../index - files/", parser);

  std::string searching = "Hello World";

  Result exp;
  document doc1 = {"101", 3.2958368660043291};
  exp.found.push_back(doc1);
  document doc2 = {"102", 0};
  exp.found.push_back(doc2);
  document doc3 = {"103", 0};
  exp.found.push_back(doc3);

  Result res = search(searching, text);

  EXPECT_EQ(res.found.size(), exp.found.size());

  for (size_t i = 0; i < exp.found.size(); ++i) {
    const document& expected_doc = exp.found[i];
    const document& actual_doc = res.found[i];

    ASSERT_EQ(expected_doc.id, actual_doc.id)
        << "Error: after calling the search function, the IDs of the documents "
           "in the Result structure are not expected";
    ASSERT_EQ(expected_doc.score, actual_doc.score)
        << "Error: after calling the search function, the document score field "
           "in the Result structure is not expected";
  }
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}