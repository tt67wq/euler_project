CC = gcc
INFILE = euler347.c
OUTFILE = euler347.o
FLAGS = -Wall -lm

build: $(INFILE)
	$(CC) $(FLAGS) $(INFILE) -o $(OUTFILE)

clean:
	rm -f *.o

rebuild: clean build
