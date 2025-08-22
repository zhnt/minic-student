#include "lexer.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

void lexer_init(Lexer* lex, const char* source) {
    lex->source = source;
    lex->pos = 0;
    lex->line = 1;
    lex->column = 1;
}

static char lexer_peek(Lexer* lex) {
    return lex->source[lex->pos];
}

static char lexer_advance(Lexer* lex) {
    char c = lex->source[lex->pos++];
    if (c == '\n') {
        lex->line++;
        lex->column = 1;
    } else {
        lex->column++;
    }
    return c;
}

static void lexer_skip_whitespace(Lexer* lex) {
    while (isspace(lexer_peek(lex))) {
        lexer_advance(lex);
    }
}

Token lexer_next_token(Lexer* lex) {
    lexer_skip_whitespace(lex);
    
    char c = lexer_peek(lex);
    if (c == '\0') {
        return (Token){TOKEN_EOF, 0, "", lex->line, lex->column};
    }
    
    if (isdigit(c)) {
        double value = 0;
        while (isdigit(lexer_peek(lex))) {
            value = value * 10 + (lexer_advance(lex) - '0');
        }
        if (lexer_peek(lex) == '.') {
            lexer_advance(lex);
            double fraction = 0.1;
            while (isdigit(lexer_peek(lex))) {
                value += (lexer_advance(lex) - '0') * fraction;
                fraction *= 0.1;
            }
        }
        // Check if this is followed by a letter (invalid identifier)
        if (isalpha(lexer_peek(lex))) {
            printf("Lexer error: Invalid identifier starting with number at line %d\n", lex->line);
            return (Token){TOKEN_ERROR, 0, "", lex->line, lex->column};
        }
        return (Token){TOKEN_NUMBER, value, "", lex->line, lex->column};
    }
    
    if (isalpha(c)) {
        int i = 0;
        char identifier[32];
        while (isalnum(lexer_peek(lex)) && i < 31) {
            identifier[i++] = lexer_advance(lex);
        }
        identifier[i] = '\0';
        Token token = {TOKEN_IDENTIFIER, 0, "", lex->line, lex->column};
        strncpy(token.identifier, identifier, 31);
        return token;
    }
    
    lexer_advance(lex);
    switch (c) {
        case '+': return (Token){TOKEN_PLUS, 0, "", lex->line, lex->column};
        case '-': return (Token){TOKEN_MINUS, 0, "", lex->line, lex->column};
        case '*': return (Token){TOKEN_MULTIPLY, 0, "", lex->line, lex->column};
        case '/': return (Token){TOKEN_DIVIDE, 0, "", lex->line, lex->column};
        case '=': return (Token){TOKEN_ASSIGN, 0, "", lex->line, lex->column};
        case ';': return (Token){TOKEN_SEMICOLON, 0, "", lex->line, lex->column};
        case '(': return (Token){TOKEN_LPAREN, 0, "", lex->line, lex->column};
        case ')': return (Token){TOKEN_RPAREN, 0, "", lex->line, lex->column};
        default: return (Token){TOKEN_ERROR, 0, "", lex->line, lex->column};
    }
}

const char* token_type_string(TokenType type) {
    switch (type) {
        case TOKEN_NUMBER: return "NUMBER";
        case TOKEN_IDENTIFIER: return "IDENTIFIER";
        case TOKEN_PLUS: return "PLUS";
        case TOKEN_MINUS: return "MINUS";
        case TOKEN_MULTIPLY: return "MULTIPLY";
        case TOKEN_DIVIDE: return "DIVIDE";
        case TOKEN_ASSIGN: return "ASSIGN";
        case TOKEN_SEMICOLON: return "SEMICOLON";
        case TOKEN_LPAREN: return "LPAREN";
        case TOKEN_RPAREN: return "RPAREN";
        case TOKEN_EOF: return "EOF";
        case TOKEN_ERROR: return "ERROR";
    }
}