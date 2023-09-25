#ifndef ABM_PARSER_H
#define ABM_PARSER_H

#include <stdio.h>
#include "program.h"

static const int PARSER_MAX_LINES = 1024;
static const int PARSER_MAX_LINE_LENGTH = 256;
static const int PARSER_MAX_LABELS = 256;

Program* parse_file(FILE *file);
Line* parse_line(char* line);
void check_label(Program* program, int line_number);

#endif