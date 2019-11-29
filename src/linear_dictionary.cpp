#include "linear_dictionary.h"

#include "dictionary_loader.h"
#include "levenshtein.h"

namespace spellchecker
{

std::vector<std::pair<std::string, std::size_t>> LinearDictionary::get_corrections(
    std::string target, std::size_t max_cost)
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

void LinearDictionary::read_from_stream(std::istream &input)
{
  dictionary_loader::read_from_stream(input, words);
}

}  // namespace spellchecker