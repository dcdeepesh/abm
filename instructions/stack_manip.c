#include <stdlib.h>
#include <string.h>
#include "program.h"

void push(Program* program, char* args) {
    stack_push_value(program->stack, atoi(args));
}

// TODO stack base is used. re-check after implementing subroutines

void rvalue(Program* program, char* args) {
    StackValue sv = program->stack->values[program->stack_base - 2];
    FunctionContext* current_fc = sv.fc_ptr;

    for (int i = 0; i < current_fc->total_variables; i++) {
        if (strcmp(current_fc->variables[i]->name, args) == 0) {
            stack_push_value(program->stack, current_fc->variables[i]->value);
            return;
        }
    }

    Variable* variable = new(Variable);
    variable->name = args;
    variable->value = 0;
    current_fc->variables[current_fc->total_variables] = variable;
    current_fc->total_variables++;
    
    stack_push_value(program->stack, 0);
}

void lvalue(Program* program, char* args) {
    StackValue sv = program->stack->values[program->stack_base - 2];
    FunctionContext* fc = sv.fc_ptr;

    for (int i = 0; i < fc->total_variables; i++) {
        if (strcmp(fc->variables[i]->name, args) == 0) {
            stack_push_value(program->stack, i);
            return;
        }
    }

    Variable* variable = new(Variable);
    variable->name = args;
    variable->value = 0;
    fc->variables[fc->total_variables] = variable;
    
    stack_push_value(program->stack, fc->total_variables);
    fc->total_variables++;
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