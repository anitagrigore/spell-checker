CXX=g++
CXXFLAGS=-std=c++17 -Iinclude -g
BIN=bin

bin/main: src/main.cpp include/trie.h
	$(CXX) -o $@ $< $(CXXFLAGS)
