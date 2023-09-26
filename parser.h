#ifndef ABM_PARSER_H
#define ABM_PARSER_H

#include <stdio.h>
#include "program.h"

Program* parse_file(FILE *file);
Line* parse_line(char* line);
void check_label(Program* program, int line_number);

#endif