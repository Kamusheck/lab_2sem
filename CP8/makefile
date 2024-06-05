CC = gcc
CFLAGS = -Wall -pedantic -std=c99
TARGET = main
SRC = main.c

all: compile run clean

compile:
	@$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

run:
	./$(TARGET)

valgrind: compile run_valgrind clean

run_valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET)

clean:
	@rm -f $(TARGET)