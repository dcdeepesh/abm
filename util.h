#ifndef ABM_UTIL_H
#define ABM_UTIL_H

#define new(structure) malloc(sizeof(structure))

#define BOOL int
#define FALSE 0
#define TRUE 1

// returns a copy of a stack string as a heap string
char* str(char* stack_str);
int get_variable(Program* program, char* var_name, BOOL address);

#endif