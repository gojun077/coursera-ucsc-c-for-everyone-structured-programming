# Makefile for coursera-ucsc-C-for-everyone-structured-programming
# Created on: Sun 26 Oct 2025
# Last Updated: Sun 26 Oct 2025
CC = gcc
CFLAGS = -g -fsanitize=address -Wall -O3 -std=c23
BINDIR = bin
VALFLAGS = --tool=memcheck --leak-check=full

C_RELATIVE := $(patsubst ./%,%,$(C_SOURCES))
C_BINARIES := $(addprefix $(BINDIR)/,$(C_RELATIVE:.c=))
C_SOURCES := $(shell find . -type f -name '*.c' -not -path './$(BINDIR)/*')
C_SOURCES := $(sort $(C_SOURCES))
ALL_TARGETS := $(C_BINARIES)

.PHONY: all all-auto check-syntax clean cleanall java mem test

all: $(ALL_TARGETS)

$(BINDIR):
	mkdir -p $(BINDIR)

$(BINDIR)/%: %.c | $(BINDIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ $<

check-syntax:
	@if [ -n "$(C_SOURCES)" ]; then \
		$(CC) $(CFLAGS) -fsyntax-only $(C_SOURCES); \
	else \
		echo "No C sources found for syntax check."; \
	fi

mem: $(C_BINARIES)
	@if [ -n "$(C_BINARIES)" ]; then \
		for file in $(C_BINARIES); do \
			echo "Running valgrind on $$file..."; \
			valgrind $(VALFLAGS) "./$$file" || true; \
		done; \
	else \
		echo "No C binaries found in $(BINDIR) for valgrind."; \
	fi

# Test target (placeholder - add your test commands)
test: $(C_BINARIES)
	@if [ -n "$(C_SOURCES)" ]; then \
		for file in $(C_SOURCES); do \
			echo "Running splint on $$file..."; \
			splint "$$file" || true; \
		done; \
	else \
		echo "No C sources found for tests."; \
	fi

clean:
	@if [ -n "$(C_BINARIES)" ]; then \
		rm -f $(C_BINARIES); \
	fi

cleanall:
	rm -rf $(BINDIR)
