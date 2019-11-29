#include "benchmark.h"
#include "dictionary_loader.h"
#include "trie_dictionary.h"

#include <algorithm>
#include <vector>
#include <utility>
#include <string>
#include <fstream>
#include <random>

std::vector<std::string> dict;

/**
 * \brief Mesure the average time it takes to find in a trie dictionary 
 * all the corrections with a maximum distance for a word.
 **/ 
double get_correction()
{
  spellchecker::TrieDictionary trie_dict(dict);
  std::random_shuffle(dict.begin(), dict.end());
  
  std::random_device seeder;
  std::mt19937 engine(seeder());

  std::uniform_int_distribution<int> changes_count(0, 2);
  std::uniform_int_distribution<char> random_chr('a', 'z');
  
  double total_time = 0;
  std::size_t nth = 0;
  std::size_t words_count = 0;
  
  // For every word in the dictionary, alter them with 0 to 2 character.
  for (auto &word : dict)
  {
    if (nth++ % 3000 != 0)
    {
      continue;
    }

    std::uniform_int_distribution<int> diff_idx(0, word.length() - 1);
    
    for (std::size_t i = 0; i < changes_count(engine); i++)
    {
      std::size_t random_pos = diff_idx(engine);
      word[random_pos] = random_chr(engine);
    }
    
    total_time += measure_time<std::milli>(&spellchecker::TrieDictionary::get_corrections, 
        &trie_dict, word, 2);
    words_count++;
  }
  
  return total_time / words_count;
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

  BENCHMARK(get_correction);
  
  
  for (const auto &[name, nano] : benchmarks)
  {
    std::cout << name << "\t" << nano << "ms\n";
  }
  
  return 0;
}