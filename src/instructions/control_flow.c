#include "program.h"

#include <stdlib.h>
#include <string.h>

void label(Program* program, char* args) {
    // Nothing to do here.
    // All labels were read and stored in the first pass.
}

void goto_(Program* program, char* args) {
    int new_ip = -1;

    for (int i = 0; i < program->total_labels; i++) {
        Label* label = program->labels[i];
        if (strcmp(label->label, args) == 0) {
            new_ip = label->line_number;
            break;
        }
    }

    if (new_ip == -1) {
        exit(3);
    } else {
        program->ip = new_ip;
    }
}

void gofalse(Program* program, char* args) {
    if (stack_pop_value(program->stack) == 0) {
        goto_(program, args);
    }
}

void gotrue(Program* program, char* args) {
    if (stack_pop_value(program->stack) != 0) {
        goto_(program, args);
    }
}

void halt(Program* program, char* args) {
    exit(0);
}