.PHONY: all
.PHONY: clean
.PHONY: python_container

clean:

# TODO, add automated tests here
test:

python_container:
	docker build -t python python/

python_local:
	cd python/wrapper && python setup.py install
