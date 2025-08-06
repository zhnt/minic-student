#ifndef MINIC_COMPILER_H
#define MINIC_COMPILER_H

#include "ast.h"
#include "bytecode.h"

typedef struct {
    Bytecode* bc;
    int next_register;
} Compiler;

void compiler_init(Compiler* comp, Bytecode* bc);
void compile_ast(Compiler* comp, ASTNode* ast);

#endif