# Makefile to build game library.

.PHONY: clean
.PHONY: cleantest
.PHONY: test

CXX	 	:= g++
CXXFLAGS 	:= -Wall -pedantic -std=c++11 -g
SRCDIR 	 	:= src
TESTDIR  	:= test
BUILDDIR 	:= build
LIBDIR		:= lib
TBUILDDIR 	:= test_build
SOURCES 	:= $(shell find $(SRCDIR) -type f -name *.cpp)
OBJECTS 	:= $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.cpp=.o))
TESTS		:= $(shell find $(TESTDIR) -type f -name *.cpp)
TESTBIN 	:= $(patsubst $(TESTDIR)/%,$(TBUILDDIR)/%,$(TESTS:.cpp=.out))


INC := -I include
LIBGAME_SHARED=libgame.so
LIBGAME_STATIC=libgame.a

all: $(LIBDIR)/$(LIBGAME_STATIC) $(LIBDIR)/$(LIBGAME_SHARED)

test: $(TESTBIN)
	@echo "Ran tests"

$(TBUILDDIR)/%.o: $(TESTDIR)/%.cpp
	@mkdir -p $(TBUILDDIR)
	@echo " $(CXX) $(CXXFLAGS) $(INC) -fPIC -c -o $@ $<"; $(CXX) $(CXXFLAGS) $(INC) -fPIC -c -o $@ $<

# My
.PRECIOUS: $(TBUILDDIR)/%.out

$(TBUILDDIR)/%.out: $(TBUILDDIR)/%.o $(OBJECTS)
	@$(CXX) $^ -o $@
	@$@

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(BUILDDIR)
	@echo " $(CXX) $(CXXFLAGS) $(INC) -fPIC -c -o $@ $<"; $(CXX) $(CXXFLAGS) $(INC) -fPIC -c -o $@ $<

$(LIBDIR)/$(LIBGAME_SHARED): $(OBJECTS)
	$(CXX) -shared -Wl,-soname,$@ -o $(LIBGAME_SHARED) $^

$(LIBDIR)/$(LIBGAME_STATIC): $(OBJECTS)
	@mkdir -p $(LIBDIR)
	@echo "ar rcs $@ $^"; ar rcs $@ $^

object:
	echo "$(SOURCES):$(SOURCES:.cpp=.o)"

cleantest:
	@echo "$(RM) -r $(TBUILDDIR)"; $(RM) -r $(TBUILDDIR)

clean: cleantest
	@echo "$(RM) -r $(BUILDDIR) $(LIBDIR)/$(LIBGAME_STATIC) $(LIBDIR)/$(LIBGAME_SHARED)"; $(RM) -r $(BUILDDIR) $(LIBDIR)/$(LIBGAME_SHARED) $(LIBDIR)/$(LIBGAME_STATIC)
