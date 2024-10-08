#ifndef ABM_STACK_H
#define ABM_STACK_H

typedef struct Program Program;
#include "util.h"

#define FC_MAX_VARIABLES 128

typedef struct Variable {
    char* name;
    int value;
} Variable;

typedef struct FunctionContext {
    Variable* variables[FC_MAX_VARIABLES];
    int total_variables;
} FunctionContext;

#define STACK_MAX_VALUES 1024

typedef union StackValue {
    int i_value;
    FunctionContext* fc_ptr;
} StackValue;

typedef struct Stack {
    StackValue values[STACK_MAX_VALUES];
    int top;
} Stack;

Stack* create_stack(Program* program);

void stack_push_value(Stack* stack, int value);
void stack_push_fc(Stack* stack, FunctionContext* fc);
int stack_pop_value(Stack* stack);
FunctionContext* stack_pop_fc(Stack* stack);
int stack_peek_value(Stack* stack);

#endif