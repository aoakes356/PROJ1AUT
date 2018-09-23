/* FUNCTIONALITY
 *
 * Takes a string, checks if it is made of valid characters
 * also checks if the string has a potentially functional
 * regex. Does not guarantee that is the case until it is fully
 * converted into a dfa.
 *
*/

#include "regexToDFA.h"
#include <string.h>
char ALPHABET[9] = {'a','b','c','d','e','E','|','&','*'};
int isMember(char c){   // Checks if the character is a member of the alphabet
    for(int i = 0; i < 9; i++){
        if(ALPHABET[i] == c){
            return 1;
        }
    }
    return 0;
}

int isAlphabet(char c){
    for(int i = 0; i < 6; i++){
        if(ALPHABET[i] == c){
            return 1;
        }
    }
    return 0;
}

int isOp(char c){
    for(int i = 6; i < 9;i++){
        if(ALPHABET[i] ==  c){
            return 1;
        }
    }
    return 0;
}

int isRegex(char* reg, int len){
    // The number of operators should be one less than the number of operators
    // the exception being '*'.
    int op = 0, let = 0;
    char current;
    for(int i = 0; i < len && reg[i] != '\0'; i++){
        current = reg[i];
        if(isOp(current) && current != '*'){
            op++;
        }else if(isMember(current) && current != '*'){
            let++;
        }
    }
    if(op+1 == let){
        return 1;
    }
    return 0;
}



