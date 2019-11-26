cmake_minimum_required(VERSION 3.15)

project(spell-checker)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(spellchecker 
  include/levenshtein.h
  include/trie.h 
  include/dictionary_loader.h
  src/levenshtein.cpp
  src/dictionary_loader.cpp)
target_include_directories(spellchecker PUBLIC include)

add_executable(dummy_demo src/dummy_demo.cpp)
target_link_libraries(dummy_demo spellchecker)
target_include_directories(dummy_demo PUBLIC include)

# Link Google Test and discover unit tests

enable_testing()
find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(tests
  tests/trie_test.cpp
  tests/levenshtein_test.cpp
  tests/dictionary_loader_test.cpp)
target_link_libraries(tests 
  GTest::GTest 
  GTest::Main 
  spellchecker)
gtest_discover_tests(tests)
