L = ../libcs50

OBJS = index.o pagedir.o
LIB = common.a

# add -DNOSLEEP to disable the automatic sleep after web-page fetches
#               (students, please do not use -DNOSLEEP!)
# add -DMEMTEST for memory tracking report in indexer
# (and run `make clean; make` whenever you change this)
FLAGS = # -DNOSLEEP # -DMEMTEST 

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(FLAGS) -I$L
CC = gcc
MAKE = make
LLIBS = $L/libcs50.a-Linux

# Build the library by archiving object files
$(LIB): $(OBJS) $(LLIBS)
	ar cr $(LIB) $(OBJS) $(LLIBS)

# Dependencies: object files depend on header files
pagedir.o: $L/webpage.h $L/file.h pagedir.h
index.o: $L/hashtable.h $L/counters.h $L/file.h $L/webpage.h pagedir.h

.PHONY: clean sourcelist

# list all the sources and docs in this directory.
sourcelist: Makefile *.md *.c *.h
	@echo $^

# clean up after our compilation
clean:
	rm -f $(LIB) *~ *.o
