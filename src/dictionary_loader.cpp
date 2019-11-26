#include "dictionary_loader.h"
#include "trie.h"

#include <string>
#include <istream>

namespace spellchecker::dictionary_loader
{
    
Trie read_from_stream(std::istream &input)
{
  Trie trie;
  std::string line;

  while (std::getline(input, line))
  {
    if (!line.empty())
    {
      trie.insert(line);
    }
  }
  
  return trie;
}
    
}