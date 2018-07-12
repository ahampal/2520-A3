Name:
Amit Hampal

Student #:
0964514

Description:
This program compares two text files (a "dictionary" text file and the 
other an "input" text file) and then proceeds to list the differences between
the dictionary and input files. The program can also alter the dictionary file
by either adding or removing words.

Compilation:
execute 'make HashAPI' to create HashTableAPI library
execute 'make' to compile main.c
execute 'make test' to create testMain
execute './main fileName.txt' from bin  to run main with txt file in same folder
execute './main ../directorypath/fileName.txt' from bin to run main with txt file
in a different directory

Assumptions and limitations:
I have assumed that removing words from the dictionary is to be case sensitive
example: if the word "Hello" exists in the dictionary, ordering the program remove
"hello" from the dictionary will not remove the word "Hello" from the dictionary.

A similar assumption has been made for adding words (adding the word "hello" will
result in a different entry from "Hello"). 

I have included sample dictionaries and
input files in the assets folder. The prefix of matching dictionaries and input files
will be the same. (eg. a3_dictionary.txt and a3_userFile.txt)

Collision Resolution Strategy:
A 2D array of nodes has been implemented as the collision strategy (seperate chaining). 
Each row represents a different index value, and whenever  entries have the same index,
said entries are placed in the same row but each entry will be in a different column
with the each entry pointing to the next entry in the row.

The hash function adds up each of the individual letter values in a key string 
and the resulting value is modulus'd by the table size to get an appropriate index.
This hash function does not result in a well distributed index for each of the nodes
when the table is small, but as the table grows in size, the distribution gets better
