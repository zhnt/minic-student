#include "minic/compiler.h"
#include "minic/ast.h"
#include "minic/bytecode.h"
#include <stdio.h>
#include <string.h>

void compiler_init(Compiler* comp, Bytecode* bc) {
    comp->bc = bc;
    comp->next_register = 0;
}

static int compile_expression(Compiler* comp, ASTNode* expr) {
    int reg = comp->next_register++;
    
    switch (expr->type) {
        case AST_NUMBER: {
            int const_idx = bytecode_add_constant(comp->bc, expr->data.number);
            bytecode_add_instruction(comp->bc, OP_LOADK, reg, const_idx, 0);
            return reg;
        }
        case AST_IDENTIFIER: {
            // For simplicity, use identifier string as constant index
            int name_idx = bytecode_add_constant(comp->bc, 0); // Placeholder
            bytecode_add_instruction(comp->bc, OP_GETGLOBAL, reg, name_idx, 0);
            return reg;
        }
        case AST_BINARY_OP: {
            int left_reg = compile_expression(comp, expr->data.binary_op.left);
            int right_reg = compile_expression(comp, expr->data.binary_op.right);
            bytecode_add_instruction(comp->bc, OP_ADD, reg, left_reg, right_reg);
            return reg;
        }
        default:
            printf("Compiler error: Unsupported AST node type\n");
            return -1;
    }
}

void compile_ast(Compiler* comp, ASTNode* ast) {
    switch (ast->type) {
        case AST_ASSIGNMENT: {
            int value_reg = compile_expression(comp, ast->data.assignment.value);
            // For simplicity, use a temporary constant index
            int name_idx = bytecode_add_constant(comp->bc, 0);
            bytecode_add_instruction(comp->bc, OP_SETGLOBAL, name_idx, value_reg, 0);
            bytecode_add_instruction(comp->bc, OP_RETURN, value_reg, 0, 0);
            break;
        }
        case AST_BINARY_OP: {
            // Expression statement - compile the expression and return
            int result_reg = compile_expression(comp, ast);
            bytecode_add_instruction(comp->bc, OP_RETURN, result_reg, 0, 0);
            break;
        }
        case AST_NUMBER: {
            // Simple number expression
            int result_reg = compile_expression(comp, ast);
            bytecode_add_instruction(comp->bc, OP_RETURN, result_reg, 0, 0);
            break;
        }
        case AST_IDENTIFIER: {
            // Identifier expression
            int result_reg = compile_expression(comp, ast);
            bytecode_add_instruction(comp->bc, OP_RETURN, result_reg, 0, 0);
            break;
        }
        default:
            printf("Compiler error: Unsupported AST node type\n");
            break;
    }
}