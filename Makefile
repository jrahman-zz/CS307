.PHONY: all
.PHONY: python_container

LIBDIR		:= gamelib
EXECUTIONDIR	:= executionserver

all: python_container

$(LIBDIR)/lib/gamelib.a:
	cd $(LIBDIR) && ${MAKE} all

python_container: $(LIBDIR)/lib/gamelib.a
	mkdir -p $(EXECUTIONDIR)/python/include
	cp $(LIBDIR)/include/*.h $(EXECUTIONDIR)/python/include
	cp $(LIBDIR)/lib/libgame.a $(EXECUTIONDIR)/python/wrapper
	docker -H tcp://127.0.0.1:2375 build $(EXECUTIONDIR)/python
	

