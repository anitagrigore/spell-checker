#include "trie.h"

namespace spellchecker
{

void Trie::insert(std::string word) noexcept
{
  Node *curr = root_.get();
  for (int i = 0; i < word.length(); i++)
  {
    if (curr->hasChildAt(word[i]))
    {
      curr = curr->childAt(word[i]);
    }
    else
    {
      Node *new_node = new Node(word[i], false, curr);
      curr->insertChild(new_node);
      curr = new_node;
    }
  }

  size_++;
  curr->end_of_word = true;
}

bool Trie::has_word(std::string word) const noexcept
{
  Node *curr = root_.get();
  for (int i = 0; i < word.length(); i++)
  {
    if (curr->hasChildAt(word[i]))
    {
      curr = curr->childAt(word[i]);
    }
    else
    {
      return false;
    }
  }

  return curr->end_of_word;
}

bool Trie::remove(std::string word) noexcept
{
  if (word.empty())
  {
    return false;
  }

  Node *next = root_.get();
  while (next && !word.empty())
  {
    if (next->hasChildAt(word[0]))
    {
      next = next->childAt(word[0]);
    }
    word = word.substr(1);
  }

  if (!next->end_of_word)
  {
    return false;
  }

  do
  {
    auto parent = next->parent;
    parent->deleteChildAt(next->chr);
    next = parent;

    if (parent->children_count >= 1 || parent->end_of_word)
    {
      break;
    }
  } while (next != nullptr && next->parent);

  size_--;
  return true;
}
}  // namespace spellchecker