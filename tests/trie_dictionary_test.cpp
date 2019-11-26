#include "gtest/gtest.h"
#include "trie_dictinary.h"


namespace spellchecker::TrieDictionary
{

TEST(TrieDictionary, Corections)
{
  Trie trie{"foo", "bar", "baz"};
  
  ASSERT_EQ(get_corrections("fo", 2), "foo");
}


}