#pragma once

#include <algorithm>
#include <cstdint>

namespace spellchecker
{

/**
 * \brief Calculates the Levenshtein distance between \p left and \p right.
 */
std::size_t levenshtein(std::string left, std::string right) noexcept;

}  // namespace spellchecker
