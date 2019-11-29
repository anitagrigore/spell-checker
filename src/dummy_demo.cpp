#include "levenshtein.h"
#include "linear_dictionary.h"
#include "trie.h"

#include <algorithm>
#include <iostream>

int main(int argc, char **argv)
{
  spellchecker::Trie dict{"victor", "anita", "dan", "danela"};

  using std::cout, std::endl;
  cout << dict.size() << endl;

  cout << std::boolalpha;

  cout << dict.remove("victor") << endl;  // true
  cout << dict.remove("ani") << endl;  // false
  cout << dict.remove("dane") << endl;  // false
  cout << dict.remove("danela") << endl;  // true
  cout << dict.has_word("dan") << endl;  // true
  cout << dict.has_word("anita") << endl;  // true

  cout << dict.size() << endl;

  cout << endl;

  std::vector<std::string> dict1;
  dict1.push_back("caiet");
  dict1.push_back("caiete");
  dict1.push_back("carnat");
  dict1.push_back("caietele");
  dict1.push_back("carnati");
  dict1.push_back("copii");
  dict1.push_back("copil");

  spellchecker::LinearDictionary dist(dict1);
  std::string input{argv[1]};
  std::vector<std::pair<std::string, std::size_t>> result = dist.get_corrections(input, 1);
  std::sort(result.begin(), result.end(), [](auto &&a, auto &&b) { return a.second < b.second; });

  for (const auto &[word, cost] : result)
  {
    std::cout << word << " -> " << cost << "\n";
  }
}
