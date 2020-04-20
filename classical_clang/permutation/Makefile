CC = gcc
INFILE = permutation_with_repeat.c
OUTFILE = permutation.o
FLAGS = -Wall

build: $(INFILE)
	$(CC) $(FLAGS) $(INFILE) -o $(OUTFILE)

clean:
	rm -f *.o

rebuild: clean build
