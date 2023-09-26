#include <stdlib.h>
#include <string.h>
#include "program.h"
#include "util.h"

void push(Program* program, char* args) {
    stack_push_value(program->stack, atoi(args));
}

// TODO uses stack_base
// Helper function for lvalue() and rvalue()
int get_variable(Program* program, char* var_name, BOOL address) {
    StackValue sv = program->stack->values[program->stack_base - 2];
    FunctionContext* current_fc = sv.fc_ptr;

    for (int i = 0; i < current_fc->total_variables; i++) {
        if (strcmp(current_fc->variables[i]->name, var_name) == 0) {
            return address ? i : current_fc->variables[i]->value;
        }
    }

    // Variable doesn't exist. Make one
    Variable* variable = new(Variable);
    variable->name = var_name;
    variable->value = 0;
    int new_var_address = current_fc->total_variables;
    current_fc->variables[new_var_address] = variable;
    current_fc->total_variables++;

    return address ? new_var_address : 0;
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