#include "compiler.h"
#include "ast.h"
#include "bytecode.h"
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
            // Find variable by name
            int var_idx = -1;
            for (int i = 0; i < comp->vars.count; i++) {
                if (strcmp(comp->vars.names[i], expr->data.identifier) == 0) {
                    var_idx = i;
                    break;
                }
            }
            
            if (var_idx == -1) {
                printf("Error: Variable '%s' not defined\n", expr->data.identifier);
                return -1;
            }
            
            bytecode_add_instruction(comp->bc, OP_GETVAR, reg, var_idx, 0);
            return reg;
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
            // Identifier expression
            int result_reg = compile_expression(comp, ast);
            bytecode_add_instruction(comp->bc, OP_RETURN, result_reg, 0, 0);
            break;
        }
        case AST_ASSIGNMENT: {
            int value_reg = compile_expression(comp, ast->data.assignment.value);
            
            // Find or create variable
            int var_idx = -1;
            for (int i = 0; i < comp->vars.count; i++) {
                if (strcmp(comp->vars.names[i], ast->data.assignment.name) == 0) {
                    var_idx = i;
                    break;
                }
            }
            
            if (var_idx == -1) {
                if (comp->vars.count >= MAX_VARIABLES) {
                    printf("Error: Too many variables\n");
                    return;
                }
                var_idx = comp->vars.count;
                strncpy(comp->vars.names[var_idx], ast->data.assignment.name, 31);
                comp->vars.count++;
            }
            
            bytecode_add_instruction(comp->bc, OP_SETVAR, var_idx, value_reg, 0);
            bytecode_add_instruction(comp->bc, OP_RETURN, value_reg, 0, 0);
            break;
        }
        case AST_SEQUENCE: {
            // Handle multiple statements - compile each one
            // For now, we'll compile just the last expression as the result
            if (ast->data.sequence.count > 0) {
                // Compile all statements except the last
                for (int i = 0; i < ast->data.sequence.count - 1; i++) {
                    ASTNode* stmt = ast->data.sequence.statements[i];
                    if (stmt->type == AST_ASSIGNMENT) {
                        int value_reg = compile_expression(comp, stmt->data.assignment.value);
                        if (value_reg == -1) return; // Error in expression
                        
                        // Find or create variable properly
                        int var_idx = -1;
                        for (int j = 0; j < comp->vars.count; j++) {
                            if (strcmp(comp->vars.names[j], stmt->data.assignment.name) == 0) {
                                var_idx = j;
                                break;
                            }
                        }
                        
                        if (var_idx == -1) {
                            if (comp->vars.count >= MAX_VARIABLES) {
                                printf("Error: Too many variables\n");
                                return;
                            }
                            var_idx = comp->vars.count;
                            strncpy(comp->vars.names[var_idx], stmt->data.assignment.name, 31);
                            comp->vars.count++;
                        }
                        
                        bytecode_add_instruction(comp->bc, OP_SETVAR, var_idx, value_reg, 0);
                    } else {
                        // For non-assignment statements, just compile them
                        compile_expression(comp, stmt);
                    }
                }
                
                // Compile the last statement as the result
                ASTNode* last = ast->data.sequence.statements[ast->data.sequence.count - 1];
                if (last->type == AST_ASSIGNMENT) {
                    int value_reg = compile_expression(comp, last->data.assignment.value);
                    if (value_reg == -1) return; // Error in expression
                    
                    // Find or create variable properly
                    int var_idx = -1;
                    for (int j = 0; j < comp->vars.count; j++) {
                        if (strcmp(comp->vars.names[j], last->data.assignment.name) == 0) {
                            var_idx = j;
                            break;
                        }
                    }
                    
                    if (var_idx == -1) {
                        if (comp->vars.count >= MAX_VARIABLES) {
                            printf("Error: Too many variables\n");
                            return;
                        }
                        var_idx = comp->vars.count;
                        strncpy(comp->vars.names[var_idx], last->data.assignment.name, 31);
                        comp->vars.count++;
                    }
                    
                    bytecode_add_instruction(comp->bc, OP_SETVAR, var_idx, value_reg, 0);
                    bytecode_add_instruction(comp->bc, OP_RETURN, value_reg, 0, 0);
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
