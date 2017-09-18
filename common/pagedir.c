/* 
 * pagedir.c
 * Shaket Chaudhary, May 2017
 * Provides functions that will be useful to crawler, indexer, and querier
 */

#include <stdio.h>
#include <stdbool.h>
#include "webpage.h"
#include "file.h"

bool
webpage_save(webpage_t *page, char *pageDirectory, int id)
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

webpage_t*
webpage_build(FILE *fp)
{
	// first line should be url
	char *url = readlinep(fp);
	// second line should be depth
	char *level = readlinep(fp);
	int depth;
	if ((sscanf(level, "%d", &depth)) != 1) {
		fprintf(stderr, "depth not found\n");
		return NULL;
	}
	// rest of the document is the html
	char *html = readfilep(fp);
	// cleaning up and returning the page
	webpage_t *page = webpage_new(url, depth, html);
	free(url);
	free(level);
	return page;
}
