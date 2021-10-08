.PHONY = all clean
TARGET = main
SOURCES = $(wildcard *.c)
OPT = -O2 -Wall
CC = gcc
CFLAGS = $(OPT) -lm
all: $(SOURCES)
	$(CC) -o $(TARGET) $^ $(CFLAGS)
clean:
	rm -rf *.o $(TARGET)
