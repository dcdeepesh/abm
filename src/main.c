#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#include "util.h"
#include "parser.h"
#include "program.h"
#include "functions.h"
#include "stack.h"

void run_program(Program* program, FunctionTable* ftable);

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: abm <abm-source-file>\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("ERR: Unable to open file (errno=%d)\n", errno);
        return 2;
    }

    Program* program = parse_file(file);
    program->ip = 0;
    program->callee_fc = NULL;
    Stack* stack = create_stack(program);
    program->stack = stack;
    program->stack_base = 0;

    FunctionTable* ftable = build_function_table();

    run_program(program, ftable);

    return 0;
}

void run_program(Program* program, FunctionTable* ftable) {
    while (program->ip < program->total_lines) {
        Line* curr_line = program->lines[program->ip];
        
        program->ip++;
        
        int findex;
        for (findex = 0; findex < ftable->total_functions; findex++) {
            Function* curr_func = ftable->functions[findex];
            if (strcmp(curr_line->op, curr_func->instruction) == 0) {
                (*(curr_func->handler))(program, curr_line->args);
                break;
            }
        }
        if (findex == ftable->total_functions) {
            printf("ERR: No function found for the instruction '%s'\n", curr_line->op);
            exit(3);
        }
    }
}