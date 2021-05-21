CC = gcc
INFILE = phi_sieve.c
OUTFILE = phi_sieve.o
FLAGS = -Wall

build: $(INFILE)
	$(CC) $(FLAGS) $(INFILE) -o $(OUTFILE)

clean:
	rm -f *.o

rebuild: clean build