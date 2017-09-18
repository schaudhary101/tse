# CS50 Lab 5
## Shaket Chaudhary, May 2017

### Indexer Implementation

### Overall

We use three data structures: a *hashtable* which itself use a *set* for its 
implementation. The hashtable stores the words that are found in the documents
in a directory created by *crawler*. The documents are named by ID, starting at
1 and increasing by one. Along with inserting a word, the hashtable can take an
item. The item we insert are *counters*. Counters for their key takes the
document ID that the word was found in. The counter also keeps track of the
frequencies of the word in each document.

### Components

We divide the code into numerous files. First, *indexer.c* simply calls all the
logic which is stored into other files. Most of the logic can be found in
*index.c* which contains logic for building, loading, and saving the index. In
addition, it provides a delete function for cleaning up the index data 
structure. Next, *pagedir.c* contains the logic for creating a webpage from
the information in the documents. Finally, there is *indextest.c* which creates
another index from one index file.

-------------------------------------------------------------------------------

####index.c

void 
index_build(char *directory, hashtable_t *index)
	pseudocode:
		open the directory and iterate through the files
		build a webpage for finding all the words
		store into a hashtable
			if the word is already in there increment the counter
			otherwise create a new counter

void 
index_load(char *filename, hashtable_t *ht)
	pseudocode:
		read the file
			each word is the key in a hashtable
				the other numbers are the key and counts for the counters

void 
index_save(const char *filename, hashtable_t *ht)
	pseudocode:
		open a file to write into
		for each line in the file write:
			the word and each ID followed by count
void 
hash_delete(void *item)
	pseudocode:
		iterate through the hashtable
			iterate through the counters
				delete

####pagedir.c

webpage_t*
webpage_build(FILE *fp)
	pseudocode:
		open a file and store the first two lines as the URL and depth
		store the rest of the file as the HTML
