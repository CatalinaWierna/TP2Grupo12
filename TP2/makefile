CC = gcc
CFLAGS = -g -Wall -pedantic-errors -std=c2x
OBJ = main.o scanner.o
TARGET = prog

.PHONY: clean run

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

main.o: main.c scanner.h
	$(CC) $(CFLAGS) -c main.c

scanner.o: scanner.c scanner.h
	$(CC) $(CFLAGS) -c scanner.c

clean:
	rm -f $(OBJ) $(TARGET)

run: $(TARGET)
	./$(TARGET)