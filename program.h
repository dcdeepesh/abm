#ifndef ABM_PROGRAM_H
#define ABM_PROGRAM_H

#include "stack.h"

typedef struct Line {
    char* op;
    char* args;
} Line;

typedef struct Label {
    char* label;
    int line_number; // zero-indexed!
} Label;

typedef struct Program {
    Line** lines;
    int total_lines; 
    Label** labels;
    int total_labels;

    int ip;
    Stack* stack;
    int stack_base;
    FunctionContext* callee_fc;
} Program;

#endif