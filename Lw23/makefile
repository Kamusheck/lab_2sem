CC = gcc
CFLAGS = -Wall -Wextra -g
VALGRIND = valgrind --leak-check=full --track-origins=yes
DATA_FILE = tree_data.txt

all: tree_program

tree_program: tree_program.o
	$(CC) $(CFLAGS) -o tree_program tree_program.o

tree_program.o: tree_program.c
	$(CC) $(CFLAGS) -c tree_program.c

clean:
	rm -f *.o tree_program $(DATA_FILE)

valgrind: all
	$(VALGRIND) ./tree_program

.PHONY: all clean valgrind