/* 
 * set.c - CS50 'set' module
 *
 * see set.h for more information.
 *
 * Shaket Chaudhary, April 2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"
#include "memory.h"
#include <stdbool.h>

/**************** file-local global variables ****************/
/* none */

/**************** local types ****************/
typedef struct setnode {
	char *key;
	void *item;		      // pointer to data for this item
	struct setnode *next;	      // link to next node
} setnode_t;

/**************** global types ****************/
typedef struct set {
	struct setnode *head;	      // head of the list of items in set
} set_t;

/**************** global functions ****************/
/* that is, visible outside this file */
/* see set.h for comments about exported functions */

/**************** local functions ****************/
/* not visible outside this file */
static setnode_t *setnode_new(const char *key, void *item);

/**************** set_new() ****************/
set_t *
set_new(void) 
{
	set_t *set = count_malloc(sizeof(set_t));

	if (set == NULL) {
		return NULL; // error allocating set
	} else {
		// initilialize contents of set structure
		set->head = NULL;
		return set;
	}
}

/**************** set_insert() ****************/
bool 
set_insert(set_t *set, const char *key, void *item)
{
	// checking parameters
	if (set == NULL || item == NULL || key == NULL) {
		return false;
	}
	// check if the key already exists
	// if exists then stop
	else if (set_find(set,key) != NULL) {
		return false;
	} 
	else {
		// copy key string for use by the set
		setnode_t *new = setnode_new(key, item);
		if (new != NULL) {
			// add it to the list
			new->next = set->head;
			set->head = new;
			return true;
		}
		else {
			return false;
		}
	}
	
}

/**************** setnode_new ****************/
/* Allocate and initialize a setnode */
static setnode_t * // not visible outside this file
setnode_new(const char *key, void *item)
{
	setnode_t *node = count_malloc(sizeof(setnode_t));

	if (node == NULL) {
		// error allocating memory for node; return error
		return NULL;
	} else {
		node->key = count_malloc(strlen(key)*sizeof(char)+1);
		strcpy(node->key, key);
		node->item = item;
		node->next = NULL;
		return node;
	}
}

/**************** set_find() ****************/
void *
set_find(set_t *set, const char *key)
{
	if (key == NULL || set == NULL) return NULL;
	setnode_t *temp = set->head;
	while (temp != NULL) { // if the node exists, check if key is a match
		if ((strcmp(temp->key, key) == 0)) {
			return temp->item;
		}
		temp = temp->next;
	}
	return NULL; // key wasn't found
}

/**************** set_print() ****************/
void 
set_print(set_t *set, FILE *fp, void (*itemprint)(FILE *fp, const char *key, void *item))
{
	if (fp != NULL) {
		if (set != NULL) {
			fputc('{', fp);
			for (setnode_t *node = set->head; node != NULL; node = node->next) {
				// print this node
				if (itemprint != NULL) { // print the node's item
					(*itemprint)(fp, node->key, node->item);
					fputc(',', fp);
				}
			}
			fputc('}', fp);
		} else {
			fputs("(null)", fp);
		}
	}
}

/**************** set_iterate() ****************/
void 
set_iterate(set_t *set, void *arg, void (*itemfunc)(void *arg, const char *key, void *item))
{
	if (set != NULL && itemfunc != NULL) {
		// call itemfunc with arg, on each item
		for (setnode_t *node = set->head; node != NULL; node = node->next) {
			(*itemfunc)(arg, node->key, node->item);
		}
	}
}

/**************** set_delete() ****************/
void 
set_delete(set_t *set, void (*itemdelete)(void *item))
{
	if (set != NULL) {
		for (setnode_t *node = set->head; node != NULL; ) {
			if (itemdelete != NULL) { // if possible...
				(*itemdelete)(node->item); // delete node's item
			}
			setnode_t *next = node->next; // remember what comes next
			count_free(node->key);
			count_free(node); // free the node
			node = next; // and move on to next
		}

		count_free(set);
	}
}
