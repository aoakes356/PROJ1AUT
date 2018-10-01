/* FUNCTIONALITY
 *
 * This file contains the code responsible for building the DFA in memory from
 * supplied regex information.
 *
*/
#include <stdlib.h>
#include "dataStructures.h"
#include <stdio.h>

DFA* DFAinit(int state, int isFinal){
    DFA* d = (DFA*)malloc(sizeof(DFA));
    d->transitions = transitionArrayInit(10);
    d->state = state;
    d->isFinal = isFinal;
    return d;
}

void incrementStates(DFA* head, int amount, intArray** visitedStates){
    if((*visitedStates) == NULL){
        (*visitedStates) = intArrayInit(10);
    }
    DFA* current = head;
    intArrayAdd((*visitedStates),head->state);
    transition* currentTransition;
    for(int i = 0; i < current->transitions->used; i++){
        currentTransition = (current->transitions->array[i]);
        if(!intIn((*visitedStates),currentTransition->state->state)){
            intArrayAdd((*visitedStates),currentTransition->state->state);
            incrementStates(currentTransition->state,amount,visitedStates);
        }
    }
    head->state += amount;
}

DFA* DFAAndR(DFA* head, DFA* arg, intArray** visitedStates){
    // Add an epsilon jump from each Final state in head to the start of arg.
    if((*visitedStates) == NULL){
        printf("IT'S NULL AHHHHHHHHHHH!!!!!!!!!!!!!!!!!!!!!!-----******\n");
        (*visitedStates) = intArrayInit(10);
    }
    DFA* current = head;
    intArrayAdd((*visitedStates),head->state);
    printf("Visited: ");
    for(int i = 0; i < (*visitedStates)->used; i++){
        printf("%i,",(*visitedStates)->array[i]);
    }
    printf("\n");
    transition* currentTransition;
    for(int i = 0; i < current->transitions->used; i++){
        currentTransition = current->transitions->array[i];
        if(!intIn((*visitedStates),currentTransition->state->state)){
            DFAAndR(currentTransition->state,arg,visitedStates);
        }
    }
    if(current->isFinal){
        transitionArrayAdd(current->transitions,transitionInit('E',arg));
        current->isFinal = 0;
    }
    return head;
}

DFA* DFAAnd(DFA* head, DFA* arg){
    intArray* visited = NULL;
    DFAAndR(head, arg,&visited);  // Epsilon jump from all final states
    intArray* incr = NULL;
    incrementStates(arg,visited->used,&incr);
    intArrayFree(&visited);
    intArrayFree(&incr);
    return head; 
}

DFA* DFAOr(DFA* head, DFA* arg){
    
}

DFA* DFAStar(DFA* head, DFA* arg){

}

void DFAFreeR(DFA** head, intArray** visitedStates){
    if((*visitedStates) == NULL){
        (*visitedStates) = intArrayInit(10);
    }
    intArrayAdd((*visitedStates),(*head)->state);
    for(int i = 0; i < (*head)->transitions->used; i++){
        if(!intIn(*visitedStates,(*head)->transitions->array[i]->state->state)){
            DFAFreeR(&((*head)->transitions->array[i]->state),visitedStates);
        }
    }
    transitionArrayFree(&((*head)->transitions));
    free(*head);
    *head = NULL;
}


void DFAFree(DFA** head){
    intArray* arr = NULL;
    DFAFreeR(head,&arr);
    intArrayFree(&arr);
}

void printTransition(transitionArray* arr, char c){
    int has = 0;
    for(int i = 0; i < arr->used; i++){
        if(arr->array[i]->c == c){
            has +=2;
            printf("%i,",arr->array[i]->state->state);
        }    
    }
    for(int i = 0; i < 13-has;i++){
        printf(" ");
    }
    printf("|");
}

void printDFAR(DFA* head, intArray** visitedStates){
    char* sepp = "|-------------|-------------|-------------|-------------|-------------|-------------|-------------|\n";
    printf(sepp);
    printf("|      ");
    printf("%i      ",head->state);
    printf("|");
    if(*visitedStates == NULL){
        *visitedStates = intArrayInit(10);
    }
    intArrayAdd(*visitedStates,head->state);
    printTransition(head->transitions,'a');
    printTransition(head->transitions,'b');
    printTransition(head->transitions,'c');
    printTransition(head->transitions,'d');
    printTransition(head->transitions,'e');
    printTransition(head->transitions,'E');
    printf("\n");
    for(int i = 0; i < head->transitions->used; i++){
        if(!intIn(*visitedStates,head->transitions->array[i]->state->state)){
           printDFAR(head->transitions->array[i]->state,visitedStates); 
        }
    }

}

void printDFA(DFA* head){
    intArray* visitedStates = NULL;
    printf("|    STATE    |      a      |      b      |      c      |      d      |      e      |      E      |\n");
    printDFAR(head,&visitedStates);
    intArrayFree(&visitedStates);
}



