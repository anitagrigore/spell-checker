CXX=g++
CXXFLAGS=-std=c++17 -Iinclude -g
BIN=bin

bin/main: src/main.cpp include/trie.h include/levenshtein.h
	$(CXX) -o $@ $< $(CXXFLAGS)
