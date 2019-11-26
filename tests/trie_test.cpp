#include "gtest/gtest.h"
#include "trie.h"

TEST(Trie, Construct)
{
  Trie empty_trie;

  ASSERT_TRUE(empty_trie.empty());

  Trie initializer_list_trie{"foo", "bar"};

  ASSERT_FALSE(initializer_list_trie.empty());
  ASSERT_EQ(initializer_list_trie.size(), 2);
}

TEST(Trie, HasWord)
{
  Trie trie{"foo", "bar"};

  EXPECT_TRUE(trie.has_word("foo"));
  EXPECT_TRUE(trie.has_word("bar"));
  EXPECT_FALSE(trie.has_word("baz"));
}

TEST(Trie, Insert)
{
  Trie trie;

  trie.insert("foo");
  trie.insert("bar");

  EXPECT_TRUE(trie.has_word("foo"));
  EXPECT_TRUE(trie.has_word("bar"));  
}

TEST(Trie, Remove)
{
  Trie trie{"foo", "bar"};
  
  EXPECT_EQ(trie.size(), 2);

  EXPECT_TRUE(trie.remove("foo"));
  EXPECT_EQ(trie.size(), 1);
  EXPECT_FALSE(trie.has_word("foo"));
  
  EXPECT_TRUE(trie.remove("bar"));
  EXPECT_TRUE(trie.empty());
  EXPECT_FALSE(trie.has_word("bar"));
  
  EXPECT_FALSE(trie.remove("baz"));
}
