# CS50 Lab 6
## Shaket Chaudhary, May 2017

#### Designing 'querier'

Querier will need to have a directory in which there are documents containing
information about webpages. Additionally it will need to have a file present
that contains all the information for building an index, this is the same file
that was produced by indextest.

#### querier.c
Querier first continuously prompts for a query until a proper answer is typed
in. The query then cleans the query out. Next the query finds the scores for
the query in each document. The scores are sorted into descending order and
the results are printed out.

#### other programs
All the other programs should be separate from querier. This includes but is
not limited to hashtable, counters, webpage, and file programs.

#### high level pseudocode

querier:

1. Check for arguments
2. Load the index from the argument into a data structure
3. Read the search query from the stdin
4. Clean and parse each query
5. If the query is incorrect, notify the user and prompt again
6. Ignore empty queries
7. Identify the set of documents matching the query
8. If no documents satisfy the query notify user
9. Rank the results of the documents in decreasing order by match
10. Exit when the query is completed or EOF is reach