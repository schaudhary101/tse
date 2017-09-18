/* 
 * hashtable.c - CS50 'hashtable' module
 *
 * see hashtable.h for more information.
 *
 * Shaket Chaudhary, April 2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "set.h"
#include "memory.h"
#include "hashtable.h"
#include "jhash.h"

/**************** file-local global variables ****************/
/* none */

/**************** local types ****************/
/* none */

/**************** global types ****************/
typedef struct hashtable {
	set_t **array;
	int length;
} hashtable_t;

/**************** global functions ****************/
/* that is, visible outside this file */
/* see set.h for comments about exported functions */

/**************** local functions ****************/
/* not visible outside this file */

/**************** hashtable_new() ****************/
hashtable_t *
hashtable_new(const int num_slots)
{
	if (num_slots <= 0) {
		return NULL; // error creating hashtable
	}
	// need to allocate memory for both the table and the array
	hashtable_t *ht = count_malloc(sizeof(hashtable_t));
	ht->array = calloc(num_slots, sizeof(set_t*));

	if (ht == NULL || ht->array == NULL) {
		return NULL; // error allocating either module
	} else {
		// initialize the hashtable
		for (int i = 0; i < num_slots; i++) {
			ht->array[i] = set_new();
		}
		ht->length = num_slots;
	}
	return ht;
}

/**************** hashtable_insert() ****************/
bool 
hashtable_insert(hashtable_t *ht, const char *key, void *item)
{
	// checking parameters
	if (ht == NULL || key == NULL || item == NULL) {
		return false;
	}

	// the hash function stores at an index
	char *dest = count_malloc(strlen(key)*sizeof(char)+1);
	strcpy(dest, key);
	
	// check if the key already exists
	// if exists then stop
	if (hashtable_find(ht,dest) != NULL) {
		return false;
	} 
	unsigned long index = JenkinsHash(dest, ht->length);
	if (set_insert(ht->array[index], dest, item) == true) {
		free(dest);
		return true;
	}
	free(dest);
	return false;
}

/**************** hashtable_find() ****************/
void *
hashtable_find(hashtable_t *ht, const char *key)
{
	if (ht == NULL || key == NULL) {
		return NULL;
	}

	unsigned long index = JenkinsHash(key, ht->length);

	if (ht->array[index] == NULL) {
		return NULL;
	}
	else {
		// search the set in the index
		return set_find(ht->array[index], key);
	}
}

/**************** hashtable_print() ****************/
void 
hashtable_print(hashtable_t *ht, FILE *fp, void (*itemprint)(FILE *fp, const char *key, void *item))
{
	if (fp != NULL) {
		if (ht != NULL) {
			fputc('{', fp);
			for (int i = 0; i < ht->length; i++) {
				if (itemprint != NULL) { // print the set
					set_print(ht->array[i], fp, itemprint);
				}
			}
			fputc('}', fp);
		} else {
			fputs("(null)", fp);
		}
	}
}

/**************** hashtable_iterate() ****************/
void 
hashtable_iterate(hashtable_t *ht, void *arg, void (*itemfunc)(void *arg, const char *key, void *item))
{
	if (ht != NULL && itemfunc != NULL) {
		for (int i = 0; i < ht->length; i++) {
			// call the function on each set in the hashtable
			set_iterate(ht->array[i], arg, (*itemfunc));
		}
	}
}

/**************** hashtable_delete() ****************/
void 
hashtable_delete(hashtable_t *ht, void (*itemdelete)(void *item))
{
	if (ht != NULL) {
		for (int i = 0; i < ht->length; i++) {
			// call the function on each set in the hashtable
			set_delete(ht->array[i], (*itemdelete));
		}
		// free the hashtable
		free(ht->array);
		ht->array = NULL;
		free(ht);
		ht = NULL;
	}
}


