#include <stdlib.h>
#include <string.h>

char* str(char* stack_str) {
    char* heap_str = malloc(strlen(stack_str) + 1);
    strcpy(heap_str, stack_str);
    return heap_str;
}