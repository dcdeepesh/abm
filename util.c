#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "program.h"

char* str(char* stack_str) {
    char* heap_str = malloc(strlen(stack_str) + 1);
    strcpy(heap_str, stack_str);
    return heap_str;
}

void trim_end(char* str) {
    int index = 0;
    while (str[index] != '\0') {
        index++;
    }

    if (index == 0) {
        // empty string
        return;
    }

    index--;
    // go to the character before the first non-whitespace character
    // (this could mean we're one character before the string's beginning)
    while (index >= 0 && isspace(str[index])) {
        index--;
    }
    
    // the next character (which will be the first whitespace character)
    // is where the string now ends
    str[index+1] = '\0';
}