# src/Makefile
CC=gcc
CFLAGS=-Wall -Wextra -std=c99

TARGET=minesweeper
TEST_TARGET=tests

SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): main.o board.o game.o utils.o
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

test: tests.o board.o game.o utils.o
	$(CC) $(CFLAGS) -o $(TEST_TARGET) $^
	./$(TEST_TARGET)

clean:
	rm -f $(OBJS) $(TARGET) $(TEST_TARGET)

.PHONY: all test clean
