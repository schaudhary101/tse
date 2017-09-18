# CS50 Lab 5
## Shaket Chaudhary, May 2017

### indexer

A *indexer* is a program that reads the document files produced by the TSE
crawler, builds an index, and writes that index to a file. *indextest* loads
an index file produced by the indexer and saves it to another file. 

### Usage: 
	./indexer pageDirectory indexFilename
	
`pageDirectory` is the pathname of a directory produced by the Crawler	
`indexFilename` is the pathname of a file into which the index should be written

	./indextest oldIndexFilename newIndexFilename
	
`oldIndexFilename` is the name of a file produced by the indexer
`newIndexFilename` is the name of a file which the index should be written

### Assumptions

No assumptions beyond those stated in the requirements. All words are
lowercased before counting occurences. The current directory must be created
before hand this program will not create the directory but will exit if it
can't find it. 

### Indexer Exit Status
	0: successful execution
	1: incorrect amount of arguments
	2: invalid directory
	3: unsuccessful creation of file
	
### Indextest Exit Status
	0: successful execution
	1: incorrect amount of arguments
	2: file couldn't be opened
	
### Limitations

Due to the data structures used for storing and retrieving information, the
files created will not be identical due to randomness. However, the content
should all be the same. Sorting is necessary to compare the files.
  
### Compilation

To compile, simply `make`. Additionally each individual program can be compiled
by simply specifying which program after typing make. Results are saved in the file created. 

See TESTING.md for details of testing and an example test run.
