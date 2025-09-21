EXEC = tema2
CC = gcc
CFLAGS = -Wall -std=c17 -O0 -g
SRC = tema2.c binary_tree.c min_heap.c task1.c task2.c task3.c task4.c

build: $(EXEC)

$(EXEC): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

run: build
	./$(EXEC)

clean:
	rm -f $(EXEC)

.PHONY: build run clean
