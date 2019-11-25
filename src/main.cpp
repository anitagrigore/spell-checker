#include "trie.h"
#include "levenshtein.h"

#include <iostream>

int main()
{
  Trie dict{"victor", "anita", "dan", "danela"};

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
  dict1.push_back("caet");
  dict1.push_back("caiete");
  dict1.push_back("caietele");

  Levenshtein dist(dict1);
  std::vector<std::pair<std::string, std::size_t>> result = dist.search("caiet", 4);

  for (int i = 0; i < result.size(); i++)
  {
    cout << result[i].first << " " << result[i].second;
  }
}
