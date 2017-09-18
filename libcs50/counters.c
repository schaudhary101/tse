/* 
 * counters.c - CS50 'counters' module
 *
 * see counters.h for more information.
 *
 * Shaket Chaudhary, April 2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counters.h"
#include "memory.h"

/**************** file-local global variables ****************/
/* none */

/**************** file-local global variables ****************/
/* none */

/**************** local types ****************/
typedef struct countersnode {
	int key;
	int count;
	struct countersnode *next;	      // link to next node
} countersnode_t;

/**************** global types ****************/
typedef struct counters {
	struct countersnode *head;	      // head of the list
} counters_t;

/**************** global functions ****************/
/* that is, visible outside this file */
/* see counters.h for comments about exported functions */

/**************** local functions ****************/
/* not visible outside this file */
static countersnode_t *countersnode_new(const int key, int count);

/**************** counters_new() ****************/
counters_t *
counters_new(void) 
{
	counters_t *ctrs=count_malloc(sizeof(counters_t));

	if (ctrs == NULL) {
		return NULL; // error allocating counters
	} else {
		// initialize contents of counters structure
		ctrs->head = NULL;
		return ctrs;
	}
}

/**************** counters_add() ****************/
void 
counters_add(counters_t *ctrs, const int key)
{
	// proceed if the key isn't negative or the counter isn't null
	if (key >= 0 && ctrs != NULL) {
		// use the counter_get function to see if key exists
		int current = counters_get(ctrs, key);
		if (current == 0) { // if the key doesn't exist
			// create a new node with a value of 1
			// uses the counters_set function
			counters_set(ctrs,key,1);

		}
		// ignore if somehow a negative number is found
		else if (current >= 0) { // increment the existing value otherwise	
			current++; // new value
			// use the counters_set function to increment
			counters_set(ctrs,key,current);
		}
	}
}

/**************** countersnode_new ****************/
static countersnode_t *
countersnode_new(const int key, int count)
{
	countersnode_t *node = count_malloc(sizeof(countersnode_t));

	if (node == NULL) {
		// error allocating memory for node; return error
		return NULL;
	} else {
		// initialize with key and count and set next to null
		node->key = key;
		node->count = count;
		node->next = NULL;
		return node;
	}

}

/**************** counters_get() ****************/
int 
counters_get(counters_t *ctrs, const int key)
{
	// checking parameters
	if (ctrs == NULL || key < 0) return 0;
	// node to iterate through the linked list
	countersnode_t *temp = ctrs->head;
	while (temp != NULL) {
		// returns the value if match is found
		if (temp->key == key) {
			return temp->count;
		}
		// otherwise keeps searching
		temp = temp->next;
	}
	return 0; // key wasn't found

}

/**************** counters_set() ****************/
void
counters_set(counters_t *ctrs, const int key, int count)
{	
	// ignores if the key is negative or the counter is negative
	if (ctrs != NULL && !(key < 0) && !(count < 0)) {
		// uses the counters get function to see if the key exists already
		int current = counters_get(ctrs, key);
		if (current == 0) { // if the key doesn't exist
			// creates a new node with the given parameters
			countersnode_t *node = countersnode_new(key, count);
			if (node != NULL) {
				// add it to the list
				node->next = ctrs->head;
				ctrs->head = node;
			}	

		}
		// if the key exists, defends against negative results
		else if (current >= 0) {
			// iterate through list until node is found
			countersnode_t *node = ctrs->head;
			while (node != NULL) {
				if (node->key == key) {
					node->count = count;
					break;
				}
				node = node->next; // else keep searching for the node
			}
		}
	}
}

/**************** counters_print() ****************/
void 
counters_print(counters_t *ctrs, FILE *fp)
{
	if (fp != NULL) {
		if (ctrs != NULL) {
			fputc('{', fp);
			for (countersnode_t *node = ctrs->head; node != NULL; node = node->next) {
				fprintf(fp, "(%d:%d)", node->key, node->count);
			}
			fputc('}', fp);
			fputc('\n',fp);
		} else {
			fputs("(null)", fp);
		}
	}
}

/**************** counters_iterate() ****************/
void
counters_iterate(counters_t *ctrs, void *arg, void (*itemfunc)(void *arg, const int key, int count))
{
	if (ctrs != NULL && itemfunc != NULL) {
		// call itemfunc with arg, on each item
		for (countersnode_t *node = ctrs->head; node != NULL; node = node->next) {
			(*itemfunc)(arg, node->key, node->count);
		}
	}
}

/**************** counters_delete() ****************/
void 
counters_delete(counters_t *ctrs)
{
	if (ctrs!= NULL) {
		for (countersnode_t *node = ctrs->head; node != NULL; ) {
			countersnode_t *next = node->next; // remember what is next
			count_free(node); // free the node
			node = next; // move on to next
		}
		count_free(ctrs);
	}

#ifdef MEMTEST
  count_report(stdout, "End of counters_delete");
#endif
}
