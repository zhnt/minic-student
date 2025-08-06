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

static ASTNode* parse_primary(Parser* parser) {
    if (parser->current.type == TOKEN_NUMBER) {
        double value = parser->current.number;
        parser_consume(parser, TOKEN_NUMBER);
        return ast_number(value);
    } else if (parser->current.type == TOKEN_IDENTIFIER) {
        char name[32];
        strncpy(name, parser->current.identifier, sizeof(name) - 1);
        parser_consume(parser, TOKEN_IDENTIFIER);
        return ast_identifier(name);
    } else {
        printf("Parser error: Unexpected token at line %d\n", parser->current.line);
        exit(1);
    }
}

static ASTNode* parse_expression(Parser* parser) {
    ASTNode* left = parse_primary(parser);
    
    while (1) {
        switch (parser->current.type) {
            case TOKEN_PLUS:
                parser_consume(parser, TOKEN_PLUS);
                left = ast_binary_op('+', left, parse_primary(parser));
                break;
            case TOKEN_MINUS:
                parser_consume(parser, TOKEN_MINUS);
                left = ast_binary_op('-', left, parse_primary(parser));
                break;
            case TOKEN_ERROR:
                printf("Parse error: Unrecognized operator or character\n");
                exit(1);
            default:
                return left;
        }
    }
    
    return left;
}

static ASTNode* parse_statement(Parser* parser) {
    // Check for assignment statement: identifier = expression;
    if (parser->current.type == TOKEN_IDENTIFIER) {
        char name[32];
        strncpy(name, parser->current.identifier, sizeof(name) - 1);
        parser_consume(parser, TOKEN_IDENTIFIER);
        
        if (parser->current.type == TOKEN_ASSIGN) {
            parser_consume(parser, TOKEN_ASSIGN);
            ASTNode* value = parse_expression(parser);
            parser_consume(parser, TOKEN_SEMICOLON);
            return ast_assignment(name, value);
        } else {
            printf("Error: Variables not supported (only numbers and '+' operations supported)\n");
            exit(1);
        }
    } else {
        // Expression statement: expression;
        ASTNode* expr = parse_expression(parser);
        parser_consume(parser, TOKEN_SEMICOLON);
        return expr;
    }
}

ASTNode* parse_program(Parser* parser) {
    // For MVP, we only support single statement
    return parse_statement(parser);
}