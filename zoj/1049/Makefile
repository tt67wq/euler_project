CC = gcc
INFILE = houseboat.c
OUTFILE = houseboat.o
FLAGS = -lm

build: $(INFILE)
	$(CC) $(FLAGS) $(INFILE) -o $(OUTFILE)

clean:
	rm -f *.o

rebuild: clean build
