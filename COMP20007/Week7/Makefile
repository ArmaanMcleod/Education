CC = gcc
CFLAGS = -Wall
EXE = hash
OBJ = main.o strhash.o

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJ)

main.o: strhash.h 
strhash.o: strhash.h

clean:
	rm -f $(OBJ) $(EXE)