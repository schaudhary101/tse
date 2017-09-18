/* 
 * indexer.c
 * Shaket Chaudhary, May 2017 
 * Indexer reads the documents in the pageDirectory output by the 
 * crawler and builds an inverted index mapping from words to documents
 * and writes that index to a file. The querier will read the index 
 * and use it answer queries
 */

#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>
#include <stdbool.h>
#include "hashtable.h"
#include "counters.h"
#include "file.h"
#include "webpage.h"
#include "index.h"
#include "pagedir.h"

int main (int argc, char *argv[])
{	
	DIR *dp;
	FILE *fp;
	hashtable_t *ht;
	char buffer[100];

	// check for correct amount of arguments
	if (argc != 3) {
		fprintf(stderr, "usage: ./indexer pageDirectory indexFilename\n");
		exit(1);
	}

	// check if pageDirectory is the directory produced by crawler
	dp = opendir(argv[1]);
	if (dp == NULL) {
		fprintf(stderr, "usage: pageDirectory doesn't exist\n");
		exit(2);
	}
	else {
		sprintf(buffer, "%s/%s", argv[1], ".crawler");
		fp = fopen(buffer, "r");
		if (fp == NULL) {
			fprintf(stderr, "pageDirectory isn't created by crawler\n");
			exit(2);
		}
		fclose(fp);
	}
	closedir(dp);
	
	// creates indexFilename, if it already exists it is overwritten
	fp = fopen(argv[2], "w");
	if (fp == NULL) {
		fprintf(stderr, "indexFilename could not be created\n");
		exit(3);
	}
	fclose(fp);

	ht = hashtable_new(500);
	// build the index from a crawler directory and its files
	index_build(argv[1], ht); 
	// save the index to a file
	index_save(argv[2], ht);
	// cleanup
	hashtable_delete(ht, hash_delete);
	exit(0);
}

