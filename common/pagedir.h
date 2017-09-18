/*
 * pagedir.h
 * Shaket Chaudhary, May 2017
 * A header file for pagedir.c, listing the functions for use in TSE
 */

#ifndef __INDEX_H
#define __INDEX_H

#include <stdio.h>
#include "webpage.h"

/**************** functions ****************/

// creates a webpage
bool
webpage_save(webpage_t *page, char *pageDirectory, int id);

// creates a webpage module from information in a file
webpage_t*
webpage_build(FILE *fp);

#endif // __INDEX_H