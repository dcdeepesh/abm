#include <string.h>
#include "program.h"
#include "util.h"

void create_global_variable(Program* program, char* var_name) {
    Variable* variable = new(Variable);
    variable->name = var_name;
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