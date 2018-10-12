/* FUNCTIONALITY
 *
 * Takes an array containing the parsed regular expression and converts it
 * into a NFA, which is then printed out in the form of a transition table. 
 *
*/
#include <stdio.h>
#include <stdlib.h>
#include "regexToDFA.h"
#include "dataStructures.h"
#include <stdbool.h>
#include <string.h>

int main(int argc, char** argv){
    if(argc > 1){       // Takes a file name
                        // Default is the file regex.txt in this dir.
        setFileName(argv[1]);
    }
    int max = 300;      // The maximum length of regex accepted.
    char* reg = (char*)malloc(sizeof(char)*max);
    int res = 0;
    char c;
    DFA* p1,*p2;
    DFAArray* st = DFAArrayInit(10); // The "Stack" that will hold the DFAs
    DFA* Final = NULL;               // The pointer to the completed DFA
    while(res != -1 ){
        res = nextRegex(reg,max);    // Get the next regex from the file.
        if(res != -1){               // Check if not end of file.
            for(int i  = 0;(c = reg[i])!= '\0'; i++){
                if(isspace(c)){
                    continue;
                }
                if(isAlphabet(c)){
                    DFAArrayAdd(st,DFAGen(c));// Create an NFA that accepts c.
                }else if(isOp(c)){
                    if(c == '*'){
                        p1 = DFAPop(st);      // Get top NFA and apply star.
                        DFAArrayAdd(st,DFAStar(p1));// Add the resulting NFA to the stack.
                    }else if(c == '|'){
                        p2 = DFAPop(st);
                        p1 = DFAPop(st);      // apply Or operation on the top two NFAs
                        DFAArrayAdd(st,DFAOr(p1,p2));// Add the resulting NFA to the stack.
                    }else if(c == '&'){
                        p2 = DFAPop(st);      // apply AND operation to the top two NFAs
                        p1 = DFAPop(st);
                        DFAArrayAdd(st,DFAAnd(p1,p2));// Add the resulting NFA to the stack.
                    }else{
                        printf("Malformed Regex, exiting.\n");
                        DFA* temp;
                        while(st->used > 0){
                            temp = DFAPop(st);
                            DFAFree(&temp);
                        }
                        DFAArrayFree(&st);
                        free(reg);
                        closeFiles();
                        return 0;
                    }
                }else{
                    printf("Malformed Regex, exiting \n");
                    DFA* temp;
                    while(st->used > 0){
                        temp = DFAPop(st);
                        DFAFree(&temp);
                    }
                    DFAArrayFree(&st);
                    free(reg);
                    closeFiles();
                    return 0;
                }
            } 
        // Pop the last DFA off the stack and print it out.
        Final = DFAPop(st);
        printDFA(Final);
        }
        if(Final != NULL){
            DFAFree(&Final);
        }
        // Make sure the stack ptr is set to 0 each time.
        if(st->used > 0){
            printf("Malformed Regex, resulting table may be invalid.");
            clearDFAArray(st);
        } 
    }
    // Free all the things and close the files.
    DFAArrayFree(&st);
    free(reg);
    closeFiles();
        
}
