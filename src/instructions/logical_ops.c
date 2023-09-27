#include "program.h"

void and_(Program* program, char* args) {
    int second = stack_pop_value(program->stack);
    int first = stack_pop_value(program->stack);
    stack_push_value(program->stack, first & second);
}

void not_(Program* program, char* args) {
    int first = stack_pop_value(program->stack);
    stack_push_value(program->stack, !first);
}

void or_(Program* program, char* args) {
    int second = stack_pop_value(program->stack);
    int first = stack_pop_value(program->stack);
    stack_push_value(program->stack, first | second);
}