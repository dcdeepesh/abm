#include <stdlib.h>
#include "program.h"
#include "stack.h"
#include "util.h"

// Create a callee FC
void begin(Program* program, char* args) {
    FunctionContext* callee_fc = new(FunctionContext);
    callee_fc->variables = malloc(sizeof(Variable) * FC_MAX_VARIABLES);
    callee_fc->total_variables = 0;
    program->callee_fc = callee_fc;
}

// Destroy the callee FC
void end(Program* program, char* args) {
    for (int i = 0; i < program->callee_fc->total_variables; i++) {
        free(program->callee_fc->variables[i]);
    }
    free(program->callee_fc->variables);
    free(program->callee_fc);
    program->callee_fc = NULL;
}

void return_(Program* program, char* args) {

}

void call(Program* program, char* args) {

}