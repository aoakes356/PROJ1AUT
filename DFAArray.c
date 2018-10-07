/* FUNCTIONALITY
 *
 * This file contains the code for creating an array/stack of DFA's
 * To be used when parsing a string supposed to be a Regex into an NFA/DFA
 *
*/

#include "dataStructures.h"

DFAArray* DFAArrayInit(int size){
    DFAArray* arr = (DFAArray*)malloc(sizeof(DFAArray));
    arr->array = (DFA**)malloc(sizeof(DFA*)*size);
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

DFA* DFAPop(DFAArray* arr){
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

void clearDFAArray(DFAArray* arr){
    arr->used = 0;
}


