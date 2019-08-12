CC = gcc
INFILE = image_perimeters.c
OUTFILE = image_perimeters.o
FLAGS = -Wall

build: $(INFILE)
	$(CC) $(FLAGS) $(INFILE) -o $(OUTFILE)

clean:
	rm -f *.o

rebuild: clean build