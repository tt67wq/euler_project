CC = gcc
INFILE = euler_problem37.c prime.c
OUTFILE = euler_problem37.o
FLAGS = -Wall

build: $(INFILE)
	$(CC) $(FLAGS) $(INFILE) -o $(OUTFILE)

clean:
	rm -f *.o

rebuild: clean build
