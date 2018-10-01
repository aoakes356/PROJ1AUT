/* FUNCTIONALITY
 *
 * Takes an array containing the parsed regular expression and converts it
 * into a DFA (Mean NFA :( ), which is then stored in the output file specified in fileIO
 * by default outputs to stdin.
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

    DFA* dfa = DFAinit(0,1); 
    intArray* arr = intArrayInit(10);

    for(int i = 1; i < 101; i++){
        transitionArrayAdd(dfa->transitions,transitionInit('a',DFAinit(i,0)));
        intArrayAdd(arr,i);
    }

    for(int i = 0; i<101; i++){
        printf("Is %i in arr? %i \n",i,intIn(arr,i));
    }

    DFA* q0 = DFAinit(0,0);
    DFA* q1 = DFAinit(1,0);
    DFA* q2 = DFAinit(2,1);
    
    transitionArrayAdd(q0->transitions,transitionInit('a',q1));
    transitionArrayAdd(q1->transitions,transitionInit('b',q2));
    transitionArrayAdd(q2->transitions,transitionInit('E',q0));

    DFA* z0 = DFAinit(0,0);
    DFA* z1 = DFAinit(1,0);
    DFA* z2 = DFAinit(2,1);
     
    transitionArrayAdd(z0->transitions,transitionInit('b',z1));
    transitionArrayAdd(z1->transitions,transitionInit('a',z2));
    transitionArrayAdd(z2->transitions,transitionInit('E',z0));
    printf("Entering the and\n");
    DFAAnd(q0,z0);
    printDFA(q0);
    printf("Exiting the and\n"); 
    printf("%i\n",dfa->transitions->used);
    intArrayFree(&arr);
    DFAFree(&dfa);
    DFAFree(&q0);
    free(st);
    free(reg);
    closeFiles();
    return 0;
}
