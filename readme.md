Grigore Iulia-Anita, 322CA

# Trie

The trie has 3 main functions, `insert`, `has_word` and `remove`, declared in `trie.h`
and implemented in `trie.cpp`.

## `insert`
Add a word in a trie by checking each letter of it. If the letter is in the trie, move the
pointer to the next children. Otherwise, insert the letter and continue. When all the letters
are in the trie, set the flag `end_of_word` to true.

## `has_word`
For each letter in the word, check if it is in the trie. If a letter is not found in it, return.
Otherwise, if all the letter are in the right order in the trie, return the flag `end_of_word`.
(This cand return false if the sequence is in the trie, but is not marked as a word; for example,
if the word `moment` is in the trie, but `mom` isn't, and we call the function with the parameter 
`mom`, it will return false).

## `remove`
If the word exists in the trie (the sequence is found and the `end_of_word` flag is set),
delete the current node and go up to the first letter of the word or until it finds
another `end_of_word`.

# Levenshtein distance

I implemented this algorithm in two ways. First one (`linear_dictionary.h`, 
`linear_dictionary.cpp`) is the simple one, where the dictionary is saved in a list
(or a vector) and the other one (`trie_dictionary.h`, `trie_dictionary.cpp`) uses a
trie for the storage of the dictionary. Both have a function called `get_corrections`
which returns a std::vector of words and costs. The difference between the two
implementations is a very important one and it consists of the average time it takes to
find the possible corrections for a word. While the first one takes, on average, 
2200 ms, the second one takes 37 ms.

# Testing

In the folder `tests` I created unit tests for all the important functions of the 
algorithms implemented. For testing the `trie_dictionary` I created a unit test
which compares the output of the `get_corrections` function of the `linear_dictionary`
and `trie_dictionary`.

The folder `benchmarks` has files calculating the average time it takes to perform certain
actions (like inserting/searching/removing a word into/from a trie or getting the possible
corrections for a word using `linear_dictionary` and `trie_dictionary`). I limited the
the dictionary to 130 words (from a total of 380000).
