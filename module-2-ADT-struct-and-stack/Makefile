# Makefile for coursera-ucsc-C-for-everyone-structured-programming
# Created on: Sun 26 Oct 2025
# Last Updated: Sun 26 Oct 2025
CC = gcc
CFLAGS = -g -fsanitize=address -Wall -O3 -std=c23
BINDIR = bin
VALFLAGS = --tool=memcheck --leak-check=full

C_SOURCES := $(sort $(wildcard *.c))
BINARIES := $(patsubst %.c,$(BINDIR)/%,$(C_SOURCES))

.PHONY: all check-syntax clean cleanall mem test

all: $(BINARIES)

$(BINDIR):
	mkdir -p $(BINDIR)

$(BINDIR)/%: %.c | $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $<

check-syntax:
	@if [ -n "$(C_SOURCES)" ]; then \
		$(CC) $(CFLAGS) -fsyntax-only $(C_SOURCES); \
	else \
		echo "No C sources found for syntax check."; \
	fi

mem: $(BINARIES)
	@if [ -n "$(BINARIES)" ]; then \
		for file in $(BINARIES); do \
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
	@if [ -n "$(BINARIES)" ]; then \
		rm -f $(BINARIES); \
	fi

cleanall:
	rm -rf $(BINDIR)
