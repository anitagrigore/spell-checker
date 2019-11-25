#pragma once

#include <algorithm>

class Levenshtein
{
public:
  std::string word;
  std::size_t cost;
  std::vector<std::string> words;

  Levenshtein(std::vector<std::string> words)
  {
    this->words = words;
  }

    std::size_t levenshtein(std::string word1, std::string word2)
    {
      std::size_t columns = word1.length() + 1;
      std::size_t rows = word2.length() + 1;

      std::vector<std::size_t> curr_row;
      curr_row.push_back(0);
      for (int col = 1; col < columns; col++)
      {
        curr_row.push_back(curr_row[col - 1] + 1);
      }

      for (int row = 1; row <rows; row++)
      {
        std::size_t insert_cost;
        std::size_t delete_cost;
        std::size_t replace_cost;

        std::vector<std::size_t> prev_row;
        for (int i = 0; i < curr_row.size(); i++)
        {
          prev_row[i] = curr_row[i];
        }

        curr_row.clear();
        curr_row.push_back(prev_row[0] + 1);

        for (int col = 1; col < columns; col++)
        {
          insert_cost = curr_row[col - 1] + 1;
          delete_cost = prev_row[col] + 1;

          if (word1[col - 1] != word2[row - 1])
          {
            replace_cost = prev_row[col - 1] + 1;
          }
          else
          {
            replace_cost = prev_row[col - 1];
          }

          curr_row.push_back(std::min(std::min(insert_cost, delete_cost), replace_cost));
        }
      }

      return curr_row.back();
    }

    std::vector<std::pair<std::string, std::size_t>> search(std::string target, std::size_t max_cost)
    {
      std::vector<std::pair<std::string, std::size_t>> results;
      for (auto word : words)
      {
        cost = levenshtein(target, word);

        if (cost <= max_cost)
        {
          results.emplace_back(word, cost);
        }
      }

      return results;
    }
};
