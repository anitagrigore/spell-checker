#include "trie_dictionary.h"

#include <sstream>
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

int main(int argc, char **argv)
{
  if (argc < 3)
  {
    return 1;
  }

  std::ifstream dictionary_source{argv[1]};
  std::string word{argv[2]};
  
  spellchecker::TrieDictionary dict;
  dict.read_from_stream(dictionary_source);
  
  auto corrections = dict.get_corrections(word);
  std::sort(corrections.begin(), corrections.end(), [](auto &&a, auto &&b) {
    return a.second < b.second;
  });
  
  for (const auto &[word, cost] : corrections)
  {
    std::cout << word << " -> " << cost << "\n";
  }
  
  return 0;
}
