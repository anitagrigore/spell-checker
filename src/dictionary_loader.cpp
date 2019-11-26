#include "dictionary_loader.h"
#include "trie.h"

#include <string>
#include <istream>

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

}
