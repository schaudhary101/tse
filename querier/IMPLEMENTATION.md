# CS50 Lab 6
## Shaket Chaudhary, May 2017

### Querier Implementation

### Overall

We use two data structures: a *hashtable* which itself uses a *set* for its
implementation. The hashtable stores the words, which are found in the
documents created by *crawler*. The documents are named by ID, starting at 1
and increasing by one. The hashtable takes an item, in this case *counters*.
Counters for their key takes the document ID that the word was found in. The
counter also keeps track of the frequencies of the word in each document. After
the user inputs a query the program searches for the counts in each document.

### Components

All the logic is contained in one program querier.c. This program parses the 
arguments first before sending the input to a query parsing function. The query
parsing function has two helper methods that identify if there is an invalid
placement of the words or or and. Additionally there are two more methods that
return the number of docuemnts in a directory and the number of ors found in a 
query.

-------------------------------------------------------------------------------

#### querier.c

`static int 
parsedQuery(FILE *fp, char *words[], int size);`
	
	1. Read from stdin into a line	
	2. Check for valid characters
	3. Tokenize the string
	4. Store the tokens into a list
	5. Print out the query

`static int 
andHelper(char *words[], const int size);`
	
	1. Check for and in the beginning of the query
	2. Loop backwards and check for and at the end of the query
	3. Loop and upon finding and in the middle of the query check for adjacents

`static int 
orHelper(char *words[], const int size);`
	
	1. Check for or in the beginning of the query
	2. Loop backwards and check for or at the end of the query
	3. Loop and upon finding or in the middle of the query check for adjacents

`static int 
docCount (char *pageDirectory);`
	
	1. Create the name of the file path
	2. Increment until a file isn't found
	3. Return the count

`static int 
orNumber (char *words[], const int size);`
	
	1. Loop through the query and check for number of ors

`static void
valueList(void *arg, const int key, int count);`

	1. Iterate through counter and store the values into a list

`static void
sortedList(int *number, counters_t *ctrs, int docNumber, char *pageDirectory);`

	1. Sort the list into descending order
	2. Iterate through the list and find # of docs with values greater than 0
	3. Print out the results with the url
