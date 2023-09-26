#include <stdlib.h>
#include <string.h>
#include "program.h"
#include "util.h"

void push(Program* program, char* args) {
    stack_push_value(program->stack, atoi(args));
}

void rvalue(Program* program, char* args) {
    stack_push_value(program->stack, get_variable(program, args, FALSE));
}

void lvalue(Program* program, char* args) {
    stack_push_value(program->stack, get_variable(program, args, TRUE));
}

void pop(Program* program, char* args) {
    stack_pop_value(program->stack);
}

void assign(Program* program, char* args) {
    int value = stack_pop_value(program->stack);
    int address = stack_pop_value(program->stack);
    FunctionContext* current_fc = program->stack->values[program->stack_base - 2].fc_ptr;
    current_fc->variables[address]->value = value;
}

void copy(Program* program, char* args) {
    stack_push_value(program->stack, stack_peek_value(program->stack));
}