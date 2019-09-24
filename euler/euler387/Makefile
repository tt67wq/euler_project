CC = gcc
INFILE = euler387.c
OUTFILE = euler387.o
FLAGS = -Wall -lm

build: $(INFILE)
	$(CC) $(FLAGS) $(INFILE) -o $(OUTFILE)

clean:
	rm -f *.o

rebuild: clean build
