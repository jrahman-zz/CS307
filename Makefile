.PHONY: all
.PHONY: clean
.PHONY: python_container
.PHONY: routing_server

LIBDIR		:= gamelib
EXECUTIONDIR	:= executionserver
ROUTINGDIR	:= routingserver

all: python_container routing_server

test:
	@cd $(LIBDIR) && ${MAKE} test
	@cd $(EXECUTIONDIR) && ${MAKE} test
	@cd $(ROUTINGDIR) && ${MAKE} test

clean:
	cd $(LIBDIR) && ${MAKE} clean
	cd ${EXECUTIONDIR} && ${MAKE} clean
	cd $(ROUTINGDIR) && ${MAKE} clean

$(LIBDIR)/lib/gamelib.a:
	cd $(LIBDIR) && ${MAKE} all

local_build: $(LIBDIR)/lib/gamelib.a
	mkdir -p $(EXECUTIONDIR)/python/include
	cp -r $(LIBDIR)/include/* $(EXECUTIONDIR)/python/include
	cp $(LIBDIR)/lib/libgame.a $(EXECUTIONDIR)/python/wrapper
	cd ${EXECUTIONDIR} && ${MAKE} python_local

routing_server:
	cd $(ROUTINGDIR) && make

python_container: $(LIBDIR)/lib/gamelib.a
	mkdir -p $(EXECUTIONDIR)/python/include
	cp -r $(LIBDIR)/include/* $(EXECUTIONDIR)/python/include
	cp $(LIBDIR)/lib/libgame.a $(EXECUTIONDIR)/python/wrapper
	cd ${EXECUTIONDIR} && ${MAKE} python_container
	

