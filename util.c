#include <stdlib.h>
#include <string.h>
#include "program.h"

char* str(char* stack_str) {
    char* heap_str = malloc(strlen(stack_str) + 1);
    strcpy(heap_str, stack_str);
    return heap_str;
}

// TODO uses stack_base
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