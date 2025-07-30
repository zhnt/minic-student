#ifndef MINIC_AST_H
#define MINIC_AST_H

typedef enum {
    AST_NUMBER,
    AST_IDENTIFIER,
    AST_BINARY_OP,
    AST_ASSIGNMENT,
    AST_PROGRAM
} ASTNodeType;

typedef struct ASTNode {
    ASTNodeType type;
    union {
        double number;
        char identifier[32];
        struct {
            struct ASTNode* left;
            struct ASTNode* right;
            char op;
        } binary_op;
        struct {
            char name[32];
            struct ASTNode* value;
        } assignment;
    } data;
} ASTNode;

ASTNode* ast_number(double value);
ASTNode* ast_identifier(const char* name);
ASTNode* ast_binary_op(char op, ASTNode* left, ASTNode* right);
ASTNode* ast_assignment(const char* name, ASTNode* value);
void ast_free(ASTNode* node);
void ast_print(ASTNode* node, int indent);

#endif