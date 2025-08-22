CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
SRCDIR = .
SOURCES = ast.c bytecode.c compiler.c debug.c lexer.c parser.c vm.c
HEADERS = ast.h bytecode.h compiler.h debug.h lexer.h parser.h vm.h
OBJECTS = $(SOURCES:.c=.o)
TARGET = minic

.PHONY: all clean

all: $(TARGET)

$(TARGET): minic.c $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) minic.c $(OBJECTS) -lm

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)