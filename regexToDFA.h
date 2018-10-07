#ifndef REG_TO_DFA
#define REG_TO_DFA

#include <stdio.h>


// File IO
int nextRegex(char*,int);

void setFileName(char*);

FILE* getFileRead();

FILE* getFileWrite();

void closeFiles();

// Parse
int isMember(char);

int isRegex(char* reg, int);

int isAlphabet(char c);

int isOp(char c); 
#endif
