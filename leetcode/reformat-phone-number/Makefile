CC = gcc
INFILE = main.c
OUTFILE = main.o
INCLUDE = /home/tt67wq/Project/euler_project/include
FLAGS = -g -Wall -I$(INCLUDE) -fsanitize=address

build: $(INFILE)
	$(CC) $(FLAGS) $(INFILE) -o $(OUTFILE)

run: $(INFILE)
	$(CC) $(FLAGS) $(INFILE) -o $(OUTFILE)
	./$(OUTFILE)

clean:
	rm -f *.o

rebuild: clean build