CC = gcc
INFILE = stern_brocot.c
OUTFILE = stern_brocot.o
FLAGS = -Wall

build: $(INFILE)
	$(CC) $(FLAGS) $(INFILE) -o $(OUTFILE)

clean:
	rm -f *.o

rebuild: clean build