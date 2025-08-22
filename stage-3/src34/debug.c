#include "debug.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void debug_options_init(DebugOptions* opts) {
    opts->verbose_all = 0;
    opts->show_tokens = 0;
    opts->show_ast = 0;
    opts->show_bytecode = 0;
    opts->show_debug = 0;
    opts->show_execution = 0;
    opts->show_registers = 0;
}

void debug_parse_args(DebugOptions* opts, int argc, char* argv[]) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-v") == 0) {
            opts->verbose_all = 1;
            opts->show_tokens = 1;
            opts->show_ast = 1;
            opts->show_bytecode = 1;
            opts->show_execution = 1;
            opts->show_registers = 1;
        } else if (strcmp(argv[i], "-vt") == 0) {
            opts->show_tokens = 1;
        } else if (strcmp(argv[i], "-va") == 0) {
            opts->show_ast = 1;
        } else if (strcmp(argv[i], "-vb") == 0) {
            opts->show_bytecode = 1;
        } else if (strcmp(argv[i], "-vd") == 0) {
            opts->show_debug = 1;
        } else if (strcmp(argv[i], "-ve") == 0) {
            opts->show_execution = 1;
        } else if (strcmp(argv[i], "-vr") == 0) {
            opts->show_registers = 1;
        } else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            debug_print_help();
            exit(0);
        }
    }
}

void debug_print_help(void) {
    printf("minic - Mini Compiler for Learning\n");
    printf("\nUSAGE:\n");
    printf("  minic [OPTIONS] [FILE]\n");
    printf("\nOPTIONS:\n");
    printf("  -h, --help     Show this help\n");
    printf("  -v             Show all details (equivalent to -vt -va -vb -ve -vr)\n");
    printf("  -vt            Show tokens from lexical analysis\n");
    printf("  -va            Show abstract syntax tree (AST)\n");
    printf("  -vb            Show bytecode instructions\n");
    printf("  -ve            Show execution trace\n");
    printf("  -vr            Show register values during execution\n");
    printf("  -vd            Show debug information\n");
    printf("\nEXAMPLES:\n");
    printf("  minic -v\n");
    printf("  echo 'x = 5 + 3;' | minic -vt -va\n");
    printf("  minic -vb -ve\n");
}

// 格式化字符串输出（截断长字符串）
static void format_string(const char* str, char* buffer, int max_len) {
    int len = strlen(str);
    if (len <= max_len) {
        strcpy(buffer, str);
    } else {
        strncpy(buffer, str, max_len - 3);
        strcpy(buffer + max_len - 3, "...");
    }
}

void debug_tokens(const char* source) {
    printf("\n🔍 === LEXICAL ANALYSIS (Tokens) ===\n");
    Lexer lexer;
    lexer_init(&lexer, source);
    
    Token token;
    int count = 0;
    do {
        token = lexer_next_token(&lexer);
        printf("  %2d: %-12s", count++, token_type_string(token.type));
        
        if (token.type == TOKEN_NUMBER) {
            printf(" value=%.2f", token.number);
        } else if (token.type == TOKEN_IDENTIFIER) {
            char display[13];
            format_string(token.identifier, display, 10);
            printf(" name='%s'", display);
        }
        printf(" (line %d, col %d)\n", token.line, token.column);
        
    } while (token.type != TOKEN_EOF && token.type != TOKEN_ERROR);
}

void debug_ast(ASTNode* ast) {
    printf("\n🌳 === ABSTRACT SYNTAX TREE (AST) ===\n");
    ast_print(ast, 1);
    
    // 额外统计信息
    printf("\n📊 AST Statistics:\n");
    printf("  Type: %s\n", 
           ast->type == AST_NUMBER ? "Number" :
           ast->type == AST_IDENTIFIER ? "Identifier" :
           ast->type == AST_BINARY_OP ? "Binary Operation" :
           ast->type == AST_ASSIGNMENT ? "Assignment" : "Unknown");
}

