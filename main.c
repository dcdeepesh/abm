#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#include "util.h"
#include "parser.h"
#include "program.h"
#include "functions.h"
#include "stack.h"

void run_program(Program* program);

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

    Stack* stack = create_stack(program);
    program->stack = stack;
    program->stack_base = stack->top;

    // for (int i = 0; i < program->total_lines; i++) {
    //     printf("%3d: [%s] [%s]\n", i+1, program->lines[i]->op, program->lines[i]->args);
    // }

    run_program(program);

    return 0;
}

void run_program(Program* program) {
    FunctionTable* ftable = build_function_table();

    while (program->ip < program->total_lines) {
        Line* curr_line = program->lines[program->ip];
        
        program->ip++;

        // skip if empty line
        if (strlen(curr_line->op) == 0) {
            continue;
        }
        
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