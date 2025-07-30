#include "minic/ast.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

ASTNode* ast_number(double value) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = AST_NUMBER;
    node->data.number = value;
    return node;
}

ASTNode* ast_identifier(const char* name) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = AST_IDENTIFIER;
    strncpy(node->data.identifier, name, sizeof(node->data.identifier) - 1);
    return node;
}

ASTNode* ast_binary_op(char op, ASTNode* left, ASTNode* right) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = AST_BINARY_OP;
    node->data.binary_op.op = op;
    node->data.binary_op.left = left;
    node->data.binary_op.right = right;
    return node;
}

ASTNode* ast_assignment(const char* name, ASTNode* value) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = AST_ASSIGNMENT;
    strncpy(node->data.assignment.name, name, sizeof(node->data.assignment.name) - 1);
    node->data.assignment.value = value;
    return node;
}

void ast_free(ASTNode* node) {
    if (!node) return;
    
    switch (node->type) {
        case AST_BINARY_OP:
            ast_free(node->data.binary_op.left);
            ast_free(node->data.binary_op.right);
            break;
        case AST_ASSIGNMENT:
            ast_free(node->data.assignment.value);
            break;
        default:
            break;
    }
    
    free(node);
}

void ast_print(ASTNode* node, int indent) {
    if (!node) return;
    
    for (int i = 0; i < indent; i++) printf("  ");
    
    switch (node->type) {
        case AST_NUMBER:
            printf("NUMBER: %.2f\n", node->data.number);
            break;
        case AST_IDENTIFIER:
            printf("IDENTIFIER: %s\n", node->data.identifier);
            break;
        case AST_BINARY_OP:
            printf("BINARY_OP: %c\n", node->data.binary_op.op);
            ast_print(node->data.binary_op.left, indent + 1);
            ast_print(node->data.binary_op.right, indent + 1);
            break;
        case AST_ASSIGNMENT:
            printf("ASSIGNMENT: %s\n", node->data.assignment.name);
            ast_print(node->data.assignment.value, indent + 1);
            break;
        default:
            printf("UNKNOWN\n");
    }
}