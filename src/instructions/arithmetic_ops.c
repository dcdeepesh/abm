#include "program.h"

void add(Program* program, char* args) {
    int second = stack_pop_value(program->stack);
    int first = stack_pop_value(program->stack);
    stack_push_value(program->stack, first + second);
}

void subtract(Program* program, char* args) {
    int second = stack_pop_value(program->stack);
    int first = stack_pop_value(program->stack);
    stack_push_value(program->stack, first - second);
}

void multiply(Program* program, char* args) {
    int second = stack_pop_value(program->stack);
    int first = stack_pop_value(program->stack);
    stack_push_value(program->stack, first * second);
}

void divide(Program* program, char* args) {
    int second = stack_pop_value(program->stack);
    int first = stack_pop_value(program->stack);
    stack_push_value(program->stack, first / second);
}

void rem(Program* program, char* args) {
    int second = stack_pop_value(program->stack);
    int first = stack_pop_value(program->stack);
    stack_push_value(program->stack, first % second);
}