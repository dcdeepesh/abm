#include <stdlib.h>
#include <string.h>
#include "program.h"
#include "util.h"

void push(Program* program, char* args) {
    stack_push_value(program->stack, atoi(args));
}

// TODO uses stack_base
// Helper function for lvalue() and rvalue()
int get_variable(Program* program, char* var_name, BOOL address, BOOL callerOnly, BOOL calleeOnly) {
    FunctionContext* fc = program->stack->values[program->stack_base + 2].fc_ptr;

    if (!calleeOnly) {
        for (int i = 0; i < fc->total_variables; i++) {
            if (strcmp(fc->variables[i]->name, var_name) == 0) {
                return address ? i : fc->variables[i]->value;
            }
        }
    }

    if (!callerOnly) {
        if (program->callee_fc != NULL) {
            for (int i = 0; i < program->callee_fc->total_variables; i++) {
                if (strcmp(program->callee_fc->variables[i]->name, var_name) == 0) {
                    return address ? (i + 60000) : program->callee_fc->variables[i]->value;
                }
            }
        }
    }

    // Variable doesn't exist. Make one
    Variable* variable = new(Variable);
    variable->name = var_name;
    variable->value = 0;
    int new_var_address = 0;
    // If we're in a begin...end block, the new
    // variable is a paremeter to the callee
    if (program->callee_fc != NULL && program->call_pending) {
        fc = program->callee_fc;
        // An offset of 60000 to distinguish local variables
        // from callee's parameters
        new_var_address += 60000;
    }
    
    new_var_address += fc->total_variables;
    fc->variables[fc->total_variables] = variable;
    fc->total_variables++;

    return address ? new_var_address : 0;
}

void rvalue(Program* program, char* args) {
    stack_push_value(program->stack, get_variable(program, args, FALSE, FALSE, FALSE));
}

void lvalue(Program* program, char* args) {
    BOOL callerOnly = FALSE;
    BOOL calleeOnly = FALSE;

    if (program->callee_fc != NULL) {
        if (program->call_pending) {
            calleeOnly = TRUE;
        } else {
            callerOnly = TRUE;
        }
    }

    stack_push_value(program->stack, get_variable(program, args, TRUE, callerOnly, calleeOnly));
}

void pop(Program* program, char* args) {
    stack_pop_value(program->stack);
}

// TODO uses stack_base
// Helper function for assign()
// Handles both callee's and current FCs
void set_variable(Program* program, int address, int value) {
    // An offset of 60000 to distinguish local variables from callee's parameters
    if (address >= 60000) {
        program->callee_fc->variables[address - 60000]->value = value;
    } else {
        FunctionContext* current_fc =
            program->stack->values[program->stack_base + 2].fc_ptr;
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