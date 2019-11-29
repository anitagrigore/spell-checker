#include "trie_dictionary.h"

#include "dictionary_loader.h"

#include <algorithm>
#include <istream>

namespace spellchecker
{

void TrieDictionary::read_from_stream(std::istream &input)
{
  dictionary_loader::read_from_stream(input, trie_);
}

/**
 * \brief Searches for the words with a distance smaller than \p max_cost.
 * \param seq The word that has to be corrected with possible words existing in the dictionary
 * \param max_cost The maximum value of the Levenshtein distance accepted for spell checking.
 * \return Returns a vector of (word, cost) pairs.
 **/
std::vector<TrieDictionary::WordCost> TrieDictionary::get_corrections(
    std::string seq, std::size_t max_cost) noexcept
{
  std::size_t columns = seq.length();
  std::vector<std::size_t> curr_row(columns);

  for (size_t col = 1; col < columns; col++)
  {
    curr_row[col] = curr_row[col - 1] + 1;
  }

  std::vector<TrieDictionary::WordCost> results;

  for (auto child : trie_.root_->children)
  {
    if (!child)
    {
      continue;
    }

    auto letter = child->chr;
    search_recursive(
        trie_.root_->children[Trie::charToIndex(letter)], letter, seq, curr_row, results, max_cost);
  }

  return results;
}

void TrieDictionary::search_recursive(Trie::Node *node, char letter, std::string word,
    std::vector<std::size_t> prev_row, std::vector<TrieDictionary::WordCost> &results,
    std::size_t max_cost)
{
  if (word.length() == 1)
    return;
  std::size_t columns = word.length() + 1;
  std::vector<std::size_t> curr_row;
  curr_row.push_back(prev_row[0] + 1);

  for (std::size_t col = 1; col < columns; col++)
  {
    std::size_t insert_cost = curr_row[col - 1] + 1;
    std::size_t delete_cost = prev_row[col] + 1;

    std::size_t replace_cost;

    if (word[col - 1] != letter)
    {
      replace_cost = prev_row[col - 1] + 1;
    }
    else
    {
      replace_cost = prev_row[col - 1];
    }

    curr_row.emplace_back(std::min(std::min(insert_cost, delete_cost), replace_cost));
  }

  if (curr_row.back() <= max_cost && node->end_of_word)
  {
    results.emplace_back(node->word(), curr_row.back());
  }

  if (*std::min_element(curr_row.begin(), curr_row.end()) <= max_cost)
  {
    for (auto child : node->children)
    {
      if (!child)
      {
        continue;
      }

      auto letter = child->chr;
      search_recursive(
          node->children[Trie::charToIndex(letter)], letter, word, curr_row, results, max_cost);
    }
  }
}

}  // namespace spellchecker
