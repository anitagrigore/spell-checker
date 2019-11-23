CXX=g++
CXXFLAGS=-std=c++17 -Iinclude
BIN=bin

bin/main: src/main.cpp include/trie.h
	$(CXX) -o $@ $< $(CXXFLAGS)
