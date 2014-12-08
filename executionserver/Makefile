.PHONY: all
.PHONY: clean
.PHONY: python_container

clean:
	rm -r python/wrapper/build
	rm python/wrapper/libgame.a
	rm -r python/include

test:

python_container:
	docker build -t python python/

python_local:
	cd python/wrapper && python setup.py build && python setup.py install
