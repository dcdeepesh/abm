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
    FunctionContext* fc = sv.fc_ptr;

    for (int i = 0; i < fc->total_variables; i++) {
        if (strcmp(fc->variables[i]->name, var_name) == 0) {
            return address ? i : fc->variables[i]->value;
        }
    }
    // If we're in a begin...end block, look in callee's FC too, for params
    if (program->callee_fc != NULL) {
        fc = program->callee_fc;
        for (int i = 0; i < fc->total_variables; i++) {
            if (strcmp(fc->variables[i]->name, var_name) == 0
                && fc->variables[i]->parameter) {
                // An offset of 1000 to distinguish local variables
                // from callee's parameters
                return address ? (i + 1000) : fc->variables[i]->value;
            }
        }
    }

    // Variable doesn't exist. Make one
    Variable* variable = new(Variable);
    variable->name = var_name;
    variable->value = 0;
    // If we're in a begin...end block, the new
    // variable is a paremeter to the callee
    if (program->callee_fc != NULL) {
        variable->parameter = TRUE;
    }
    
    int new_var_address = fc->total_variables;
    fc->variables[new_var_address] = variable;
    fc->total_variables++;

    if (program->callee_fc != NULL) {
        // An offset of 1000 to distinguish local variables
        // from callee's parameters
        new_var_address += 1000;
    }
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

// TODO uses stack_base
// Helper function for assign()
// Handles both callee's and current FCs
void set_variable(Program* program, int address, int value) {
    // An offset of 1000 to distinguish local variables from callee's parameters
    if (address >= 1000) {
        program->callee_fc->variables[address - 1000]->value = value;
    } else {
        FunctionContext* current_fc =
            program->stack->values[program->stack_base - 2].fc_ptr;
        current_fc->variables[address]->value = value;
    }
}

void assign(Program* program, char* args) {
    int value = stack_pop_value(program->stack);
    int address = stack_pop_value(program->stack);
    set_variable(program, address, value);
}

void copy(Program* program, char* args) {
    stack_push_value(program->stack, stack_peek_value(program->stack));
}