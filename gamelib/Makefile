# Makefile to build game library.

.PHONY: clean
.PHONY: test

CXX	 	:= g++
CXXFLAGS 	:= -Wall -pedantic -std=c++11
SRCDIR 	 	:= src
TESTDIR  	:= test
BUILDDIR 	:= build
TBUILDDIR 	:= test_build
SOURCES 	:= $(shell find $(SRCDIR) -type f -name *.cpp)
OBJECTS 	:= $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.cpp=.o))
TESTS		:= $(shell find $(TESTDIR) -type f -name *.cpp)
TESTBIN 	:= $(patsubst $(TESTDIR)/%,$(TBUILDDIR)/%,$(TESTS:.cpp=.out))

INC := -I include
GAME_LIB_NAME=libgame.so

all: game_lib

test: $(TESTBIN)
	@echo "Ran tests"

$(TBUILDDIR)/%.o: $(TESTDIR)/%.cpp
	@mkdir -p $(TBUILDDIR)
	@echo " $(CXX) $(CXXFLAGS) $(INC) -c -o $@ $<"; $(CXX) $(CXXFLAGS) $(INC) -c -o $@ $<

$(TBUILDDIR)/%.out: $(TBUILDDIR)/%.o $(OBJECTS)
	$(CXX) $^ -o $@
	$@

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(BUILDDIR)
	@echo " $(CXX) $(CXXFLAGS) $(INC) -c -o $@ $<"; $(CXX) $(CXXFLAGS) $(INC) -c -o $@ $<

game_lib: $(OBJECTS)
	$(CXX) -shared -Wl,-soname,$(GAME_LIB_NAME) -o $(GAME_LIB_NAME) $^

object:
	echo "$(SOURCES):$(SOURCES:.cpp=.o)"

clean:
	@echo "$(RM) -r $(BUILDDIR) $(GAME_LIB_NAME)"; $(RM) -r $(BUILDDIR) $(GAME_LIB_NAME)
	@echo "$(RM) -r $(TBUILDDIR)"; $(RM) -r $(TBUILDDIR)
