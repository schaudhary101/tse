# CS50 Lab 6
## Shaket Chaudhary, May 2017

### Querier Testing

Querier returns a list which states the number of matches for a given query.
For querier to be a good program, it needs to consistently output the same 
results given the same data. 

### Error Verificiation
All the cases below test for invalid output. In each case the expected result
returned. I test for invalid arguments first. Then I check for if the files
don't exist. Finally I test for invalid queries.

	[schaudhary@flume ~/cs50/labs/tse/querier]$ querier
	usage: ./querier pageDirectory indexFilename
	[schaudhary@flume ~/cs50/labs/tse/querier]$ querier pagedir
	usage: ./querier pageDirectory indexFilename
	[schaudhary@flume ~/cs50/labs/tse/querier]$ querier pagedir indexfile
	usage: pageDirectory doesn't exist
	[schaudhary@flume ~/cs50/labs/tse/querier]$ querier ../crawler/data indexfile
	indexFilename does not exist
	[schaudhary@flume ~/cs50/labs/tse/querier]$ querier ../crawler/data ../indexer/file1
	KEY WORDs:> Dartmouth College and
	Error: 'and' cannot be last
	KEY WORDs:> and Dartmouth College
	Error: 'and' cannot be first
	KEY WORDs:> or Dartmouth College
	Error: 'or' cannot be first
	KEY WORDs:> Dartmouth College or
	Error: 'or' cannot be last
	KEY WORDs:> Dartmouth and or College
	Error: 'or' and 'and' cannot be adjacent
	KEY WORDs:> 1 Dartmouth College
	Error: bad character '1' in query.
	
### Testing searches

Next was testing to see if the results were accurate and consistent. I first
tested *Dartmouth College*. Querier should treat this as "dartmouth and
college". Next I tested for Dartmouth and college individually. Then I tested
for Dartmouth or college and simple addition will verify that the results are
consistent. Finally I explicitly said Dartmouth and College and this was the
same result as the first search. Finally I tried searching for my name and as
expected there were no matching documents.

	[schaudhary@flume ~/cs50/labs/tse/querier]$ querier ../crawler/data ../indexer/file1
	KEY WORDs:> Dartmouth College
	Query: dartmouth college
	Matches 3 documents (ranked):
	score   3 doc   2: http://old-www.cs.dartmouth.edu/~dfk/
	score   1 doc   1: http://old-www.cs.dartmouth.edu/~cs50/index.html
	score   1 doc   3: http://old-www.cs.dartmouth.edu/~cs50/
	[schaudhary@flume ~/cs50/labs/tse/querier]$ querier ../crawler/data ../indexer/file1
	KEY WORDs:> Dartmouth
	Query: dartmouth
	Matches 3 documents (ranked):
	score   5 doc   2: http://old-www.cs.dartmouth.edu/	~dfk/
	score   1 doc   1: http://old-www.cs.dartmouth.edu/~cs50/index.html
	score   1 doc   3: http://old-www.cs.dartmouth.edu/~cs50/
	[schaudhary@flume ~/cs50/labs/tse/querier]$ querier ../crawler/data ../indexer/file1
	KEY WORDs:> College
	Query: college
	Matches 3 documents (ranked):
	score   3 doc   2: http://old-www.cs.dartmouth.edu/~dfk/
	score   1 doc   1: http://old-www.cs.dartmouth.edu/~cs50/index.html
	score   1 doc   3: http://old-www.cs.dartmouth.edu/~cs50/
	[schaudhary@flume ~/cs50/labs/tse/querier]$ querier ../crawler/data ../indexer/file1
	KEY WORDs:> Dartmouth or College
	Query: dartmouth or college
	Matches 3 documents (ranked):
	score   8 doc   2: http://old-www.cs.dartmouth.edu/~dfk/
	score   2 doc   1: http://old-www.cs.dartmouth.edu/~cs50/index.html
	score   2 doc   3: http://old-www.cs.dartmouth.edu/~cs50/
	[schaudhary@flume ~/cs50/labs/tse/querier]$ querier ../crawler/data ../indexer/file1
	KEY WORDs:> Dartmouth and College
	Query: dartmouth and college
	Matches 3 documents (ranked):
	score   3 doc   2: http://old-www.cs.dartmouth.edu/~dfk/
	score   1 doc   1: http://old-www.cs.dartmouth.edu/~cs50/index.html
	score   1 doc   3: http://old-www.cs.dartmouth.edu/~cs50/
	[schaudhary@flume ~/cs50/labs/tse/querier]$ querier ../crawler/data ../indexer/file1
	KEY WORDs:> Shaket Chaudhary
	Query: shaket chaudhary
	No documents match.

### Additional Information
There were no memory leaks, which was tested with valgrind. 