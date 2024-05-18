all: compile run clean

compile:
	@gcc main.c -Wall -pedantic -std=c99 -o main

run:
	./main

valgrind: compile run_valgrind clean

run_valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./main

clean:
	@rm -f main