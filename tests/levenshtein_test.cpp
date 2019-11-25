#include "gtest/gtest.h"
#include "levenshtein.h"

namespace spellchecker
{

TEST(Levenshtein, Dummy)
{
  ASSERT_EQ(levenshtein("foo", "foo"), 0);
  ASSERT_EQ(levenshtein("foo", "fooo"), 1);
}

}