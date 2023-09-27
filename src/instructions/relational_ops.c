#include "program.h"

void ne(Program* program, char* args) {
    int second = stack_pop_value(program->stack);
    int first = stack_pop_value(program->stack);
    stack_push_value(program->stack, first != second);
}

void le(Program* program, char* args) {
    int second = stack_pop_value(program->stack);
    int first = stack_pop_value(program->stack);
    stack_push_value(program->stack, first <= second);
}

void ge(Program* program, char* args) {
    int second = stack_pop_value(program->stack);
    int first = stack_pop_value(program->stack);
    stack_push_value(program->stack, first >= second);
}

void lt(Program* program, char* args) {
    int second = stack_pop_value(program->stack);
    int first = stack_pop_value(program->stack);
    stack_push_value(program->stack, first < second);
}

void gt(Program* program, char* args) {
    int second = stack_pop_value(program->stack);
    int first = stack_pop_value(program->stack);
    stack_push_value(program->stack, first > second);
}

void eq(Program* program, char* args) {
    int second = stack_pop_value(program->stack);
    int first = stack_pop_value(program->stack);
    stack_push_value(program->stack, first == second);
}