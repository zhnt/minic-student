#include "compiler.h"
#include "ast.h"
#include "bytecode.h"
#include <stdio.h>
#include <string.h>

void compiler_init(Compiler* comp, Bytecode* bc) {
    comp->bc = bc;
    comp->next_register = 0;
    comp->vars.count = 0; // 变量系统已禁用，学生需要实现
}

static int compile_expression(Compiler* comp, ASTNode* expr) {
    int reg = comp->next_register++;
    
    switch (expr->type) {
        case AST_NUMBER: {
            int const_idx = bytecode_add_constant(comp->bc, expr->data.number);
            bytecode_add_instruction(comp->bc, OP_LOADK, reg, const_idx, 0);
            return reg;
        }
        case AST_BINARY_OP: {
            int left_reg = compile_expression(comp, expr->data.binary_op.left);
            int right_reg = compile_expression(comp, expr->data.binary_op.right);
            switch (expr->data.binary_op.op) {
                case '+':
                    bytecode_add_instruction(comp->bc, OP_ADD, reg, left_reg, right_reg);
                    break;
                case '-':
                    bytecode_add_instruction(comp->bc, OP_SUB, reg, left_reg, right_reg);
                    break;
                case '*':
                    bytecode_add_instruction(comp->bc, OP_MUL, reg, left_reg, right_reg);
                    break;
                case '/':
                    bytecode_add_instruction(comp->bc, OP_DIV, reg, left_reg, right_reg);
                    break;
            }
            return reg;
        }
        case AST_IDENTIFIER: {
            // TODO: 学生需要实现变量查找功能
            printf("Error: Variable support not implemented yet\n");
            return -1;
        }
        default:
            printf("Compiler error: Unsupported AST node type\n");
            return -1;
    }
}

void compile_ast(Compiler* comp, ASTNode* ast) {
    if (!ast) return;
    
    switch (ast->type) {
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
            // TODO: 学生需要实现变量表达式
            printf("Error: Variable support not implemented yet\n");
            break;
        }
        case AST_ASSIGNMENT: {
            // TODO: 学生需要实现变量赋值功能
            printf("Error: Assignment support not implemented yet\n");
            return;
        }
        case AST_SEQUENCE: {
            // 只处理非赋值语句，保留多语句支持
            if (ast->data.sequence.count > 0) {
                // 跳过赋值语句，只处理表达式
                for (int i = 0; i < ast->data.sequence.count - 1; i++) {
                    ASTNode* stmt = ast->data.sequence.statements[i];
                    if (stmt->type != AST_ASSIGNMENT) {
                        compile_expression(comp, stmt);
                    }
                }
                
                // 处理最后一个语句作为结果
                ASTNode* last = ast->data.sequence.statements[ast->data.sequence.count - 1];
                if (last->type == AST_ASSIGNMENT) {
                    printf("Error: Assignment support not implemented yet\n");
                } else {
                    int result_reg = compile_expression(comp, last);
                    if (result_reg == -1) return; // Error in expression
                    bytecode_add_instruction(comp->bc, OP_RETURN, result_reg, 0, 0);
                }
            }
            break;
        }
        default:
            printf("Compiler error: Unsupported AST node type\n");
            break;
    }
}
