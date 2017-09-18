# CS50 Lab 4
## Shaket Chaudhary, April 2017

### crawler

A *crawler* is a program designed for downloading pages off the web. The crawler takes a URL, local directory, and depth.

### Usage: 
./crawler [seedURL] [pageDirectory] [maxDepth]

`seedURL` must be a valid URL and internal	
`pageDirectory` must exist and be a writable directory	
`maxDepth` must be a nonnegative integer

### Assumptions

No assumptions beyond those stated in the requirements. The current directory must be created before hand this program will not create the directory but will exit if it can't find it. Additionally, he crawler stays within the cs.dartmouth domain. 

### Exit Status
	1: incorrect amount of arguments
	2: invalid URL
	3: invalid directory
	4: invalid depth

### Limitations

Program takes substantial amount of time to run, will run slower for increasing max depth. Only staying in the cs.dartmouth domain.
  
### Compilation

To compile, simply `make`. Results are saved in the directory created. 

See [TESTING](TESTING.md) for details of testing and an example test run.
