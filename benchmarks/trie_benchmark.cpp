#include "benchmark.h"
#include "dictionary_loader.h"

#include <algorithm>
#include <vector>
#include <utility>
#include <string>
#include <fstream>

std::vector<std::string> dict;

double trie_insert()
{
  std::random_shuffle(dict.begin(), dict.end());

  spellchecker::Trie trie;
  
  double t = 0;
  for (auto word : dict)
  {
    t += measure_time(&spellchecker::Trie::insert, &trie, word);
  }
  
  return t / dict.size();
}

double trie_search()
{
  std::random_shuffle(dict.begin(), dict.end());
  
  spellchecker::Trie trie;
  for (auto word : dict)
  {
    trie.insert(word);
  }
  
  double t = 0;
  for (auto word : dict)
  {
    t += measure_time(&spellchecker::Trie::has_word, &trie, word);
  }
  
  return t / dict.size();
}

double trie_remove()
{
  std::random_shuffle(dict.begin(), dict.end());
  
  spellchecker::Trie trie;
  for (auto word : dict)
  {
    trie.insert(word);
  }
  
  double t = 0;
  for (auto word : dict)
  {
    t += measure_time(&spellchecker::Trie::remove, &trie, word);
  }
  
  return t / dict.size();
}

int main()
{
  std::ifstream source{"data/english.txt"};
  if (!source.is_open())
  {
    std::cerr << "failed to open stream at" << __FILE__ << ":" << __LINE__ << "\n";
    return 0;
  }

  spellchecker::dictionary_loader::read_from_stream(source, dict);
  
  SETUP_BENCHMARK();

  BENCHMARK(trie_insert);
  BENCHMARK(trie_search);
  BENCHMARK(trie_remove);
  
  for (const auto &[name, nano] : benchmarks)
  {
    std::cout << name << "\t" << nano << "ns\n";
  }
  
  return 0;
}