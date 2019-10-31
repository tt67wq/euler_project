CC = clang
INFILE = solve.c
OUTFILE = solve.o
FLAGS = -Wall

build: $(INFILE)
	$(CC) $(FLAGS) $(INFILE) -lm -o $(OUTFILE)

clean:
	rm -f *.o

rebuild: clean build
