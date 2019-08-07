CC = gcc
INFILE = trees_made_to_order.c
OUTFILE = trees_made_to_order.o
FLAGS = -Wall

build: $(INFILE)
	$(CC) $(FLAGS) $(INFILE) -o $(OUTFILE)

clean:
	rm -f *.o

rebuild: clean build