#pragma once

#include <algorithm>
#include <cstdint>

namespace spellchecker
{

/**
 * \brief Calculates the Levenshtein distance between \p left and \p right.
 */
std::size_t levenshtein(std::string left, std::string right) noexcept;

}  // namespace spellchecker

class Levenshtein
{
public:
  std::string word;
  std::size_t cost;
  std::vector<std::string> words;

  Levenshtein(std::vector<std::string> words)
  {
    this->words = words;
  }

  std::vector<std::pair<std::string, std::size_t>> search(std::string target, std::size_t max_cost)
  {
    std::vector<std::pair<std::string, std::size_t>> results;
    for (auto word : words)
    {
      cost = spellchecker::levenshtein(target, word);

      if (cost <= max_cost)
      {
        results.emplace_back(word, cost);
      }
    }

    return results;
  }
};
