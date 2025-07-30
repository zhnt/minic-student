#ifndef MINIC_DEBUG_H
#define MINIC_DEBUG_H

#include "minic/lexer.h"
#include "minic/ast.h"
#include "minic/bytecode.h"
#include "minic/vm.h"

typedef struct {
    int verbose_all;      // -v
    int show_tokens;      // -vt
    int show_ast;         // -va
    int show_bytecode;    // -vb
    int show_debug;       // -vd
    int show_execution;   // -ve
    int show_registers;   // -vr
} DebugOptions;

void debug_options_init(DebugOptions* opts);
void debug_parse_args(DebugOptions* opts, int argc, char* argv[]);
void debug_print_help(void);

// 调试打印函数
void debug_tokens(const char* source);
void debug_ast(ASTNode* ast);
void debug_bytecode(Bytecode* bc);
void debug_execution(VM* vm, Bytecode* bc);

#endif