/* FUNCTIONALITY
 *
 * Takes two file names, reads each line expecting it to contain a valid regex
 * in postfix notation. Will contain a function called "nextRegex" which will
 * read from the file and return a line presumed to be a regex. If it is an
 * empty file or the next line is empty, it returns a null pointer.
 *
*/

#include "regexToDFA.h"
#include <stdio.h>
#include <stdlib.h>

char* IN = "regex.txt"; // The file we will read from.
FILE* IN_F = NULL;
char* OUT = "DFATable.txt";
FILE* OUT_F = NULL;     // The file we will write to.

int nextRegex(char* reg, int max){
    if(IN_F == NULL){
        getFileRead();
        if(IN_F == NULL){
            return -1;
        }        
    }
    return -1*(fgets(reg,max,IN_F) == NULL);// Returns 0 on sucess -1 on fail
}

void setFileName(char* name){
    IN = name;
}

FILE* getFileRead(){
    if(IN_F == NULL){
        return IN_F = fopen(IN,"r");
    }else{
        return IN_F;
    }
}

FILE* getFileWrite(){
    if(OUT_F == NULL){
        return IN_F = fopen(OUT,"w");
    }else{
        return OUT_F;
    }
}

void closeFiles(){
    if(OUT_F != stdout && OUT_F != NULL){
        fclose(OUT_F);
        OUT_F = NULL;
    }
    if(IN_F != NULL){
        fclose(IN_F);
        IN_F = NULL;
    }
}

