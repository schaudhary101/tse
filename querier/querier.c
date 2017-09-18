/* 
 * querier.c by Shaket Chaudhary 
 * May, 2017
 * A querier reads an index produced by an indexer and
 * the page files produced by the Crawler, to answer
 * written queries entered by the user
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>
#include "index.h"
#include "file.h"
#include "hashtable.h"
#include "counters.h"

static int parsedQuery(FILE *fp, char *words[], int size);
static int andHelper(char *words[], const int size);
static int orHelper(char *words[], const int size);
static int docCount (char *pageDirectory);
static int orNumber (char *words[], const int size);
static void valueList(void *arg, const int key, int count);
static void sortedList (int number[], counters_t *ctrs, int docNumber, 
		char *pageDirectory);

static int never(int c) { 
	return (0); 
}

int main(int argc, char *argv[])
{
	DIR *dp;
	FILE *fp;
	hashtable_t *ht;
	char crawlerFile[100];

	// checking for correct amount of arguments
	if (argc != 3) {
		fprintf(stderr, "usage: ./querier pageDirectory indexFilename\n");
		exit(1);
	}
	// checking if pageDirectory is produced by crawler and is a directory
	dp = opendir(argv[1]);
	if (dp == NULL) {
		fprintf(stderr, "usage: pageDirectory doesn't exist\n");
		exit(1);
	} else {
		sprintf(crawlerFile, "%s/%s", argv[1], ".crawler");
		fp = fopen(crawlerFile, "r");
		if (fp == NULL) {
			fprintf(stderr, "pageDirectory isn't created by crawler\n");
			exit(1);
		}
		fclose(fp);
	}
	closedir(dp);

	// check for indexFilename
	fp = fopen(argv[2], "r");
	if (fp == NULL) {
		fprintf(stderr, "indexFilename does not exist\n");
		exit(1);
	}
	fclose(fp);

	// create a new index
	ht = hashtable_new(500);
	index_load(argv[2], ht);

	// create an array to contain the cleaned query
	int size = 500;
	char *words[size];
	// keep running the query until a valid query
	while (parsedQuery(stdin, words, size) != 0);
	// holds the final scores for each document
	counters_t *final = counters_new();
	// get the number of or's found in a query
	int orCount = orNumber(words, size);
	// find the number of documents in the directory
	int docNumber = docCount(argv[1]);
	for (int j = 1; j <= docNumber; j++) {
		int scores[orCount+1]; // array for keeping track of each words score
		for (int x = 0; x < orCount + 1; x++) {
			scores[x] = 0;
		}
		int index = 0; // keep track of index
		int finalScore = 1000; // temporary value
		for (int i = 0; i < size; i++) {  
			if (words[i] != NULL && strcmp(words[i], "and")) { // ignore and
				if (strcmp(words[i], "or")) { // keep the lowest
					counters_t *ctrs = hashtable_find(ht, words[i]);
					int temp_score = counters_get(ctrs, j);
					if (temp_score <= finalScore) {
						finalScore = temp_score;
						scores[index] = finalScore;
					}
				} else { // treat or as start of new count
					index++;
					continue;
				}
			}
		}
		finalScore = 0;
		// combine the scores (intersection)
		for (int x = 0; x < orCount + 1; x++) {
			finalScore = finalScore + scores[x];
		}
		counters_set(final, j, finalScore);
	}
	// clean up the memory
	for (int i = 0; i < size; i++) {
		free(words[i]);
	}

	// create a list for sorting matches in descending order
	int number[500];
	for (int i = 0; i < 500; i++) {
	    number[i] = 0; // initialize to 0 matches which won't be reported
	}
	// function to put the values of the counter into a array list
	counters_iterate(final, number, valueList); 
	sortedList(number, final, docNumber, argv[1]);

	counters_delete(final);
	hashtable_delete(ht, hash_delete);
	exit(0);
}

static int 
parsedQuery(FILE *fp, char *words[], int size)
{
	// clear up if there is existing data
	for (int i = 0; i < size; i++) words[i] = NULL;
	char line[size]; // line for reading the stdin
	char *token; // for splitting up into words
	int j = 0;

	printf("KEY WORDs:> ");
	if (fgets(line, size, fp) != NULL) {
		if (strlen(line) == 1) return -1;
		for (int i = 0; i < strlen(line); i++) {
			// normalize the words
			if (!(isalpha(line[i])) && !(isspace(line[i]))) {
				fprintf(stderr, "Error: bad character '%c' in query.\n",
				 line[i]);
				return -1;
			}
			line[i] = tolower(line[i]);
		}
		// tokenize and remove the spaces and new lines
		token = strtok(line, "\n");
		token = strtok(line, " ");
		// allocate memory for the tokens and store in array of pointers
		while (token != NULL) {
			words[j] = malloc(strlen(token)+1);
			strcpy(words[j], token);
			j++;
			token = strtok(NULL, " ");
		}
		// clean up if and error is found
		if (andHelper(words, size) == -1) {
			for (int i = 0; i < size; i++) {
				free(words[i]);
				words[i] = NULL;
			}	
			return -1;
		}
		// clean up if or error is found
		if (orHelper(words, size) == -1) {
			for (int i = 0; i < size; i++) {
				free(words[i]);
				words[i] = NULL;
			}	
			return -1;
		}
		printf("Query:");
		for (int i; i < size; i++) {
			if (words[i] != NULL) {
				printf(" %s", words[i]);
			}
		}
		printf("\n");
	}
	return 0;
}

static int 
andHelper(char *words[], const int size) 
{
	// finds the first word and it cannot be and
	int exit_status = 0;
	if (strcmp(words[0], "and") == 0) {
		fprintf(stderr, "Error: '%s' cannot be first\n", words[0]);
		return -1;
	}
	for (int i = size - 1; i >= 0; i--) {
		// finds the first non null word and that word cannot be and
		if (words[i] != NULL) {
			if (strcmp(words[i], "and") == 0) {
				fprintf(stderr, "Error: '%s' cannot be last\n", words[i]);
				exit_status = -1;
				break;
			}
			else {
				exit_status = 0;
				break;
			}
		}
	}
	// if there was something wrong with the last word then stop & report error
	if (exit_status == -1) return exit_status;
	for (int i = size - 1; i >= 0; i--) {
		if (words[i] != NULL) {
			if (strcmp(words[i], "and") == 0) { // checking for adjacent or/and
				if (strcmp(words[i-1], "or") == 0) {
					fprintf(stderr, "Error: '%s' and '%s' cannot be adjacent\n"
						, words[i], words[i-1]);
					exit_status = -1;
					break;
				}
				if (strcmp(words[i-1], "and") == 0) {
					fprintf(stderr, "Error: '%s' and '%s' cannot be adjacent\n"
						, words[i], words[i-1]);
					exit_status = -1;
					break;
				}
			}
		}	
	}
	return exit_status;
}

static int 
orHelper(char *words[], const int size) 
{
	// finds the first word and it cannot be or
	int exit_status = 0;
	if (strcmp(words[0], "or") == 0) {
		fprintf(stderr, "Error: '%s' cannot be first\n", words[0]);
		return -1;
	}
	for (int i = size - 1; i >= 0; i--) {
		// finds the first non null word and that word can't be or
		if (words[i] != NULL) {
			if (strcmp(words[i], "or") == 0) {
				fprintf(stderr, "Error: '%s' cannot be last\n", words[i]);
				exit_status = -1;
				break;
			}
			else {
				exit_status = 0;
				break;
			}
		}
	}
	// if there was something wrong with the last word then stop
	if (exit_status == -1) return exit_status;
	for (int i = size - 1; i >= 0; i--) { // checking for adjacent or & and
		if (words[i] != NULL) {
			if (strcmp(words[i], "or") == 0) {
				if (strcmp(words[i-1], "or") == 0) {
					fprintf(stderr, "Error: '%s' and '%s' cannot be adjacent\n"
						, words[i], words[i-1]);
					exit_status = -1;
					break;
				}
				if (strcmp(words[i-1], "and") == 0) {
					fprintf(stderr, "Error: '%s' and '%s' cannot be adjacent\n"
						, words[i], words[i-1]);
					exit_status = -1;
					break;
				}
			}
		}	
	}
	return exit_status;
}

static int 
docCount (char *pageDirectory) 
{
	// goes into the directory and gets the number of documents
	FILE *fp;
	char buffer[100];
	int ID = 1;
	sprintf(buffer, "%s/%d", pageDirectory, ID);
	fp = fopen(buffer, "r");
	while (fp != NULL) {
		fclose(fp);
		ID++;
		sprintf(buffer, "%s/%d", pageDirectory, ID);
		fp = fopen(buffer, "r");
	}
	return ID - 1;
}

static int 
orNumber (char *words[], const int size) 
{
	// find out the number of ors in the query
	int count = 0;
	for (int i = 0; i < size; i++) {
		if (words[i] != NULL) {
			if (strcmp(words[i], "or") == 0) {
				count++;
			}
		}
	}
	return count;
}

static void 
valueList(void *arg, const int key, int count)
{
	// for iterator to create a list of the values
    int *number = arg;
    for (int i = 0; i < key; i++) number[i] = count;
}

static void 
sortedList (int number[], counters_t *ctrs, int docNumber, char *pageDirectory)
{
    int i, j, a;
    char buffer[100];
    char *URL;
    FILE *fp;
    /*  sorting begins ... */
    for (i = 0; i < 500; ++i) {
        for (j = i + 1; j < 500; ++j) {
            if (number[i] < number[j]) {
                a = number[i];
                number[i] = number[j];
                number[j] = a;
            }
        }
    }
    int totalMatches = 0;
    for (int y = 0; y < 500; y++) {
    	if (number[y] != 0) totalMatches++;
    } 
    // if there are no matches then exit
    if (totalMatches == 0) {
    	printf("No documents match.\n");
    	return;
    } 
    // print out total matches
    printf("Matches %d documents (ranked):\n", totalMatches);
    for (i = 0; i < 500; ++i) {
    	for (int x = 0; x <= docNumber; x++) {
    		if (counters_get(ctrs, x) == number[i] && number[i]) {
    			counters_add(ctrs, x);
    			sprintf(buffer, "%s/%d", pageDirectory, x);
    			fp = fopen(buffer, "r");
    			URL = readlinep(fp); // the first line in the file is the URL
    			printf("score   %d doc   %d: %s\n", number[i], x, URL);
    			free(URL);
    			fclose(fp);
    		}
    	}
    }
}
