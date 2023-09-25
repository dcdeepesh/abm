#include "functions.h"

#include <stdlib.h>
#include "util.h"
#include "instructions/all.h"
#include "program.h"

void add_to_function_table(FunctionTable* table, char* instruction, void (*handler)(Program*, char*)) {
    Function* function = new(Function);
    function->instruction = instruction;
    function->handler = handler;

    table->functions[table->total_functions] = function;
    table->total_functions++;
}

FunctionTable* build_function_table() {
    FunctionTable* table = new(FunctionTable);
    table->functions = malloc(sizeof(Function*) * TOTAL_INSTRUCTIONS);
    table->total_functions = 0;

    add_to_function_table(table, "push", push);
    add_to_function_table(table, "rvalue", rvalue);
    add_to_function_table(table, "lvalue", lvalue);
    add_to_function_table(table, "pop", pop);
    add_to_function_table(table, ":=", assign);
    add_to_function_table(table, "copy", copy);

    add_to_function_table(table, "label", label);
    add_to_function_table(table, "goto", goto_);
    add_to_function_table(table, "gofalse", gofalse);
    add_to_function_table(table, "gotrue", gotrue);
    add_to_function_table(table, "halt", halt);

    add_to_function_table(table, "+", add);
    add_to_function_table(table, "-", subtract);
    add_to_function_table(table, "*", multiply);
    add_to_function_table(table, "/", divide);
    add_to_function_table(table, "div", rem);

    add_to_function_table(table, "&", and_);
    add_to_function_table(table, "!", not_);
    add_to_function_table(table, "|", or_);

    add_to_function_table(table, "<>", ne);
    add_to_function_table(table, "<=", le);
    add_to_function_table(table, ">=", ge);
    add_to_function_table(table, "<", lt);
    add_to_function_table(table, ">", gt);
    add_to_function_table(table, "=", eq);

    add_to_function_table(table, "print", print);
    add_to_function_table(table, "show", show);

    add_to_function_table(table, "begin", begin);
    add_to_function_table(table, "end", end);
    add_to_function_table(table, "return", return_);
    add_to_function_table(table, "call", call);
}