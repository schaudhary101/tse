# Makefile for the "crawler" program
#
# Shaket Chaudhary - April 2017

L = ../libcs50

CC=gcc
CFLAGS=-Wall -pedantic -std=c11 -ggdb -I$L
PROG = crawler
OBJS = crawler.o
LIBS = -lm -lcurl -lcs50
LLIBS = $L/libcs50.a
MAKE = make

.PHONY: all clean

all: $(PROG)

# executable depends on object files
$(PROG): $(OBJS) 
	$(CC) $(CFLAGS) -L$(L) -I$(L) $(OBJS) $(LLIBS) $(LIBS) -o $(PROG)

# object files depend on include files
crawler.o: $L/bag.h $L/hashtable.h $L/webpage.h
	$(CC) $(CFLAGS) -I$(L) -c crawler.c

clean:
	rm -f $(PROG)
	rm -f *~ *.o
	rm -rf *.dSYM
