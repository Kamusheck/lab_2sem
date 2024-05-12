all: compile run

compile:
	@gcc main.c structure.h -Wall -pedantic -std=c99 -o main

run:
	./main

valgrind: compile run_valgrind

run_valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./main

