CC = gcc
INFILE = euler46.c prime.c
OUTFILE = euler46.o
FLAGS = -Wall

build: $(INFILE)
	$(CC) $(FLAGS) $(INFILE) -o $(OUTFILE)

clean:
	rm -f *.o

rebuild: clean build
