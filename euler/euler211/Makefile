CC = gcc
INFILE = euler211.c
OUTFILE = euler211.o
FLAGS = -lm

build: $(INFILE)
	$(CC) $(FLAGS) $(INFILE) -o $(OUTFILE)

clean:
	rm -f *.o

rebuild: clean build
