#include <string.h>
#include "program.h"
#include "util.h"

void create_global_variable(Program* program, char* var_name) {
    Variable* variable = new(Variable);
    variable->names[variable->total_names] = var_name;
    variable->total_names++;
    variable->value = 0;

    program->global_variables[program->total_global_variables] = variable;
    program->total_global_variables++;
}

void int_(Program* program, char* args) {
    char *var_name = strtok(args, " ");
    while (var_name) {
        create_global_variable(program, var_name);
        var_name = strtok(NULL, " ");
    }
}

void dot_data(Program* program, char* args) {
}

void dot_text(Program* program, char* args) {
}

Variable* get_variable_from_address(Program* program, int address) {
    // An offset of 61000 to indicate global variables
    if (address >= 61000) {
        return program->global_variables[address - 61000];;
    }
    // An offset of 60000 to indicate callee's parameters
    else if (address >= 60000) {
        return program->callee_fc->variables[address - 60000];
    } else {
        FunctionContext* current_fc =
            program->stack->values[program->stack_base + 2].fc_ptr;
        return current_fc->variables[address];
    }
}

void lvalue_assign(Program* program, char* args) {
    int right = stack_pop_value(program->stack);
    int left = stack_pop_value(program->stack);

    Variable* lv = get_variable_from_address(program, left);
    Variable* rv = get_variable_from_address(program, right);

    for (int i = 0; i < lv->total_names; i++) {
        rv->names[rv->total_names] = lv->names[i];
        rv->total_names++;
    }
    lv->total_names = 0;
}