void debug_bytecode(Bytecode* bc) {
    printf("\n⚙️  === BYTECODE INSTRUCTIONS ===\n");
    
    printf("📦 Constants Pool:\n");
    for (int i = 0; i < bc->constants_count; i++) {
        printf("  CONST[%d] = %.2f\n", i, bc->constants[i]);
    }
    
    printf("\n📝 Instructions:\n");
    printf("  %-5s %-12s %-8s %-8s %-8s\n", "PC", "OPCODE", "A", "B", "C");
    printf("  %-5s %-12s %-8s %-8s %-8s\n", "---", "------", "-", "-", "-");
    
    for (int i = 0; i < bc->count; i++) {
        Instruction* instr = &bc->code[i];
        printf("  %-5d %-12s %-8d %-8d %-8d", 
               i, 
               instr->op == OP_LOADK ? "LOADK" :
               instr->op == OP_ADD ? "ADD" :
               instr->op == OP_SUB ? "SUB" :
               instr->op == OP_MUL ? "MUL" :
               instr->op == OP_DIV ? "DIV" :
               instr->op == OP_SETVAR ? "SETVAR" :
               instr->op == OP_GETVAR ? "GETVAR" :
               instr->op == OP_RETURN ? "RETURN" : "UNKNOWN",
               instr->a, instr->b, instr->c);
        
        if (instr->op == OP_LOADK && instr->b < bc->constants_count) {
            printf("  # K[%d]=%.2f", instr->b, bc->constants[instr->b]);
        }
        printf("\n");
    }
}

void debug_execution(VM* vm, Bytecode* bc) {
    printf("\n🚀 === EXECUTION TRACE ===\n");
    
    // 初始化执行跟踪
    for (int pc = 0; pc < bc->count; pc++) {
        Instruction* instr = &bc->code[pc];
        
        printf("\n📍 PC=%d: ", pc);
        switch (instr->op) {
            case OP_LOADK:
                printf("LOADK R[%d] = K[%d] (%.2f)", 
                       instr->a, instr->b, bc->constants[instr->b]);
                vm->registers[instr->a] = bc->constants[instr->b];
                break;
                
            case OP_ADD:
                printf("ADD R[%d] = R[%d] (%.2f) + R[%d] (%.2f)", 
                       instr->a, instr->b, vm->registers[instr->b], 
                       instr->c, vm->registers[instr->c]);
                vm->registers[instr->a] = vm->registers[instr->b] + vm->registers[instr->c];
                break;
                
            case OP_SUB:
                printf("SUB R[%d] = R[%d] (%.2f) - R[%d] (%.2f)", 
                       instr->a, instr->b, vm->registers[instr->b], 
                       instr->c, vm->registers[instr->c]);
                vm->registers[instr->a] = vm->registers[instr->b] - vm->registers[instr->c];
                break;
                
            case OP_MUL:
                printf("MUL R[%d] = R[%d] (%.2f) * R[%d] (%.2f)", 
                       instr->a, instr->b, vm->registers[instr->b], 
                       instr->c, vm->registers[instr->c]);
                vm->registers[instr->a] = vm->registers[instr->b] * vm->registers[instr->c];
                break;
                
            case OP_DIV:
                printf("DIV R[%d] = R[%d] (%.2f) / R[%d] (%.2f)", 
                       instr->a, instr->b, vm->registers[instr->b], 
                       instr->c, vm->registers[instr->c]);
                vm->registers[instr->a] = vm->registers[instr->b] / vm->registers[instr->c];
                break;
                
            case OP_SETVAR:
                printf("SETVAR V[%d] = R[%d] (%.2f)", 
                       instr->a, instr->b, vm->registers[instr->b]);
                vm->variables[instr->a] = vm->registers[instr->b];
                break;
                
            case OP_GETVAR:
                printf("GETVAR R[%d] = V[%d] (%.2f)", 
                       instr->a, instr->b, vm->variables[instr->b]);
                vm->registers[instr->a] = vm->variables[instr->b];
                break;
                
            case OP_RETURN:
                printf("RETURN R[%d] (%.2f)", instr->a, vm->registers[instr->a]);
                vm->result = vm->registers[instr->a];
                break;
        }
        
        // 显示寄存器状态
        printf("\n   Registers: ");
        for (int r = 0; r <= 3; r++) {
            printf("R[%d]=%.2f ", r, vm->registers[r]);
        }
        printf("\n");
    }
    
    printf("\n✅ Execution complete! Final result: %.2f\n", vm->result);
}
