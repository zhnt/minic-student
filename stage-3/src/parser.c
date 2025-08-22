#include "parser.h"
#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void parser_init(Parser* parser, Lexer* lexer) {
    parser->lexer = lexer;
    parser->current = lexer_next_token(lexer);
}

static int parser_consume(Parser* parser, TokenType type) {
    if (parser->current.type != type) {
        printf("Parser error: Expected %s, got %s at line %d\n", 
               token_type_string(type), token_type_string(parser->current.type), parser->current.line);
        return 0;
    }
    parser->current = lexer_next_token(parser->lexer);
    return 1;
}

static ASTNode* parse_expression(Parser* parser);
static ASTNode* parse_term(Parser* parser);
static ASTNode* parse_factor(Parser* parser);

static ASTNode* parse_primary(Parser* parser) {
    if (parser->current.type == TOKEN_NUMBER) {
        double value = parser->current.number;
        parser_consume(parser, TOKEN_NUMBER);
        return ast_number(value);
    } else if (parser->current.type == TOKEN_IDENTIFIER) {
        char name[32];
        strncpy(name, parser->current.identifier, 31);
        parser_consume(parser, TOKEN_IDENTIFIER);
        return ast_identifier(name);
    } else if (parser->current.type == TOKEN_LPAREN) {
        parser_consume(parser, TOKEN_LPAREN);
        ASTNode* expr = parse_expression(parser);
        parser_consume(parser, TOKEN_RPAREN);
        return expr;
    } else {
        printf("Parser error: Unexpected token %s at line %d\n", 
               token_type_string(parser->current.type), parser->current.line);
        return NULL;
    }
}

static ASTNode* parse_factor(Parser* parser) {
    // Handle unary operators
    if (parser->current.type == TOKEN_MINUS) {
        parser_consume(parser, TOKEN_MINUS);
        ASTNode* operand = parse_factor(parser);
        return ast_binary_op('*', ast_number(-1), operand);
    }
    
    if (parser->current.type == TOKEN_PLUS) {
        parser_consume(parser, TOKEN_PLUS);
        return parse_factor(parser); // Unary plus is a no-op
    }
    
    ASTNode* left = parse_primary(parser);
    
    while (parser->current.type == TOKEN_MULTIPLY || parser->current.type == TOKEN_DIVIDE) {
        char op = (parser->current.type == TOKEN_MULTIPLY) ? '*' : '/';
        parser_consume(parser, parser->current.type);
        ASTNode* right = parse_primary(parser);
        left = ast_binary_op(op, left, right);
    }
    
    return left;
}

static ASTNode* parse_term(Parser* parser) {
    ASTNode* left = parse_factor(parser);
    if (!left) return NULL;
    
    while (parser->current.type == TOKEN_PLUS || parser->current.type == TOKEN_MINUS) {
        char op = (parser->current.type == TOKEN_PLUS) ? '+' : '-';
        parser_consume(parser, parser->current.type);
        ASTNode* right = parse_factor(parser);
        if (!right) return NULL;
        left = ast_binary_op(op, left, right);
    }
    
    return left;
}

static ASTNode* parse_expression(Parser* parser) {
    // TODO: 学生需要添加赋值语句支持
    // 目前只支持表达式计算
    return parse_term(parser);
}

static ASTNode* parse_statement(Parser* parser) {
    // Always parse as an expression first
    return parse_expression(parser);
}

ASTNode* parser_program(Parser* parser) {
    // Handle multiple statements/expressions
    ASTNode** statements = NULL;
    int count = 0;
    int capacity = 0;
    
    while (parser->current.type != TOKEN_EOF) {
        // Skip semicolons
        while (parser->current.type == TOKEN_SEMICOLON) {
            parser_consume(parser, TOKEN_SEMICOLON);
        }
        
        if (parser->current.type == TOKEN_EOF) {
            break;
        }
        
        // Parse the next statement/expression
        ASTNode* stmt = parse_statement(parser);
        if (stmt) {
            // Resize array if needed
            if (count >= capacity) {
                capacity = capacity == 0 ? 4 : capacity * 2;
                statements = realloc(statements, sizeof(ASTNode*) * capacity);
                if (!statements) {
                    printf("Error: Memory allocation failed\n");
                    return NULL;
                }
            }
            statements[count++] = stmt;
        } else {
            // Skip to next statement on error
            while (parser->current.type != TOKEN_EOF && parser->current.type != TOKEN_SEMICOLON) {
                parser->current = lexer_next_token(parser->lexer);
            }
        }
        
        // Skip optional semicolons between statements
        while (parser->current.type == TOKEN_SEMICOLON) {
            parser_consume(parser, TOKEN_SEMICOLON);
        }
    }
    
    if (count == 0) {
        free(statements);
        return NULL; // Return NULL for empty program with errors
    } else if (count == 1) {
        ASTNode* result = statements[0];
        free(statements);
        return result; // Single statement
    } else {
        ASTNode* result = ast_sequence(statements, count);
        free(statements);
        return result;
    }
}