CC = gcc
INFILE = main.c
OUTFILE = main.o
FLAGS = -g -Wall -fsanitize=address

build: $(INFILE)
	$(CC) $(FLAGS) $(INFILE) -o $(OUTFILE)

run: $(INFILE)
	$(CC) $(FLAGS) $(INFILE) -o $(OUTFILE)
	./$(OUTFILE)

clean:
	rm -f *.o

rebuild: clean build
