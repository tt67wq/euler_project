CC = clang
INFILE = main.c
OUTFILE = main.o
FLAGS = -Wall -lm -fsanitize=address

build: $(INFILE)
	$(CC) $(FLAGS) $(INFILE) -o $(OUTFILE)

run: $(INFILE)
	$(CC) $(FLAGS) $(INFILE) -o $(OUTFILE)
	./$(OUTFILE)

clean:
	rm -f *.o

rebuild: clean build