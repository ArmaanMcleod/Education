CC = gcc
CFLAGS = -Wall -Wextra
EXE = heaptest
OBJ = main.o heap.o

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJ)

main.o: heap.h 
heap.o: heap.h

clean:
	rm -f $(OBJ) $(EXE)
