.PHONY: all
.PHONY: clean
.PHONY: python_container

LIBDIR		:= gamelib
EXECUTIONDIR	:= executionserver

all: python_container

test:
	@cd gamelib && ${MAKE} test
	cd gamelib && ${MAKE} test

clean:
	cd $(LIBDIR) && ${MAKE} clean
	cd ${EXECUTIONDIR} && ${MAKE} clean

$(LIBDIR)/lib/gamelib.a:
	cd $(LIBDIR) && ${MAKE} all

local_build: $(LIBDIR)/lib/gamelib.a
	mkdir -p $(EXECUTIONDIR)/python/include
	cp -r $(LIBDIR)/include/* $(EXECUTIONDIR)/python/include
	cp $(LIBDIR)/lib/libgame.a $(EXECUTIONDIR)/python/wrapper
	cd ${EXECUTIONDIR} && ${MAKE} python_local

python_container: $(LIBDIR)/lib/gamelib.a
	mkdir -p $(EXECUTIONDIR)/python/include
	cp -r $(LIBDIR)/include/* $(EXECUTIONDIR)/python/include
	cp $(LIBDIR)/lib/libgame.a $(EXECUTIONDIR)/python/wrapper
	cd ${EXECUTIONDIR} && ${MAKE} python_container
	

