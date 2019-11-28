cmake_minimum_required(VERSION 3.15)

project(spell-checker)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_library(spellchecker 
  include/levenshtein.h
  include/trie.h 
  include/trie_dictionary.h
  include/linear_dictionary.h
  include/dictionary_loader.h
  src/levenshtein.cpp
  src/trie_dictionary.cpp
  src/dictionary_loader.cpp
  src/linear_dictionary.cpp
  src/trie.cpp)
target_include_directories(spellchecker PUBLIC include)

add_executable(dummy_demo src/dummy_demo.cpp)
target_link_libraries(dummy_demo spellchecker)
target_include_directories(dummy_demo PUBLIC include)

add_executable(trie_demo src/trie_demo.cpp)
target_link_libraries(trie_demo spellchecker)
target_include_directories(trie_demo PUBLIC include)

add_executable(benchmark benchmarks/trie_benchmark.cpp)
target_link_libraries(benchmark spellchecker)
target_include_directories(benchmark PUBLIC include)


# Link Google Test and discover unit tests

enable_testing()
find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(tests
  tests/trie_test.cpp
  tests/levenshtein_test.cpp
  tests/dictionary_loader_test.cpp
  tests/trie_dictionary_test.cpp)
target_link_libraries(tests 
  GTest::GTest 
  GTest::Main 
  spellchecker)
gtest_discover_tests(tests)
