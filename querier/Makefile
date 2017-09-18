# Makefile for indexer.c and indextest.c
# Shaket Chaudhary, May 2017

L = ../libcs50
C = ../common

CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb -I$C -I$L
PROG = querier
OBJS = querier.o
LLIBS = $C/common.a $L/libcs50.a-Linux
MAKE = make

.PHONY: all clean

all: $(PROG)

#executable depends on object files
$(PROG): $(OBJS) $(LLIBS)
	$(CC) $(CFLAGS) $(OBJS) $(LLIBS) -o $(PROG)


# object files depend on include files
querier.o: $L/hashtable.h $L/counters.h  $L/file.h $L/webpage.h $C/index.h $C/pagedir.h


clean:
	rm -f $(PROG)
	rm -f *~ *.o
	rm -rf *.dSYM