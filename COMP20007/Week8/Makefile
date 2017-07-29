CC = gcc
CFLAGS = -Wall
EXE = hashtable
OBJ = main.o hashtbl.o strhash.o

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJ)

main.o: strhash.h
hashtbl.o: strhash.h hashtbl.h
strhash.o: strhash.h

clean:
	rm -f $(OBJ) $(EXE)