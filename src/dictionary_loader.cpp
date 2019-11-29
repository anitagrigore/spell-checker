#include "dictionary_loader.h"

#include "trie.h"

#include <istream>
#include <string>

namespace spellchecker::dictionary_loader
{

void read_from_stream(std::istream &input, Trie &dict)
{
  std::string line;

  while (std::getline(input, line))
  {
    if (!line.empty())
    {
      dict.insert(line);
    }
  }
}

void read_from_stream(std::istream &input, std::vector<std::string> &dict)
{
  std::string line;

  while (std::getline(input, line))
  {
    if (!line.empty())
    {
      dict.push_back(line);
    }
  }
}

}  // namespace spellchecker::dictionary_loader
