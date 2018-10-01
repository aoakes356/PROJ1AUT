/* FUNCTIONALITY
 *
 * Boilerplate dynamic array for holding integer
 *
*/

#include<stdlib.h>
#include "dataStructures.h"

intArray* intArrayInit(int size){
    intArray* arr = (intArray*)malloc(sizeof(intArray));
    arr->array = (int*)malloc(sizeof(int)*size);
    arr->size = size;
    arr->used = 0;
    return arr;
}

void intArrayAdd(intArray* arr, int t){
    if(arr->size == arr->used){
        arr->size *= 2;
        arr->array = (int*)realloc(arr->array,sizeof(int)*arr->size);
    }
    arr->array[arr->used++] = t;
}

int intIn(intArray* arr, int t){
    for(int i = 0; i < arr->used; i++){
        if(arr->array[i] == t){
            return 1;
        }
    }
    return 0;
}

void clearArray(intArray* arr){
    arr->used = 0;
}

void intArrayFree(intArray** arr){
    free((*arr)->array);
    free(*arr);
}
