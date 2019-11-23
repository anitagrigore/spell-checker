#include "trie.h"

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
}
