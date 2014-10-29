# Makefile to build game library.

.PHONY: clean

CXX := g++
CXXFLAGS := -Wall -pedantic -std=c++11
SRCDIR := src
BUILDDIR := build
SOURCES := $(shell find $(SRCDIR) -type f -name *.cpp)
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.cpp=.o))
INC := -I include
GAME_LIB_NAME=libgame.so

all: game_lib

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(BUILDDIR)
	@echo " $(CXX) $(CXXFLAGS) $(INC) -c -fPIC -o $@ $<"; $(CXX) $(CXXFLAGS) $(INC) -c -fPIC -o $@ $<

game_lib: $(OBJECTS)
	$(CXX) -shared -Wl,-soname,$(GAME_LIB_NAME) -o $(GAME_LIB_NAME) $^

object:
	echo "$(SOURCES):$(SOURCES:.cpp=.o)"

clean:
	@echo "$(RM) -r $(BUILDDIR) $(GAME_LIB_NAME)"; $(RM) -r $(BUILDDIR)

