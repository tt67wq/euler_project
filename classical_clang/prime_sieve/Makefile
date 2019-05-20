CC = gcc
INFILE = prime_sieve.c
OUTFILE = prime_sieve.o
FLAGS = -Wall

build: $(INFILE)
	$(CC) $(FLAGS) $(INFILE) -o $(OUTFILE)

clean:
	rm -f *.o

rebuild: clean build