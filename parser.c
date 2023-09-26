#include "parser.h"

#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

Program* parse_file(FILE *file) {
    Program* program = malloc(sizeof(Program));
    program->lines = malloc(sizeof(Line*) * PARSER_MAX_LINES);
    program->labels = malloc(sizeof(Label*) * PARSER_MAX_LABELS);
    program->total_labels = 0;

    char line_buf[PARSER_MAX_LINE_LENGTH];
    int line_no = 0;
    while (fgets(line_buf, PARSER_MAX_LINE_LENGTH, file) != NULL) {
        Line* parsed_line = parse_line(line_buf);
        
        // skip if empty line
        if (strlen(parsed_line->op) == 0) {
            continue;
        }

        program->lines[line_no] = parsed_line;
        check_label(program, line_no);
        line_no++;
    }
    program->total_lines = line_no;

    return program;
}

Line* parse_line(char* line) {
    Line* result = malloc(sizeof(Line));
    int line_ch_index = 0;

    // skip the indentation
    while (isspace(line[line_ch_index])) {
        line_ch_index++;
    }

    // extract the instruction
    char op[16];
    int op_ch_index = 0;
    while (!isspace(line[line_ch_index])) {
        op[op_ch_index++] = line[line_ch_index++];
    }
    op[op_ch_index] = '\0';
    result->op = str(op);

    // skip any whitespace and extract the args
    while (isspace(line[line_ch_index])) {
        line_ch_index++;
    }

    char args[256];
    int args_ch_index = 0;
    while (line[line_ch_index] != '\n' 
        && line[line_ch_index] != '\r'
        && line[line_ch_index] != '\0') {

        args[args_ch_index++] = line[line_ch_index++];
    }
    args[args_ch_index] = '\0';
    result->args = str(args);

    return result;
}

void check_label(Program* program, int line_number) {
    Line* line = program->lines[line_number];
    if (strcmp(line->op, "label") == 0) {
        Label* label = new(Label);
        label->label = line->args;
        label->line_number = line_number;
        program->labels[program->total_labels++] = label;
    }
}