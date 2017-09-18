# CS50 Lab 4
## Shaket Chaudhary, April 2017

### Testing 'crawler'

To test my *crawler* I tried many different test cases on the terminal to explore the capabilities of the *crawler* program and to demonstrate its use.

It tests the program with various forms of incorrect command-line arguments to ensure that its command-line parsing, and validation of those parameters, works correctly.

It tests the crawler with a seedURL that points to a non-existent server.

It tests the crawler with a seedURL that points to a non-internal server.

It tests the crawler with a seedURL that points to a valid server but non-existent page.

It crawls a simple, closed set of cross-linked web pages to crawl. It ensures that some page(s) are mentioned multiple times within a page, and multiple times across the set of pages. It ensures there is a loop (a cycle in the graph of pages). In such a little site, I know exactly what set of pages should be crawled, at what depths, and I know where your program might trip up.

I point the crawler at a page in that site, and explore at depths 0, 1, 2, 3, 4, 5. I verified that the files created match expectations.

I repeated with a different seed page in that same site. If the site is indeed a graph, with cycles, there should be several interesting starting points.

I pointed the crawler at our Wikipedia playground. I explored at depths 0, 1, 2. I verify that the files created match expectations.

####Testing for incorrect amount of arguments
	[schaudhary@wildcat ~/cs50/labs/tse/crawler]$ crawler
	usage: crawler [seedURL] [pageDirectory] [maxDepth]
	
	[schaudhary@wildcat ~/cs50/labs/tse/crawler]$ crawler http://old-www.cs.dartmouth.edu/~cs50/index.html
	usage: crawler [seedURL] [pageDirectory] [maxDepth]
	
	[schaudhary@wildcat ~/cs50/labs/tse/crawler]$ crawler http://old-www.cs.dartmouth.edu/~cs50/index.html data
	usage: crawler [seedURL] [pageDirectory] [maxDepth]

#### Testing for correct url
	[schaudhary@wildcat ~/cs50/labs/tse/crawler]$ crawler wrong data 1
	usage: [seedURL] is not valid
	[schaudhary@wildcat ~/cs50/labs/tse/crawler]$ crawler http://facebook.com data a
	usage: [seedURL] is not valid
	[schaudhary@wildcat ~/cs50/labs/tse/crawler]$ crawler http://old-www.cs.dartmouth.edu/~cs50/indexnotreal.html data 1
	error: page not fetched
#### Testing for correct directory
	[schaudhary@wildcat ~/cs50/labs/tse/crawler]$ crawler http://old-www.cs.dartmouth.edu/~cs50/index.html data 1
	usage: [pageDirectory] doesn't exist
#### Testing for correct integer
	[schaudhary@wildcat ~/cs50/labs/tse/crawler]$ crawler http://old-www.cs.dartmouth.edu/~cs50/index.html data a
	usage: [maxDepth] must be an integer
	[schaudhary@wildcat ~/cs50/labs/tse/crawler]$ crawler http://old-www.cs.dartmouth.edu/~cs50/index.html data 1a
	usage: [maxDepth] must be an integer
	[schaudhary@wildcat ~/cs50/labs/tse/crawler]$ crawler http://old-www.cs.dartmouth.edu/~cs50/index.html data ?
	usage: [maxDepth] must be an integer
	

### Limitations
I never tested for depths beyond 5 as it is not polite. Additionally testing bigger numbers results in slower results often too slow to reasonably test.