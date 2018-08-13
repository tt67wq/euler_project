CC = gcc
INFILE = miller_rabin.c
OUTFILE = miller_rabin.o
FLAGS = -Wall

build: $(INFILE)
	$(CC) $(FLAGS) $(INFILE) -o $(OUTFILE)

clean:
	rm -f *.o

rebuild: clean build