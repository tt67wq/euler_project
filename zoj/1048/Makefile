CC = gcc
INFILE = financial_management.c
OUTFILE = financial_management.o
FLAGS = -Wall

build: $(INFILE)
	$(CC) $(FLAGS) $(INFILE) -o $(OUTFILE)

clean:
	rm -f *.o

rebuild: clean build