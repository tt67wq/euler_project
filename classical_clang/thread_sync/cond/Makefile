CC = clang
INFILE = cond.c
OUTFILE = cond.o
FLAGS = -Wall -lpthread

build: $(INFILE)
	$(CC) $(FLAGS) $(INFILE) -o $(OUTFILE)

clean:
	rm -f *.o

rebuild: clean build
