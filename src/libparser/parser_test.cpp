#include <gtest/gtest.h>
#include <libparser/parser.h>

TEST(ParserTest, First) {
  Parser parser(2, {"a", "is", "this"}, 3);

  std::string text = "This is a simple test.";
  auto ngrams = parser.parseText(text);

  ASSERT_EQ(ngrams.size(), 4);

  ASSERT_EQ(ngrams[0].first, "si");
  ASSERT_EQ(ngrams[0].second, 0);

  ASSERT_EQ(ngrams[1].first, "sim");
  ASSERT_EQ(ngrams[1].second, 0);

  ASSERT_EQ(ngrams[2].first, "te");
  ASSERT_EQ(ngrams[2].second, 1);

  ASSERT_EQ(ngrams[3].first, "tes");
  ASSERT_EQ(ngrams[3].second, 1);
}

TEST(ParserTest, Second) {
  Parser parser(1, {"a", "is", "test"}, 4);

  std::string text = "This is a test.";
  auto ngrams = parser.parseText(text);

  ASSERT_EQ(ngrams.size(), 4);

  ASSERT_EQ(ngrams[0].first, "t");
  ASSERT_EQ(ngrams[0].second, 0);

  ASSERT_EQ(ngrams[1].first, "th");
  ASSERT_EQ(ngrams[1].second, 0);

  ASSERT_EQ(ngrams[2].first, "thi");
  ASSERT_EQ(ngrams[2].second, 0);

  ASSERT_EQ(ngrams[3].first, "this");
  ASSERT_EQ(ngrams[3].second, 0);
}

TEST(ParserTest, Third) {
  Parser parser(1, {}, 1);

  std::string text = "This is a test.";
  auto ngrams = parser.parseText(text);

  ASSERT_EQ(ngrams.size(), 4);

  ASSERT_EQ(ngrams[0].first, "t");
  ASSERT_EQ(ngrams[0].second, 0);

  ASSERT_EQ(ngrams[1].first, "i");
  ASSERT_EQ(ngrams[1].second, 1);

  ASSERT_EQ(ngrams[2].first, "a");
  ASSERT_EQ(ngrams[2].second, 2);

  ASSERT_EQ(ngrams[3].first, "t");
  ASSERT_EQ(ngrams[3].second, 3);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}