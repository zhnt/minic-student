#ifndef MINIC_PARSER_H
#define MINIC_PARSER_H

#include "minic/lexer.h"
#include "minic/ast.h"

typedef struct {
    Lexer* lexer;
    Token current;
} Parser;

void parser_init(Parser* parser, Lexer* lexer);
ASTNode* parse_program(Parser* parser);

#endif