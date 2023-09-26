#include "stack.h"

#include <stdlib.h>
#include "util.h"
#include "program.h"

Stack* create_stack(Program* program) {
    Stack* stack = new(Stack);
    stack->values = malloc(sizeof(StackValue) * STACK_MAX_VALUES);
    stack->top = 0;

    // push the initial "previous" stack base (dummy)
    stack_push_value(stack, -1);

    // push the initial return ip (dummy)
    stack_push_value(stack, -1);

    // push the initial function context
    FunctionContext* fc = new(FunctionContext);
    fc->variables = malloc(sizeof(Variable) * FC_MAX_VARIABLES);
    fc->total_variables = 0;
    stack_push_fc(stack, fc);

    return stack;
}

void stack_push_value(Stack* stack, int value) {
    StackValue sv;
    sv.i_value = value;
    stack->values[stack->top] = sv;
    stack->top++;
}

void stack_push_fc(Stack* stack, FunctionContext* fc) {
    StackValue sv;
    sv.fc_ptr = fc;
    stack->values[stack->top] = sv;
    stack->top++;
}

int stack_pop_value(Stack* stack) {
    stack->top--;
    return stack->values[stack->top].i_value;
}

FunctionContext* stack_pop_fc(Stack* stack) {
    stack->top--;
    return stack->values[stack->top].fc_ptr ;
}

int stack_peek_value(Stack* stack) {
    return stack->values[stack->top - 1].i_value;
}