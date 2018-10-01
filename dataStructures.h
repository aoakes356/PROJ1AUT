#ifndef AUT_DATA_STRUCTURES
#define AUT_DATA_STRUCTURES



#define MAX_STACK_POINTER 300
#include <stdlib.h>

typedef struct stack {
    int stackptr;
    int stackarr[MAX_STACK_POINTER];
} stack;

typedef struct transitionArray transitionArray;

typedef struct DFA {
    int state;
    transitionArray* transitions;
    int isFinal;
} DFA;

typedef struct transition {
    char c;
    DFA* state;
} transition;

typedef struct transitionArray{
    transition** array;
    size_t used;        // Effectively a stack pointer.
    size_t size;
}transitionArray;

typedef struct intArray{
    int* array;
    size_t used;        // Effectively a stack pointer.
    size_t size;
}intArray;


/* Stack Code */
stack* stackInit();
int push(stack* s,char c);
char pop(stack* s);
void stackFree(stack* s);
int isMT(stack* s);

/* DFA Code */
void incrementStates(DFA* head, int amount, intArray** visitedStates);
DFA* DFAinit(int state, int isFinal);
DFA* DFAAnd(DFA* head, DFA* arg);
DFA* DFAAndR(DFA* head, DFA* arg, intArray** visitedStates);
DFA* DFAOr(DFA* head, DFA* arg);
DFA* DFAStar(DFA* head, DFA* arg);
void DFAFree(DFA** head);
void printDFA(DFA* head);

/* Transition code */

transition* transitionInit(char c, DFA* target);
void transitionFree(transition** t);

/* Transition array code */

transitionArray* transitionArrayInit(int size);
void transitionArrayAdd(transitionArray* arr, transition* t);
void transitionArrayFree(transitionArray** arr);

/* Integer Array Code */

intArray* intArrayInit(int size);
void intArrayAdd(intArray* arr, int t);
int intIn(intArray* arr, int t);
void intArrayFree(intArray** arr);
void clearArray(intArray* arr);

#endif
