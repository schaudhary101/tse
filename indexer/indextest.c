/* 
 *  indextest.c
 *  Shaket Chaudhary, May 2017
 *  indextest.c is a program for testing indexer.c
 *  The program loads from a file into a data structure
 *  and then writes the index into a new file and compares the two.
 */

#include <stdio.h>
#include <stdlib.h>
#include "hashtable.h"
#include "index.h"

int main(int argc, char *argv[])
{
	FILE *fp;
	hashtable_t *ht = hashtable_new(500);
	// checking arguments
	if (argc != 3) {
		fprintf(stderr, "usage: ./indextest oldIndexFilename newIndexFilename\n");
		exit(1);
	}
	// checking if file is readable
	fp = fopen(argv[1], "r");
	if (fp == NULL) {
		fprintf(stderr, "oldIndexFilename could not be opened");
		exit(2);
	}
	fclose(fp);
	// load the index from the first file
	index_load(argv[1], ht);
	// save the index into a second file
	index_save(argv[2], ht);
	// cleanup
	hashtable_delete(ht, hash_delete);
}
