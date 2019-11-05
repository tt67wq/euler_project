CC = clang
INFILE = solve.c
OUTFILE = solve.o
FLAGS = -Wall

build: $(INFILE)
	$(CC) -g -fsanitize=address $(FLAGS) $(INFILE) -o $(OUTFILE)

clean:
	rm -f *.o

rebuild: clean build