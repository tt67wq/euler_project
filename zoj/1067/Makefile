CC = gcc
INFILE = color.c
OUTFILE = color.o
FLAGS = -lm

build: $(INFILE)
	$(CC) $(FLAGS) $(INFILE) -o $(OUTFILE)

clean:
	rm -f *.o

rebuild: clean build
