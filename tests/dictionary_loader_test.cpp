#include "gtest/gtest.h"
#include "dictionary_loader.h"

#include <sstream>

namespace spellchecker::dictionary_loader
{
    
TEST(DictionaryLoader, ReadFromStream)
{
  std::istringstream in{"foo\nbar\nbaz\n"};
  
  auto dict = read_from_stream(in);
  
  EXPECT_EQ(dict.size(), 3);
  EXPECT_TRUE(dict.has_word("foo"));
  EXPECT_TRUE(dict.has_word("bar"));
  EXPECT_TRUE(dict.has_word("baz"));
}
    
}
