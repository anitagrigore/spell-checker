#include <cstdint>
#include <string>
#include <utility>
#include <vector>

namespace spellchecker
{

class LinearDictionary
{
public:
  std::string word;
  std::size_t cost;
  std::vector<std::string> words;

  LinearDictionary() = default;

  LinearDictionary(std::vector<std::string> words)
  {
    this->words = words;
  }

  LinearDictionary(std::initializer_list<std::string> words) : words{words}
  {}

  /**
   * \brief Populate the dictionary from an input stream.
   * \see spellchecker::dictionary_loader::read_from_stream
   */
  void read_from_stream(std::istream &in);

  /**
   * \brief Gives a set of words from the existent dictionary as a possible
   * correction for the \p target.
   *
   * \param target The word which has to be corrected.
   * \param max_cost The maximum distance between the \p target and the words in
   * the dictionary.
   *
   * \return Returns a list of words with the correspondent cost that are suited
   * corrections for the \p target.
   **/
  std::vector<std::pair<std::string, std::size_t>> get_corrections(
      std::string target, std::size_t max_cost);
};

}  // namespace spellchecker
