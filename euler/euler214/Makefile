CC = gcc
INFILE = euler214.c
OUTFILE = euler214.o
FLAGS = -lm

build: $(INFILE)
	$(CC) $(FLAGS) $(INFILE) -o $(OUTFILE)

clean:
	rm -f *.o

rebuild: clean build
