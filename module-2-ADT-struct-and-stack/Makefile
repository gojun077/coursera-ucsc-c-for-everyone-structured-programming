# Makefile for coursera-ucsc-C-for-everyone-structured-programming
# Created on: Sun 26 Oct 2025
# Last Updated: Sun 26 Oct 2025
CC = gcc
CFLAGS = -g -fsanitize=address -Wall -O3 -std=c23
BINDIR = bin
VALFLAGS = --tool=memcheck --leak-check=full

C_SOURCES := $(shell find . -type f -name '*.c' -not -path './$(BINDIR)/*')
C_SOURCES := $(sort $(C_SOURCES))
ALL_TARGETS := $(C_SOURCES)

.PHONY: all check-syntax clean cleanall mem test

all: $(ALL_TARGETS)

$(BINDIR):
	mkdir -p $(BINDIR)

check-syntax:
	@if [ -n "$(C_SOURCES)" ]; then \
		$(CC) $(CFLAGS) -fsyntax-only $(C_SOURCES); \
	else \
		echo "No C sources found for syntax check."; \
	fi

mem: $(BINDIR)
	@if [ -n "$(BINDIR)" ]; then \
		for file in $(BINDIR); do \
			echo "Running valgrind on $$file..."; \
			valgrind $(VALFLAGS) "./$$file" || true; \
		done; \
	else \
		echo "No C binaries found in $(BINDIR) for valgrind."; \
	fi

# Test target (placeholder - add your test commands)
test: all
	@if [ -n "$(C_SOURCES)" ]; then \
		for file in $(C_SOURCES); do \
			echo "Running splint on $$file..."; \
			splint "$$file" || true; \
		done; \
	else \
		echo "No C sources found for tests."; \
	fi

clean:
	@if [ -n "$(BINDIR)" ]; then \
		rm -f $(BINDIR); \
	fi

cleanall:
	rm -rf $(BINDIR)
