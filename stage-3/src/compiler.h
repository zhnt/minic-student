#ifndef MINIC_COMPILER_H
#define MINIC_COMPILER_H

#include "ast.h"
#include "bytecode.h"

#define MAX_VARIABLES 100

typedef struct {
    char names[MAX_VARIABLES][32];
    int count;
} SymbolTable;

typedef struct {
    Bytecode* bc;
    int next_register;
    SymbolTable vars;
} Compiler;

void compiler_init(Compiler* comp, Bytecode* bc);
void compile_ast(Compiler* comp, ASTNode* ast);

#endif