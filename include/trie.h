#pragma once

#include <initializer_list>
#include <iostream>
#include <memory>
#include <set>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>
#include <stack>

namespace spellchecker
{
  
class TrieDictionary;
  
}

class Trie
{
  friend class spellchecker::TrieDictionary;

  static const int kLettersCount = 26;

  static std::size_t charToIndex(char c) noexcept
  {
    return c - 'a';
  }

public:
  struct Node
  {
    friend class TrieDictionary;

  public:
    explicit Node(char chr = '\0', bool end_of_word = false, Node *parent = nullptr) :
        children{},
        parent{parent},
        chr{chr},
        children_count{0},
        end_of_word{end_of_word}
    {}

    ~Node()
    {
      for (auto &i : children)
      {
        delete i;
      }
    }

    Node *childAt(char c)
    {
      return children[charToIndex(c)];
    }

    bool hasChildAt(char c) const
    {
      return children[charToIndex(c)] != nullptr;
    }

    void insertChild(Node *node)
    {
      if (hasChildAt(node->chr) || node->chr == '\0')
      {
        throw std::invalid_argument("node is invalid");
      }

      children[charToIndex(node->chr)] = node;
      node->parent = this;

      children_count++;
    }

    void deleteChildAt(char c)
    {
      if (children[charToIndex(c)])
      {
        children_count--;

        delete children[charToIndex(c)];
        children[charToIndex(c)] = nullptr;
      }
    }
    
    std::string word() const
    {
      std::stack<char> s;
      
      auto curr = this;
      while (curr->parent)
      {
        s.push(curr->chr);
        curr = curr->parent;
      }
      
      std::string w;

      while (!s.empty())
      {
        w.push_back(s.top());
        s.pop();
      }
      
      return w;
    }

    Node *children[kLettersCount];
    Node *parent;
    char chr;
    std::size_t children_count;
    bool end_of_word;
  };

  // Create an empty Trie.
  Trie() : root_{std::make_unique<Node>()}, size_{0}
  {}

  // Create a Trie from a list of words.
  Trie(const std::initializer_list<std::string> &words) : Trie()
  {
    for (const auto &str : words)
    {
      insert(str);
    }
  }

  // Insert a new word into the trie.
  void insert(std::string word) noexcept
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

  // Check whether the given word exists in the Trie.
  bool has_word(std::string word) const noexcept
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

  // Remove the given word from the Trie. Returns true if the word existed and
  // was deleted and false otherwise.
  bool remove(std::string word) noexcept
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

  std::size_t size() const
  {
    // TODO Check whether storing a cached size is better than calculating it or not.
    return size_;
  }

  bool empty() const
  {
    return size() == 0;
  }

private:
  std::unique_ptr<Node> root_;
  std::size_t size_;
};
