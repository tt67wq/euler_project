CC = gcc
INFILE = bode_plot.c
OUTFILE = bode_plot.o
FLAGS = -Wall -lm

build: $(INFILE)
	$(CC) $(FLAGS) $(INFILE) -o $(OUTFILE)

clean:
	rm -f *.o

rebuild: clean build
