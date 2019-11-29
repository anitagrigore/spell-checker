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

class Trie
{
  friend class TrieDictionary;

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
    
    /**
     * \brief Recreates the word from characters saved in Trie.
     * \return Returns the word from the Trie.
     **/
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

  /**
   * \brief Create an empty Trie.
   * \return Returns an empty Trie.
   **/ 
  Trie() : root_{std::make_unique<Node>()}, size_{0}
  {}

  /**
   * \brief Create a Trie from a list of words.
   * \param words A list of words to be added to the Trie.
   * return Returns a new Trie with the \p words in it.
   **/ 
  Trie(const std::initializer_list<std::string> &words) : Trie()
  {
    for (const auto &str : words)
    {
      insert(str);
    }
  }
  
  Trie(const std::vector<std::string> &words) : Trie()
  {
    for (const auto &str : words)
    {
      insert(str);
    }
  }
  
  /**
   * \brief Insert a new word into the trie.
   **/ 
  void insert(std::string word) noexcept;

 /**
  * \brief Check whether the given word exists in the Trie.
  * \return Returns true if it exists, false otherwise
  **/ 
  bool has_word(std::string word) const noexcept;

  /**
   * \brief Remove the given word from the Trie.
   * \return Returns true if the word existed and was deleted and false otherwise.
   **/
  bool remove(std::string word) noexcept;

  std::size_t size() const noexcept
  {
    return size_;
  }

  bool empty() const noexcept
  {
    return size() == 0;
  }

private:
  std::unique_ptr<Node> root_;
  std::size_t size_;
};

}
