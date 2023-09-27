#include <stdio.h>

#include "program.h"

void print(Program* program, char* args) {
    printf("%d\n", stack_peek_value(program->stack));
}

void show(Program* program, char* args) {
    printf("%s\n", args);
}