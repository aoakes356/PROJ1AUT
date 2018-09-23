/* FUNCTIONALITY
 *
 * Takes an array containing the parsed regular expression and converts it
 * into a DFA, which is then stored in the output file specified in fileIO
 *
*/
#include <stdio.h>
#include <stdlib.h>
#include "regexToDFA.h"
#include "dataStructures.h"
#include <stdbool.h>

int main(int argc, char** argv){
    if(argc > 1){       // Takes a file name
                        // Default is the file regex.txt in this dir.
        setFileName(argv[1]);
    }
    int max = 300;
    char* reg = (char*)malloc(sizeof(char)*max);
    int res = 0; 
    while(res != -1 ){
        res = nextRegex(reg,max);
        if(res != -1){
            printf("%s",reg);
            printf("is Regex? %i\n",isRegex(reg,max));
        }
    }
    stack* st = stackInit();
    push(st,'a');
    push(st,'b');
    printf("%c %c \n",pop(st),pop(st));
    free(st);
    free(reg);
    closeFiles();
    return 0;
}
