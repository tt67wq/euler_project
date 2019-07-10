CC = gcc
INFILE = crashing_ballon.c
OUTFILE = crashing_ballon.o
FLAGS = -Wall

build: $(INFILE)
	$(CC) $(FLAGS) $(INFILE) -o $(OUTFILE)

clean:
	rm -f *.o

rebuild: clean build