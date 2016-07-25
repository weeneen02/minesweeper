export PATH := src/

CC=gcc
CFLAGS=-lm
DEPS = mine.h

#%.o: %.c $(DEPS)
#	$(CC) -c $@ $< $(CFLAGS)

mine: mine.o mines_functions.o
	$(CC) -o mine mine.o mines_functions.o $(CFLAGS)

mine.o: mine.c mines_functions.c
	$(CC) -c mine.c mines_functions.c

mines_functions.o: mine.c mines_functions.c
	$(CC) -c mine.c mines_functions.c

.PHONY: clean
	
clean:
	rm mine.o mines_functions.o
