# Makefile de exemplo (Manual do GNU Make)
     
CFLAGS = -Wall -Wextra -g -std=c99 # flags de compilacao
CC = gcc

all: tp3.o racional.o utils.o
	$(CC) -o tp3 tp3.o racional.o utils.o

racional.o: racional.c racional.h
	$(CC) -c $(CFLAGS) racional.c

utils.o: utils.c utils.h
	$(CC) -c $(CFLAGS) utils.c

tp3.o: tp3.c racional.h
	$(CC) -c $(CFLAGS) tp3.c

clean:
	rm -f *.o *~ tp3
