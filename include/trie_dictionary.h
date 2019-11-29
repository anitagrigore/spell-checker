#pragma once

#include "trie.h"

#include <cstdint>
#include <istream>
#include <string>
#include <utility>
#include <vector>

namespace spellchecker
{

class TrieDictionary
{
public:
  using WordCost = std::pair<std::string, std::size_t>;

  static constexpr std::size_t DEFAULT_CORRECTIONS_MAX_COST = 2;

  TrieDictionary() = default;

  TrieDictionary(std::initializer_list<std::string> values) : trie_{values}
  {}

  TrieDictionary(std::vector<std::string> values) : trie_{values}
  {}

  /**
   * \brief Populate the dictionary from an input stream.
   * \see spellchecker::dictionary_loader::read_from_stream
   */
  void read_from_stream(std::istream &in);

  /**
   * \brief Gives a set of words from the existent dictionary as a possible
   * correction for the \p seq.
   *
   * \param seq The word which has to be corrected.
   * \param max_cost The maximum distance between the \p target and the words in
   * the dictionary.
   *
   * \return Returns a list of words with the correspondent cost that are suited
   * corrections for the \p target.
   **/
  std::vector<WordCost> get_corrections(
      std::string seq, std::size_t max_cost = DEFAULT_CORRECTIONS_MAX_COST) noexcept;

private:
  void search_recursive(Trie::Node *node, char letter, std::string word,
      std::vector<std::size_t> prev_row, std::vector<std::pair<std::string, std::size_t>> &results,
      std::size_t max_cost);

private:
  Trie trie_;
};

}  // namespace spellchecker
