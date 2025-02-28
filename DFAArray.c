/* FUNCTIONALITY
 *
 * This file contains the code for creating an array/stack of DFA's
 * To be used when parsing a string supposed to be a Regex into an NFA/DFA
 *
*/

#include "dataStructures.h"

DFAArray* DFAArrayInit(int size){   // Initialize an expandable array of NFAs
    DFAArray* arr = (DFAArray*)malloc(sizeof(DFAArray));
    arr->array = (DFA**)malloc(sizeof(DFA*)*size);      // Initialize the array of DFA pointers.
    arr->size = size;
    arr->used = 0;
    return arr;
}

void DFAArrayAdd(DFAArray* arr, DFA* t){    // Add is effectively a push.
    if(arr->size == arr->used){
        arr->size *= 2;
        arr->array = (DFA**)realloc(arr->array,sizeof(DFA*)*arr->size);
    }
    arr->array[arr->used++] = t;
}

DFA* DFAPop(DFAArray* arr){ // Remove the last element of the array or "top of the stack" and return its value.
    if(arr->used > 0){
        return arr->array[--arr->used];
    }else{
        return (DFA*)NULL;
    }
}

void DFAArrayFree(DFAArray** arr){  // Not responsible for freeing DFA's
    free((*arr)->array);
    free(*arr);
    *arr = NULL;
}

int DFAIn(DFAArray* arr, DFA* dfa){     // Checks if the DFA array contains a given pointer.
    for(int i = 0; i < arr->used; i++){
        if(arr->array[i] == dfa){
            return 1;
        }
    }
    return 0;
}

void clearDFAArray(DFAArray* arr){      // Simply set used to 0 so the next element to be used is 0.
    arr->used = 0;
}


