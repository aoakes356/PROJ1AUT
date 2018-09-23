#ifndef AUT_DATA_STRUCTURES
#define AUT_DATA_STRUCTURES



#define MAX_STACK_POINTER 300

typedef struct stack{
    int stackptr;
    int stackarr[MAX_STACK_POINTER];
} stack;

stack* stackInit();
int push(stack* s,char c);
char pop(stack* s);
void stackFree(stack* s);
int isMT(stack* s);








#endif
