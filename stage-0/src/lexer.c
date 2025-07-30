#include "minic/lexer.h"
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
        return (Token){TOKEN_NUMBER, value, "", lex->line, lex->column};
    }
    
    if (isalpha(c)) {
        Token token = {TOKEN_IDENTIFIER, 0, "", lex->line, lex->column};
        int i = 0;
        while (isalnum(lexer_peek(lex)) && i < 31) {
            token.identifier[i++] = lexer_advance(lex);
        }
        token.identifier[i] = '\0';
        return token;
    }
    
    lexer_advance(lex);
    switch (c) {
        case '+': return (Token){TOKEN_PLUS, 0, "", lex->line, lex->column};
        case '=': return (Token){TOKEN_ASSIGN, 0, "", lex->line, lex->column};
        case ';': return (Token){TOKEN_SEMICOLON, 0, "", lex->line, lex->column};
        default: return (Token){TOKEN_ERROR, 0, "", lex->line, lex->column};
    }
}

const char* token_type_string(TokenType type) {
    switch (type) {
        case TOKEN_NUMBER: return "NUMBER";
        case TOKEN_IDENTIFIER: return "IDENTIFIER";
        case TOKEN_PLUS: return "PLUS";
        case TOKEN_ASSIGN: return "ASSIGN";
        case TOKEN_SEMICOLON: return "SEMICOLON";
        case TOKEN_EOF: return "EOF";
        case TOKEN_ERROR: return "ERROR";
    }
}