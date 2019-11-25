#include "levenshtein.h"

namespace spellchecker
{

static std::size_t levenshtein(std::string left, std::string right) noexce
{
  std::size_t columns = left.length() + 1;
  std::size_t rows = right.length() + 1;

  std::vector<std::size_t> curr_row(columns);

  for (std::size_t col = 1; col < columns; col++)
  {
    curr_row[col] = curr_row[col - 1] + 1;
  }

  for (std::size_t row = 1; row < rows; row++)
  {
    std::vector<std::size_t> prev_row(curr_row);

    curr_row.clear();
    curr_row.push_back(prev_row[0] + 1);

    for (std::size_t col = 1; col < columns; col++)
    {
      std::size_t insert_cost = curr_row[col - 1] + 1;
      std::size_t delete_cost = prev_row[col] + 1;
      std::size_t replace_cost;

      if (left[col - 1] != right[row - 1])
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

}  // namespace spellchecker
