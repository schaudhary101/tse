# CS50 Lab 4
## Shaket Chaudhary, April 2017

### Implementing 'crawler'

####Pseudo code for logic/algorithmic flow

The crawler will run as follows:

	1. execute from a command line
	2. parse the command line, validate parameters, initialize other modules
	3. make a webpage for the seedURL, marked with depth=0
	4. add that page to the bag of webpages to crawl
	5. add that URL to the hashtable of URLs seen
	6. while there are more webpages to crawl,
		1. extract a webpage (URL,depth) item from the bag of webpages to be crawled
		2. pause for at least one second,
		3. use pagefetcher to retrieve a webpage for that URL,
		4. use pagesaver to write the webpage to the directory with a unique ID
		5. if the webpage depth is less than the max, explore to find links:
			1. normalize the URL
			2. ignore non-internal URLs
			3. insert URL into a hashtable
			4. make a new webpage if successful

####Data structures
Crawler used bags and hashtables. Hashtables use sets for its implementation. Bags were used to store websites to explore. Hashtables were used to store the information retrieved from those websites. Additionally, functions from webpage module was used to parse the websites and fetch the websites. I created my own pagesaver function.

####Additional Information
Errors only occurred for problems with the arguments. If the given webpage doesn't exist but the domain is correct, then it couldn't be fetched and thus nothing will be saved in the directory. This doesn't show up as an error as this is due to a limitation of the webpage module. Additionally, if some pages couldn't be saved, then the program continues on to the next page.

