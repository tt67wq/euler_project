CC = gcc
INFILE = euler62.c hash_table.c item.c
OUTFILE = euler62.o
FLAGS = -Wall

build: $(INFILE)
	$(CC) $(FLAGS) $(INFILE) -o $(OUTFILE)

clean:
	rm -f *.o

rebuild: clean build
