.PHONY: all
.PHONY: clean
.PHONY: python_container

LIBDIR		:= gamelib
EXECUTIONDIR	:= executionserver

all: python_container

clean:
	cd $(LIBDIR) && ${MAKE} clean

$(LIBDIR)/lib/gamelib.a:
	cd $(LIBDIR) && ${MAKE} all

python_container: $(LIBDIR)/lib/gamelib.a
	mkdir -p $(EXECUTIONDIR)/python/include
	cp -r $(LIBDIR)/include/* $(EXECUTIONDIR)/python/include
	cp $(LIBDIR)/lib/libgame.a $(EXECUTIONDIR)/python/wrapper
	docker build -t python $(EXECUTIONDIR)/python
	

