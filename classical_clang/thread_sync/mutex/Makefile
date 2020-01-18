CC = clang
INFILE = mutex.c
OUTFILE = mutex.o
FLAGS = -Wall -lpthread

build: $(INFILE)
	$(CC) $(FLAGS) $(INFILE) -o $(OUTFILE)

clean:
	rm -f *.o

rebuild: clean build
