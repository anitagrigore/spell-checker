#include "gtest/gtest.h"
#include "trie_dictionary.h"
#include "linear_dictionary.h"

#include <algorithm>
#include <fstream>

namespace spellchecker
{

TEST(TrieDictionary, SmallDictionary)
{
  TrieDictionary fast_dictionary{"foo", "bar", "baz"};
  LinearDictionary linear_dictionary{"foo", "bar", "baz"};
  
  ASSERT_EQ(fast_dictionary.get_corrections("fo", 2), linear_dictionary.get_corrections("fo", 2));
}

TEST(TrieDictionary, EnglishDictionary)
{
  std::ifstream in("data/english.txt");
  ASSERT_TRUE(in.is_open());

  TrieDictionary fast_dictionary;
  fast_dictionary.read_from_stream(in);
  
  in.close();
  in.open("data/english.txt");
  ASSERT_TRUE(in.is_open());

  LinearDictionary linear_dictionary;
  linear_dictionary.read_from_stream(in);
  
  auto sort_by_word = [](auto &&a, auto &&b) { return a.first < b.first; };
  
  auto fast_corrections = fast_dictionary.get_corrections("baad", 1);
  auto linear_corrections = linear_dictionary.get_corrections("baad", 1);
  
  std::sort(fast_corrections.begin(), fast_corrections.end(), sort_by_word);
  std::sort(linear_corrections.begin(), linear_corrections.end(), sort_by_word);
  
  EXPECT_EQ(fast_corrections, linear_corrections);
  
  fast_corrections = fast_dictionary.get_corrections("moter", 1);
  linear_corrections = linear_dictionary.get_corrections("moter", 1);

  std::sort(fast_corrections.begin(), fast_corrections.end(), sort_by_word);
  std::sort(linear_corrections.begin(), linear_corrections.end(), sort_by_word);

  EXPECT_EQ(fast_corrections, linear_corrections);
}

}
