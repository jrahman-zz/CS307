# Makefile to build game library.

.PHONY: clean
.PHONY: cleantest
.PHONY: test

CXX	 	:= g++
BASEFLAGS 	:= -Wall -std=c++11 -g
CXXTFLAGS	:= $(BASEFLAGS)
CXXFLAGS	:= $(BASEFLAGS) -pedantic
SRCDIR 	 	:= src
TESTDIR  	:= test
BUILDDIR 	:= build
LIBDIR		:= lib
TBUILDDIR 	:= test_build
SOURCES 	:= $(shell find $(SRCDIR) -type f -name *.cpp)
OBJECTS 	:= $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.cpp=.o))
TESTS		:= $(shell find $(TESTDIR) -type f -name *.cpp)
TESTBIN 	:= $(patsubst $(TESTDIR)/%,$(TBUILDDIR)/%,$(TESTS:.cpp=.out))
BINDIR		:= bin
TOOLDIR		:= tools

INC := -I include
LIBGAME_SHARED=libgame.so
LIBGAME_STATIC=libgame.a

all: $(LIBDIR)/$(LIBGAME_STATIC) $(LIBDIR)/$(LIBGAME_SHARED)

test: cleantest $(TESTBIN)
	@cp $(TESTDIR)/test.sh $(TBUILDDIR)
	@cd $(TBUILDDIR) && ./test.sh
	echo "Ran tests"

$(TBUILDDIR)/%.o: $(TESTDIR)/%.cpp
	@mkdir -p $(TBUILDDIR)
	@$(CXX) $(CXXTFLAGS) $(INC) -fPIC -c -o $@ $<

# My
.PRECIOUS: $(TBUILDDIR)/%.out

# My other
.PRECIOUS: $(TBUILDDIR)/%.o

$(TBUILDDIR)/%.out: $(TBUILDDIR)/%.o $(OBJECTS)
	@$(CXX) $^ -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) $(INC) -fPIC -c -o $@ $<

$(LIBDIR)/$(LIBGAME_SHARED): $(OBJECTS)
	mkdir -p $(LIBDIR)
	$(CXX) -shared -Wl,-soname,$@ -o $(LIBGAME_SHARED) $^

$(LIBDIR)/$(LIBGAME_STATIC): $(OBJECTS)
	mkdir -p $(LIBDIR)
	ar rcs $@ $^

tools: levelcheck

levelcheck: $(OBJECTS) $(TOOLDIR)/levelcheck.cpp
	mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) $(INC) -o $(BINDIR)/levelcheck $^

object:
	echo "$(SOURCES):$(SOURCES:.cpp=.o)"

cleantest:
	@$(RM) -r $(TBUILDDIR)

clean: cleantest
	$(RM) -r $(BUILDDIR) $(LIBDIR)/$(LIBGAME_SHARED) $(LIBDIR)/$(LIBGAME_STATIC)
