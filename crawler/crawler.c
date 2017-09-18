/*
 *	Shaket Chaudhary	
 *	"crawler.c"
 *	April 2017
 *	TSE crawler is a standalone program that crawls the web and retrieves
 *	webpages starting from a "seed" URL. It parses the seed webpage, extracts
 *	any embedded URLs, then retrieves each of those pages, recursively, but
 *	its exploration to a given "depth".
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include "bag.h"
#include "hashtable.h"
#include "webpage.h"

void crawler(char *seedURL, char *pageDirectory, int maxDepth);
bool webpage_save(webpage_t *page, char *pageDirectory, int id);

int main(int argc, char *argv[])
{

	FILE *fp;
	DIR *dp;
	// checking for arguments
	if (argc != 4) {
		fprintf(stderr, "usage: crawler [seedURL] [pageDirectory] [maxDepth]\n");
		exit(1);
	}

	// checks if a valid URL was inputted
	if (IsInternalURL(argv[1]) == false) {
		fprintf(stderr, "usage: [seedURL] is not valid\n");
		exit(2);
	}

	// saving the page directory into a character array

	dp = opendir(argv[2]);
	if (dp == NULL) {
		fprintf(stderr, "usage: [pageDirectory] doesn't exist\n");
		exit(3);
	}
	else {
		// see if the directory is writable
		char buffer[100];
		sprintf(buffer, "%s/%s", argv[2], ".crawler");
		fp = fopen(buffer, "w");
		if (fp == NULL) {
			fprintf(stderr, "usage: [pageDirectory] isn't writable\n");

			exit(3);
		}

		fclose(fp);
	}

	closedir(dp);
	// checking for valid maxDepth
	int depth; // hold the max depth
	char other; // in case user inputs non integers
	if ((sscanf(argv[3], "%d%c", &depth, &other) == 1)) {
		if (depth < 0) {
			fprintf(stderr, "usage: [maxDepth] must be a positive integer\n");
			exit(4);
		}
	}
	else {
		fprintf(stderr, "usage: [maxDepth] must be an integer\n");
		exit(4);
	}
	

	// pass the parameters to crawler
	crawler(argv[1], argv[2], depth);
}

void crawler(char *seedURL, char *pageDirectory, int maxDepth)
{
	// used for storing the webpages
	bag_t *bag = bag_new();
	hashtable_t *ht = hashtable_new(100);

	// initially with null html and 0 depth and store the webpage
	webpage_t *wp = webpage_new(seedURL, 0, NULL);

	bag_insert(bag, wp);
	hashtable_insert(ht, seedURL, "seen"); // add the url to seen list

	webpage_t *current = bag_extract(bag); // extracts a page to be crawled
	int id = 1;
	while (current != NULL) { // while there are more webpages to crawl
		// gets the content of that page
		if (webpage_fetch(current)) {
			if ((webpage_save(current, pageDirectory, id)) == false) {
				printf("error: page not saved\n");
			}
		}
		else {
			printf("error: page not fetched\n");
		}
		if (webpage_getDepth(current) < maxDepth) {
			int pos = 0;
			char *result;
			while ((pos = webpage_getNextURL(current, pos, &result)) > 0) {
				// ignore page if it isn't internal
				if (IsInternalURL(result) == false) {
					free(result);
				}
				else {
					// insert into hashtable of seen pages
					if (hashtable_insert(ht, result, &id) == true) {
						webpage_t *next = webpage_new(result, webpage_getDepth(current)+1, NULL);
						bag_insert(bag, next);

					}
					free(result);
				}
			}
		}
		webpage_t *next = bag_extract(bag);
		webpage_delete(current); // frees the page
		current = next;
		id++;
		// saves it into the directory with a unique id
	}
}

bool webpage_save(webpage_t *page, char *pageDirectory, int id)
{
	if (page == NULL || pageDirectory == NULL || id < 0) return false;
	FILE *fp;
	char buffer[100];
	sprintf(buffer,"%s/%i", pageDirectory, id); 

	if ((fp = fopen(buffer, "w")) != NULL) {
	// each webpage is saved with a unique id
		fprintf(fp, "%s\n", webpage_getURL(page)); // first line is the url
	 	fprintf(fp, "%d\n", webpage_getDepth(page)); // second line is the depth
	 	fprintf(fp, "%s", webpage_getHTML(page)); // rest is the content
	 	fclose(fp);
	}
	else {
		return false;
	}
	return true;
}
