#ifndef ABM_FUNCTIONS_H
#define ABM_FUNCTIONS_H

#include "program.h"

#define TOTAL_INSTRUCTIONS 35

typedef struct Function {
    char* instruction;
    void (*handler)(Program*, char*);
} Function;

typedef struct FunctionTable {
    Function* functions[TOTAL_INSTRUCTIONS];
    int total_functions;
} FunctionTable;

void add_to_function_table(FunctionTable* table, char* instruction, void (*handler)(Program*, char*));
FunctionTable* build_function_table();

#endif