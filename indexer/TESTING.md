# CS50 Lab 5
## Shaket Chaudhary, May 2017

### Indexer Testing

Indexer created a file which prints the contents of the hashtable. For indexer
to be a good program, it needs to consistently output the same results given
the same data. Indextest reads from the output file created by indexer and
proceeds to put that data back into a index data structure. From there it
prints the contents again to another file. Then the two files need to compared
to see if the results are the same.

However due to the nature of the modules used by indexer, the output doesn't
necessarily have to come out in the exact same order. Thus before comparing the
two output files it is necessary to sort the two files. 

The commands executed can be seen below:

`indexer data indexfile1`
`indextest indexfile1 indexfile2`
`gawk -f indexsort.awk indexfile1 > indexfile1.sorted`
`gawk -f indexsort.awk indexfile2 > indexfile2.sorted`	

Initial inspection by looking at the beginning of both documents sorted seemed
to indicate that the two file outputs were the same results.

	[schaudhary@wildcat ~/cs50/labs/tse/indexer]$ cat 	indexfile2.sorted | head
	about 2 3
	above 2 1
	academy 2 1
	acm 2 1
	activities 2 2
	affiliate 2 1
	after 1 1 3 1
	all 2 1
	amp 1 1 3 1
	amulet 2 1
	[schaudhary@wildcat ~/cs50/labs/tse/indexer]$ cat 	indexfile1.sorted | head
	about 2 3
	above 2 1
	academy 2 1
	acm 2 1
	activities 2 2
	affiliate 2 1
	after 1 1 3 1
	all 2 1
	amp 1 1 3 1
	amulet 2 1
	
Further inspection was performed by the diff command. It was found that the two
files, after being sorted were identical.

	[schaudhary@wildcat ~/cs50/labs/tse/indexer]$ diff -s indexfile1.sorted indexfile2.sorted
	Files indexfile1.sorted and indexfile2.sorted are identical

###Additional Information
The results can also be manually evaluated in the files with a .sorted
extension. I used my output from my crawler which was put into a directory
called data. This directory was copied for convenience into indexer but the
original can be accessed as well by providing the correct path. Similarly the
data from Kotz's sample output can also be used to compare the results. In all
cases the results were identical files.
