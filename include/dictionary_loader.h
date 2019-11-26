#pragma once

#include <iostream>
#include <istream>

#include "trie.h"

namespace spellchecker::dictionary_loader
{

/**
 * \brief Read the dictionary from an input stream. Each word must be on its own
 * line in the stream (i.e. separated by LF).
 * \param input The stream to read from. Note that the stream will be read until
 * EOF or another error condition occurs.
 * \returns The populated Trie.
 */
Trie read_from_stream(std::istream &input);

}
