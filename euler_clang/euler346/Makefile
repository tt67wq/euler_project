CC = gcc
INFILE = euler346.c
OUTFILE = euler346.o
FLAGS = -Wall -lm

build: $(INFILE)
	$(CC) $(FLAGS) $(INFILE) -o $(OUTFILE)

clean:
	rm -f *.o

rebuild: clean build
