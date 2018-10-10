Automata and Formal Languages: PROJECT ONE

A C program that reads a text file which has one or more regular expressions
in postfix notation, converts them into a NFA, and displays it on the screen
in the form of a transition table.

By Andrew Oakes


BUILD INSTRUCTIONS -----------------------------------------------------------

To compile the code, type 'make' into the terminal while you are in the
project directory.

If you want the program to be built with debug informations, type 'make debug'

To get rid of the current object files, type 'make clean'.

USAGE INSTRUCTIONS -----------------------------------------------------------

To run the program, first follow the above build instructions, then type
'./dfa <path to regex file>'. By default it will use regex.txt.

<IMPORTANT TO READ THIS>

This will print out a transition table for each regex present in the file. The
final states will be labeled with a series of Fs. the start state will always 
be the top state in the table.  

FILES ------------------------------------------------------------------------

convert.c - Contains the main program, responsible for converting the regex to
a NFA and printing it out.

DFAArray.c - Contains various functions pertaining too an expandable array 
that holds DFA pointers.

intArray.c - Contains various functions pertaining too an expandable array 
that holds integers.

parse.c - Contains functions for checking if a character is an operator or a
member of the alphabet.

regex.txt - Contains the regular expressions to be processed.

dataStructures.h - Defines all of the structs used for each data structure as
well as the function prototypes for all the functions that are needed in order
to use the data structures.

DFA.c - Contains the code for creating and manipulating NFAs (or, and, star).

Makefile - Contains the code for compiling the program with different options.

README.txt - this

stack.c - Ended up not being necessary. Fixed size stack for storing integers.

fileIO.c - Contains functions for reading each regex from a file.

regexToDFA.h - Contains the function prototypes used by everything besides the
data structure files.

transition.c - Contains the functions for creating new transitions which are 
used in the transition arrays that each DFA node has.
