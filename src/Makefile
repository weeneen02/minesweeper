
CC=gcc
CFLAGS=
DEPS = mine.h
OBJS = mine.o mines_functions.o
SRCS = mine.c mines_functions.c

all: mine clean

mine: $(OBJS)
	$(CC) -o mine $(OBJS)

%.o: %.c $(DEPS)
	$(CC) -c $(SRCS)


.PHONY: make clean
clean:
	rm mine.o mines_functions.o
