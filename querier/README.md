# CS50 Lab 6
## Shaket Chaudhary, May 2017

### querier

A *querier* is a standalone program that reads the index file produced by the
*indexer*, and page files produced by the *querier*, and answers search queries
submitted via stdin.

### Usage: 
	./querier pageDirectory indexFilename
	
`pageDirectory` is the pathname of a directory produced by the Crawler	
`indexFilename` is the pathname of a file into which the index should be written

### Assumptions

Since indexer didn't accept any words less than 3 characters, I assumed the
user wouldn't input any small words and expect results. The program keeps 
prompting the user until a proper search performs. I assumed an and between
every word and only did functions for or when an or was found.

### Querier Exit Status
	0: successful execution
	1: incorrect amount of arguments
	
### Limitations

The user can't search for and or or because they are special words in the 
program. The user can't search for words smaller than 3 because there won't
be any in the files due to the way indexer created the file. Additionally
the way this program was set up, there can't be more than 30 documents that
match, this can be adjusted however by changing the size of the array(s).
  
### Compilation

To compile, simply `make`.

See TESTING.md for details of testing and an example test run.
