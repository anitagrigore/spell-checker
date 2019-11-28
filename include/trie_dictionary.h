#pragma once

#include "trie.h"

#include <istream>
#include <utility>
#include <string>
#include <cstdint>
#include <vector>

namespace spellchecker
{
  
class TrieDictionary
{
public:
  using WordCost = std::pair<std::string, std::size_t>;
  
  static constexpr std::size_t DEFAULT_CORRECTIONS_MAX_COST = 1;
  
  TrieDictionary() = default;
  
  TrieDictionary(std::initializer_list<std::string> values) : trie_{values}
  {}
  
  /**
   * \brief Populate the dictionary from an input stream.
   * \see spellchecker::dictionary_loader::read_from_stream
   */
  void read_from_stream(std::istream &in);
  
  std::vector<WordCost> get_corrections(std::string seq, 
      std::size_t max_cost = DEFAULT_CORRECTIONS_MAX_COST) noexcept;
      
private:
  void search_recursive(Trie::Node* node, 
      char letter, 
      std::string word, 
      std::vector<std::size_t> prev_row, 
      std::vector<std::pair<std::string, std::size_t>> &results, 
      std::size_t max_cost);

private:
  Trie trie_;
};

}
