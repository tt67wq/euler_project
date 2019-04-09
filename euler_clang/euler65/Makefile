CC = gcc
INFILE = bigint.c euler65.c
OUTFILE = euler65.o
FLAGS = -Wall

build: $(INFILE)
	$(CC) $(FLAGS) $(INFILE) -o $(OUTFILE)

clean:
	rm -f *.o

rebuild: clean build
