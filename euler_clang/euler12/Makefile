CC = gcc
INFILE = euler_problem12.c hashmap.c
OUTFILE = euler_problem12.o
FLAGS = -Wall

build: $(INFILE)
	$(CC) $(FLAGS) $(INFILE) -o $(OUTFILE)

clean:
	rm -f *.o

rebuild: clean build
