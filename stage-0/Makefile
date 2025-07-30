CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g -I./include
LDFLAGS = -lm

SRCDIR = src
BUILDDIR = build
TARGET = $(BUILDDIR)/minic

SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(SOURCES:$(SRCDIR)/%.c=$(BUILDDIR)/%.o)

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.c | $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

clean:
	rm -rf $(BUILDDIR)

.PHONY: clean