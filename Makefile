CC ?= gcc
CFLAGS ?= -std=c99 -Wall -Wextra -pedantic -O2

all: bin/binpacking

bin/binpacking: src/main.c src/binpacking.c src/binpacking.h
	@mkdir -p bin
	$(CC) $(CFLAGS) -o $@ src/main.c src/binpacking.c

bin/test_binpacking: tests/test_binpacking.c src/binpacking.c src/binpacking.h
	@mkdir -p bin
	$(CC) $(CFLAGS) -o $@ tests/test_binpacking.c src/binpacking.c

test: bin/test_binpacking
	./bin/test_binpacking

clean:
	rm -rf bin

.PHONY: all test clean
