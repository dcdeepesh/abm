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

void lvalue_assign(Program* program, char* args) {
    
}