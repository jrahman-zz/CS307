# Makefile to build game library.

.PHONY: clean

CXX=g++
CXXFLAGS= -Wall -pedantic -std=c++11
SRCS=$(wildcard *.cpp)
OBJS=$(SRCS:.cpp=.o)

GAME_LIB_NAME=libgame.so

all: game_lib

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -fPIC $< -o $@

game_lib: $(OBJS)
	$(CXX) -shared -Wl,-soname,$(GAME_LIB_NAME) -o $(GAME_LIB_NAME) $^

clean:
	rm -f *.o $(GAME_LIB_NAME)

