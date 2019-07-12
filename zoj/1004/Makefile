CC = gcc
INFILE = anagrams.c
OUTFILE = anagrams.o
FLAGS = -Wall

build: $(INFILE)
	$(CC) $(FLAGS) $(INFILE) -o $(OUTFILE)

clean:
	rm -f *.o

rebuild: clean build