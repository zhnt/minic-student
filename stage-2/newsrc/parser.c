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

// 前向声明
static ASTNode* parse_expression(Parser* parser);
static ASTNode* parse_term(Parser* parser);
static ASTNode* parse_factor(Parser* parser);

// 表达式层：处理加减法
static ASTNode* parse_expression(Parser* parser) {
    ASTNode* left = parse_term(parser);
    
    while (parser->current.type == TOKEN_PLUS || parser->current.type == TOKEN_MINUS) {
        TokenType op = parser->current.type;
        parser_consume(parser, op);
        ASTNode* right = parse_term(parser);
        
        char op_char = (op == TOKEN_PLUS) ? '+' : '-';
        left = ast_binary_op(op_char, left, right);
    }
    
    return left;
}

// 项层：处理乘除法（学生需要在这里添加 * 和 / 支持）
static ASTNode* parse_term(Parser* parser) {
    ASTNode* left = parse_factor(parser);
    
    // TODO: 学生需要在这里添加乘法和除法支持
    // 当前只支持基本因子，需要添加以下代码：
    /*
    while (parser->current.type == TOKEN_STAR || parser->current.type == TOKEN_SLASH) {
        TokenType op = parser->current.type;
        parser_consume(parser, op);
        ASTNode* right = parse_factor(parser);
        
        char op_char = (op == TOKEN_STAR) ? '*' : '/';
        left = ast_binary_op(op_char, left, right);
    }
    */
    
    return left;
}

// 因子层：处理基本元素和括号（学生需要在这里添加括号支持）
static ASTNode* parse_factor(Parser* parser) {
    if (parser->current.type == TOKEN_NUMBER) {
        double value = parser->current.number;
        parser_consume(parser, TOKEN_NUMBER);
        return ast_number(value);
    } else if (parser->current.type == TOKEN_IDENTIFIER) {
        char name[32];
        strncpy(name, parser->current.identifier, sizeof(name) - 1);
        parser_consume(parser, TOKEN_IDENTIFIER);
        return ast_identifier(name);
    } else if (parser->current.type == TOKEN_LEFT_PAREN) {
        // 括号支持已完整实现
        parser_consume(parser, TOKEN_LEFT_PAREN);
        ASTNode* expr = parse_expression(parser);
        parser_consume(parser, TOKEN_RIGHT_PAREN);
        return expr;
    } else {
        printf("Parser error: Unexpected token '%s' at line %d\n", 
               parser->current.lexeme, parser->current.line);
        exit(1);
    }
}

static ASTNode* parse_statement(Parser* parser) {
    // 简化版本：只支持表达式计算
    // 学生可以基于此添加赋值语句支持
    ASTNode* expr = parse_expression(parser);
    if (parser->current.type == TOKEN_SEMICOLON) {
        parser_consume(parser, TOKEN_SEMICOLON);
    }
    return expr;
}

ASTNode* parse_program(Parser* parser) {
    return parse_statement(parser);
}