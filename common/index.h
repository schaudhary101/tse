/*
 * index.h
 * Shaket Chaudhary, May 2017
 * A header file for index.c, listing the functions for use in TSE
 */

#ifndef __INDEX_H
#define __INDEX_H

#include <stdio.h>
#include <hashtable.h>

/**************** functions ****************/

// builds a word to count in document mapping
void 
index_build(char *directory, hashtable_t *index);

// reads from a file and loads an index
void 
index_load(char *filename, hashtable_t *ht);

// writes the index to a file
void 
index_save(const char *filename, hashtable_t *ht);

// deletes the hashtable of counters
void 
hash_delete(void *item);

#endif // __INDEX_H