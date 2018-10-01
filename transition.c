/* FUNCTIONALITY
 * 
 * This is the c file for the transition data structure. It will store the dfa that is transitioned to
 * when the character c is the next character in a string. This file will also contain the code
 * for a dynamically growing array that contains transitions. These arrays will be used by the DFA
 * data structure to store all of their transitions.
 *
*/
#include <stdlib.h>
#include "dataStructures.h"

transition* transitionInit(char c, DFA* target){
    transition* newTransition = (transition*)malloc(sizeof(transition));
    newTransition->c = c;
    newTransition->state = target;
    return newTransition;
}

void transitionFree(transition** t){
    free(*t);
    (*t) = NULL;
}

transitionArray* transitionArrayInit(int size){
    transitionArray* arr = (transitionArray*)malloc(sizeof(transitionArray));
    arr->array = (transition**)malloc(sizeof(transition*)*size);
    arr->size = size;
    arr->used = 0;
    return arr;
}

void transitionArrayAdd(transitionArray* arr, transition* t){
    if(arr->size == arr->used){
        arr->size *= 2;
        arr->array = (transition**)realloc(arr->array,sizeof(transition*)*arr->size);

    }
    arr->array[arr->used++] = t;
}

void transitionArrayFree(transitionArray** arr){
    for(int i = 0; i < (*arr)->used; i++){
        transitionFree(&((*arr)->array[i]));
    }
    free((*arr)->array);
    free(*arr);
    *arr = NULL;

}
