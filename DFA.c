/* FUNCTIONALITY
 *
 * This file contains the code responsible for building the DFA in memory from
 * supplied regex information.
 *
*/
#include <stdlib.h>
#include "dataStructures.h"
#include <stdio.h>
#include <math.h>

DFA* DFAinit(int state, int isFinal){       // Initialize a new DFA data structure (really an NFA, but oh well.)
    DFA* d = (DFA*)malloc(sizeof(DFA));
    d->transitions = transitionArrayInit(10);   // Each NFA needs a transition array.
    d->state = state;
    d->isFinal = isFinal;
    return d;
}

void incrementStates(DFA* head, int amount, intArray** visitedStates){ // Increments all the state values in the NFA by the given value.
    if((*visitedStates) == NULL){                                      // This ensure that all DFA's will have unique names
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
        (*visitedStates) = intArrayInit(10);
    }
    DFA* current = head;
    intArrayAdd((*visitedStates),head->state);
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
    DFA* newStart = DFAinit(-1,0);
    intArray* incr = NULL;
    int x = DFANodeCount(head);
    incrementStates(arg,x,&incr);
    clearArray(incr);
    transitionArrayAdd(newStart->transitions,transitionInit('E',head));    
    transitionArrayAdd(newStart->transitions,transitionInit('E',arg));
    incrementStates(newStart,1,&incr);
    intArrayFree(&incr);
    return newStart;
}

DFA* DFAStarR(DFA* head, DFA* start, intArray** visitedStates){
    // Add an epsilon jump from each Final state in head to the start state.
    if((*visitedStates) == NULL){
        (*visitedStates) = intArrayInit(10);
    }
    DFA* current = head;
    intArrayAdd((*visitedStates),head->state);
    transition* currentTransition;
    for(int i = 0; i < current->transitions->used; i++){
        currentTransition = current->transitions->array[i];
        if(!intIn((*visitedStates),currentTransition->state->state)){
            DFAStarR(currentTransition->state,start,visitedStates);
        }
    }
    if(current->isFinal){
        transitionArrayAdd(current->transitions,transitionInit('E',start));
    }
    return head;
}

DFA* DFAStar(DFA* head){
    intArray* visited = NULL;
    DFAStarR(head, head,&visited);  // Epsilon jump from all final states
    intArrayFree(&visited);
    return head; 
}

DFA* DFAGen(char c){    // Returns a DFA/NFA that accepts the given character.

    DFA* start = DFAinit(0,0);
    DFA* end = DFAinit(1,1);
    transitionArrayAdd(start->transitions,transitionInit(c,end));
    return start;

}

void DFAFreeR(DFA** head, DFAArray** visitedStates){
    if((*visitedStates) == NULL){
        (*visitedStates) = DFAArrayInit(10);
    }
    /*printf("State: %i  ",(*head)->state);
    for(int i = 0; i < (*visitedStates)->used; i++){
        printf("%i, ",(*visitedStates)->array[i]);
    }
    printf("\n");*/
    DFAArrayAdd((*visitedStates),(*head));
    //printf("Used: %i \n",(*head)->transitions->used);
    for(int i = 0; i < (*head)->transitions->used; i++){
        if(!DFAIn(*visitedStates,(*head)->transitions->array[i]->state)){
            //printf("Going to %p \n",(*head)->transitions->array[i]->state);
            DFAFreeR(&((*head)->transitions->array[i]->state),visitedStates);
        }
    }
    if(*head != NULL){
        transitionArrayFree(&((*head)->transitions));
        free(*head);
        *head = NULL;
    }
}


void DFAFree(DFA** head){
    DFAArray* arr = NULL;
    DFAFreeR(head,&arr);
    DFAArrayFree(&arr);
    *head = NULL;
}

int intLength(int i){
    if(i == 0){
        return 1;
    }
    return floor(log10(i))+1;

}

void printTransition(transitionArray* arr, char c){
    int has = 0;
    for(int i = 0; i < arr->used; i++){
        if(arr->array[i]->c == c){
            has += 1+intLength(arr->array[i]->state->state);
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
    int length = 13-intLength(head->state);
    if(!head->isFinal){
        printf("|");
        printf("%i",head->state);
        for(int i = 0; i < length; i++){
            printf(" ");
        }
        printf("|");
       
    }else{
        printf("|");
        printf("%i",head->state);
        for(int i = 0; i < length; i++){
            printf("F");
        }
        printf("|");
    }
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
    printf("|-------------|-------------|-------------|-------------|-------------|-------------|-------------|\n");
    intArrayFree(&visitedStates);
}

void DFANodeCountR(DFA* head, int* count, intArray** visitedStates){
    if(*visitedStates == NULL){
        *visitedStates = intArrayInit(10);
    }
    intArrayAdd(*visitedStates,head->state);
    (*count)++;
    for(int i = 0; i < head->transitions->used; i++){
        if(!intIn(*visitedStates,head->transitions->array[i]->state->state)){
            DFANodeCountR(head->transitions->array[i]->state,count,visitedStates);
        }
    }
}

int DFANodeCount(DFA* head){
    int count = 0;
    intArray* visited = NULL;
    DFANodeCountR(head,&count, &visited);
    intArrayFree(&visited);
    return count;
}


