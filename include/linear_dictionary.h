#include <string>
#include <cstdint>
#include <vector>
#include <utility>

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
  
  LinearDictionary(std::initializer_list<std::string> words): words{words}
  {}
  
  /**
   * \brief Populate the dictionary from an input stream.
   * \see spellchecker::dictionary_loader::read_from_stream
   */
  void read_from_stream(std::istream &in);

  std::vector<std::pair<std::string, std::size_t>> get_corrections(std::string target, 
      std::size_t max_cost);
};

}
