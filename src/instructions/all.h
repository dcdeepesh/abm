#ifndef ABM_INSTRUCTIONS_H
#define ABM_INSTRUCTIONS_H

#include "program.h"

void add(Program* program, char* args);
void subtract(Program* program, char* args);
void multiply(Program* program, char* args);
void divide(Program* program, char* args);
void rem(Program* program, char* args);

void label(Program* program, char* args);
void goto_(Program* program, char* args);
void gofalse(Program* program, char* args);
void gotrue(Program* program, char* args);
void halt(Program* program, char* args);

void and_(Program* program, char* args);
void not_(Program* program, char* args);
void or_(Program* program, char* args);

void print(Program* program, char* args);
void show(Program* program, char* args);

void ne(Program* program, char* args);
void le(Program* program, char* args);
void ge(Program* program, char* args);
void lt(Program* program, char* args);
void gt(Program* program, char* args);
void eq(Program* program, char* args);

void push(Program* program, char* args);
void rvalue(Program* program, char* args);
void lvalue(Program* program, char* args);
void pop(Program* program, char* args);
void assign(Program* program, char* args);
void copy(Program* program, char* args);

void begin(Program* program, char* args);
void end(Program* program, char* args);
void return_(Program* program, char* args);
void call(Program* program, char* args);

void int_(Program* program, char* args);
void dot_data(Program* program, char* args);
void dot_text(Program* program, char* args);

#endif