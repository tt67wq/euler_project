CC = gcc
INFILE = array.c euler_problem156.c
OUTFILE = euler_problem156.o
FLAGS = -Wall

build: $(INFILE)
	$(CC) $(FLAGS) $(INFILE) -o $(OUTFILE)

clean:
	rm -f *.o

rebuild: clean build
