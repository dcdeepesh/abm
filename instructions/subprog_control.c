#include <stdlib.h>
#include "program.h"
#include "stack.h"
#include "util.h"
#include "instructions/all.h"

// Create a callee FC
void begin(Program* program, char* args) {
    FunctionContext* callee_fc = new(FunctionContext);
    callee_fc->total_variables = 0;
    program->callee_fc = callee_fc;
    program->call_pending = TRUE;
}

// Destroy the callee FC
void end(Program* program, char* args) {
    for (int i = 0; i < program->callee_fc->total_variables; i++) {
        free(program->callee_fc->variables[i]);
    }
    free(program->callee_fc);
    program->callee_fc = NULL;
}

void return_(Program* program, char* args) {
    int return_ip = program->stack->values[program->stack_base + 1].i_value;
    program->ip = return_ip;
    
    FunctionContext* callee_fc = program->stack->values[program->stack_base + 2].fc_ptr;
    program->callee_fc = callee_fc;

    program->stack->top = program->stack_base;
    program->stack_base = program->stack->values[program->stack_base].i_value;
}

void call(Program* program, char* args) {
    int new_stack_base = program->stack->top;

    stack_push_value(program->stack, program->stack_base);
    stack_push_value(program->stack, program->ip);
    stack_push_fc(program->stack, program->callee_fc);

    program->stack_base = new_stack_base;
    program->callee_fc = NULL;
    program->call_pending = FALSE;

    goto_(program, args);
}