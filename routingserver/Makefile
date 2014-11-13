.PHONY: all
.PHONY: clean
.PHONY: run
.PHONY: test
.PHONY: compile
.PHONY: reload

all: compile

compile:
	cd server && sbt compile

reload:
	cd server && sbt reload

clean:
	cd server && sbt clean

test:
	test/test.py

run:
	cd server && sbt run

