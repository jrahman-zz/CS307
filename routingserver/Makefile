.PHONY: all
.PHONY: clean
.PHONY: run
.PHONY: test
.PHONY: compile
.PHONY: reload

all: compile

compile: tugboat
	cd server && sbt compile

reload:
	cd server && sbt reload

clean:
	cd server && sbt clean

test:
	test/test.py

run:
	cd server && sbt run

tugboat:
	git clone https://github.com/softprops/tugboat.git tugboat
	cd tugboat && git checkout 70c102e29abd3f88587c61fa3ae2791c5632d760 && git reset --hard
	cd tugboat && sbt publish-local

