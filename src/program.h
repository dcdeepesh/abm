#ifndef ABM_PROGRAM_H
#define ABM_PROGRAM_H

#include "util.h"
#include "stack.h"

#define PARSER_MAX_LINES 1024
#define PARSER_MAX_LINE_LENGTH 256
#define PARSER_MAX_LABELS 256

typedef struct Line {
    char* op;
    char* args;
} Line;

typedef struct Label {
    char* label;
    int line_number; // zero-indexed!
} Label;

typedef struct Program {
    Line* lines[PARSER_MAX_LINES];
    int total_lines; 
    Label* labels[PARSER_MAX_LABELS];
    int total_labels;

    int ip;
    Stack* stack;
    int stack_base;
    FunctionContext* callee_fc;
    BOOL call_pending;
} Program;

#endif