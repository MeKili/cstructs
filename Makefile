# cstructs — build and test a small C data-structures library.
# Windows note: build via WSL/Linux; needs a C compiler + make (preinstalled on CI).

CC ?= cc
CFLAGS ?= -std=c11 -Wall -Wextra -Werror -Iinclude -O2
SANFLAGS = -fsanitize=address,undefined -fno-omit-frame-pointer -g

SRC := $(wildcard src/*.c)
TESTS := $(wildcard tests/test_*.c)
BINS := $(patsubst tests/%.c,build/%,$(TESTS))
HEADERS := $(wildcard include/cstructs/*.h)

.PHONY: all test sanitize format format-check clean

all: test

build:
	mkdir -p build

# Each tests/test_*.c is a standalone program linked against every library source.
build/%: tests/%.c $(SRC) | build
	$(CC) $(CFLAGS) $< $(SRC) -o $@

test: $(BINS)
	@for t in $(BINS); do echo "== $$t =="; ./$$t || exit 1; done
	@echo "All tests passed."

sanitize: | build
	@for t in $(TESTS); do \
		out=build/san_$$(basename $$t .c); \
		echo "== sanitize $$t =="; \
		$(CC) $(CFLAGS) $(SANFLAGS) $$t $(SRC) -o $$out && ./$$out || exit 1; \
	done
	@echo "Sanitizer run passed."

format:
	clang-format -i $(SRC) $(TESTS) $(HEADERS)

format-check:
	clang-format --dry-run --Werror $(SRC) $(TESTS) $(HEADERS)

clean:
	rm -rf build
