/* 
 *  index.c
 *  Shaket Chaudhary, May 2017
 *  index.c contains functions for building the index. The index will be
 *  implemented as a hashtable of counters. Additional functions also help
 *  to write the index to a file.
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "hashtable.h"
#include "counters.h"
#include "file.h"
#include "webpage.h"
#include "pagedir.h"

// helper methods for writing to a file
static void simpleprint(void *arg, const char *key, void *item);
static void countersprint(void *arg, const int key, int item);

// function for building the index
void 
index_build(char *directory, hashtable_t *ht)
{
	FILE *fp;
	char crawlerFile[100];
	// start with document 1 and proceed until no more documents left
	int ID = 1;
	sprintf(crawlerFile, "%s/%d", directory, ID);

	// for getting next word
	char *result;
	webpage_t *page;

	fp = fopen(crawlerFile, "r");
	while (fp != NULL) {
		// retrieve all words in a page
		page = webpage_build(fp);
		int pos = 0;
		while ((pos = webpage_getNextWord(page, pos, &result)) > 0) {
			if (strlen(result) >= 3){
				// normalizing the word
				for (int i = 0; i < strlen(result); i++) {
					result[i] = tolower(result[i]);
				}
				// if the word is in the index increment the counter
				if ((hashtable_find(ht, result)) != NULL) {
					counters_add(hashtable_find(ht, result), ID);
				}
				// otherwise create a new counter module
				else {
					counters_t *ctr = counters_new();
					counters_add(ctr, ID);
					hashtable_insert(ht, result, ctr);
				}
			}
      		free(result);
 		}
		// open the next file in the directory
		webpage_delete(page);
		fclose(fp);
		ID++;
		sprintf(crawlerFile, "%s/%d", directory, ID);
		fp = fopen(crawlerFile, "r");
	}
}

// function for creating an index from a file
void 
index_load(char *filename, hashtable_t *ht)
{
	FILE *fp;
	// variables for loading an index
	char *word;
	int ID;
	int count;
	// reading from the file created by indexer
	fp = fopen(filename, "r");
	word = readwordp(fp);
	while (word != NULL) {
		// scan for all IDs and counts
		counters_t *ctrs = counters_new();
		while (fscanf(fp, "%d %d", &ID, &count) == 2) {
			counters_set(ctrs, ID, count);
		}
		hashtable_insert(ht, word, ctrs);
		free(word);
		word = readwordp(fp);
	}
	fclose(fp);
}

// function to write the index to the file
void 
index_save(char *filename, hashtable_t *ht) 
{
	FILE *fp;
	fp = fopen(filename, "w");
	hashtable_iterate(ht, fp, simpleprint);
	fclose(fp);
}

// function to iterate through counters
static void 
simpleprint(void *arg, const char *key, void *item)
{
	FILE *fp = arg;
	counters_t *ctrs = item;
	bool print = true;
	if (fp != NULL && key != NULL && print == true) {
		fprintf(fp, "%s ", key);
		counters_iterate(ctrs, fp, countersprint);
		fprintf(fp, "\n");
	}
}

// printing function for counters
static void 
countersprint(void *arg, const int key, int item)
{
	FILE *fp = arg;
	if (fp != NULL) {
		fprintf(fp, "%d ", key);
		fprintf(fp, "%d ", item);
	}
}

// function for freeing up the hashtable
void hash_delete(void *item)
{
	counters_t *ctrs = item;
	counters_delete(ctrs);
}

