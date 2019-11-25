cmake_minimum_required(VERSION 3.15)

project(spell-checker)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(spellchecker 
  include/levenshtein.h
  include/trie.h 
  src/levenshtein.cpp)
target_include_directories(spellchecker PUBLIC include)

add_executable(dummy_demo src/dummy_demo.cpp)
target_link_libraries(dummy_demo spellchecker)
target_include_directories(dummy_demo PUBLIC include)
