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
 * \param dict The trie to be populated with the words read.
 */
void read_from_stream(std::istream &input, Trie &dict);

/**
 * \brief Read the dictionary from an input stream. Each word must be on its own
 * line in the stream (i.e. separated by LF).
 * \param input The stream to read from. Note that the stream will be read until
 * EOF or another error condition occurs.
 * \param dict The vector to be populated with the words read.
 **/ 
void read_from_stream(std::istream &input, std::vector<std::string> &dict);

}
