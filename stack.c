#include "dataStructures.h"
#include <stdio.h>
#include <stdlib.h>

stack* stackInit(){
    stack* s = (stack*)malloc(sizeof(stack));
    s->stackptr = 0;
    return s;
}

int push(stack* s,char c){
    if(s->stackptr < 300){
        s->stackarr[s->stackptr++] = c;
        return 1;
    }
    return 0;
}

char pop(stack* s){
    return s->stackarr[--s->stackptr];
}

void stackFree(stack* s){
    if(s != NULL){
        free(s);
    }
}
