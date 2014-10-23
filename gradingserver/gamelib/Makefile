# Makefile to build game library.

.PHONY: clean

CXX=g++
CXXFLAGS= -Wall -pedantic -std=c++11 -fPIC
SRCS=game_state.cpp actor.cpp hero_actor.cpp public.cpp
OBJS=$(SRCS:.cpp=.o)

GAME_LIB_NAME=libgame.so

all: game_lib

#%.o: %.cpp
#	$(CXX) $(CXXFLAGS) -fPIC -c $< -o $@

depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CXX) $(CXXFLAGS)  -MM $^ > ./.depend;

include .depend

game_lib: $(OBJS)
	$(CXX) -shared -Wl,-soname,$(GAME_LIB_NAME) -o $(GAME_LIB_NAME) $^

clean:
	rm -f *.o $(GAME_LIB_NAME)

