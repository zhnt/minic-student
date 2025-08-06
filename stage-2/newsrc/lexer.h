#ifndef MINIC_LEXER_H
#define MINIC_LEXER_H

typedef enum {
    TOKEN_NUMBER,
    TOKEN_IDENTIFIER,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_ASSIGN,
    TOKEN_SEMICOLON,
    TOKEN_EOF,
    TOKEN_ERROR
} TokenType;

typedef struct {
    TokenType type;
    double number;
    char identifier[32];
    int line;
    int column;
} Token;

typedef struct {
    const char* source;
    int pos;
    int line;
    int column;
} Lexer;

void lexer_init(Lexer* lex, const char* source);
Token lexer_next_token(Lexer* lex);
const char* token_type_string(TokenType type);

#endif