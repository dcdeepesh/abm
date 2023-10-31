#ifndef ABM_UTIL_H
#define ABM_UTIL_H

#include <stdlib.h>

#define new(structure) malloc(sizeof(structure))

#define BOOL int
#define FALSE 0
#define TRUE 1

// returns a copy of a stack string as a heap string
char* str(char* stack_str);
void trim_end(char* str);

#endif