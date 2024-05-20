BUILD_REL=../$(BUILD)

CC=gcc
CFLAGS=-Wall -Wextra -g -std=gnu99 -I$(BUILD_REL)/include/
LDFLAGS=-L$(BUILD_REL)/lib -lncurses -lcursel

TARGETS=$(BUILD_REL)/bin/nav-example

.PHONY: all
all: $(TARGETS)

$(BUILD_REL)/bin/nav-example: src/nav-example.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

# Formatting
FORMAT=clang-format
FORMAT_CHECK_FLAGS=--dry-run --Werror
FORMAT_FIX_FLAGS=-i

FORMAT_FILES=$(shell find src -type f)

.PHONY: checkformat
checkformat:
	$(FORMAT) $(FORMAT_CHECK_FLAGS) $(FORMAT_FILES)

.PHONY: format
format:
	$(FORMAT) $(FORMAT_FIX_FLAGS) $(FORMAT_FILES)
