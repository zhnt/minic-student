#include "lexer.h"
#include "parser.h"
#include "ast.h"
#include "compiler.h"
#include "vm.h"
#include "debug.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

static void repl_mode(DebugOptions* opts __attribute__((unused))) {
    printf("minic - Mini Compiler for Learning (REPL)\n");
    printf("Type 'exit' or 'quit' to exit, 'help' for help\n\n");
    
    char input[1024];
    
    while (1) {
        printf("minic> ");
        fflush(stdout);
        
        if (!fgets(input, sizeof(input), stdin)) {
            break;
        }
        
        // Remove newline
        input[strcspn(input, "\n")] = 0;
        
        // Handle special commands
        if (strcmp(input, "exit") == 0 || strcmp(input, "quit") == 0) {
            printf("Goodbye!\n");
            break;
        }
        
        if (strcmp(input, "help") == 0) {
            printf("Available commands:\n");
            printf("  exit, quit - Exit the REPL\n");
            printf("  help       - Show this help\n");
            printf("Enter expressions like: x = 5 + 3;\n\n");
            continue;
        }
        
        if (strlen(input) == 0) {
            continue;
        }
        
        // Ensure semicolon for statements
        char full_input[1024];
        int has_semicolon = strchr(input, ';') != NULL;
        int is_assignment = strchr(input, '=') != NULL;
        
        if (!has_semicolon) {
            snprintf(full_input, sizeof(full_input), "%s;", input);
        } else {
            strncpy(full_input, input, sizeof(full_input));
        }
        
        // Process the expression
        Lexer lexer;
        lexer_init(&lexer, full_input);
        
        Parser parser;
        parser_init(&parser, &lexer);
        
        ASTNode* ast = NULL;
        
        // 直接执行，不使用fork
        ast = parser_program(&parser);
        if (!ast) {
            continue; // Error already printed by parser
        }
        
        Bytecode bc;
        bytecode_init(&bc);
        
        static Compiler persistent_comp;
        static int compiler_initialized = 0;
        if (!compiler_initialized) {
            compiler_init(&persistent_comp, &bc);
            compiler_initialized = 1;
        } else {
            persistent_comp.bc = &bc;
            persistent_comp.next_register = 0;
        }
        compile_ast(&persistent_comp, ast);
        
        // 使用持久的VM实例
        static VM persistent_vm;
        static int vm_initialized = 0;
        if (!vm_initialized) {
            vm_init(&persistent_vm);
            vm_initialized = 1;
        }
        
        double result = vm_execute(&persistent_vm, &bc);
        
        if (!is_assignment) {
            printf("%.2f\n", result);
        }
        
        ast_free(ast);
        bytecode_free(&bc);
    }
}

int main(int argc, char* argv[]) {
    DebugOptions opts;
    debug_options_init(&opts);
    debug_parse_args(&opts, argc, argv);
    
    if (argc == 2 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)) {
        debug_print_help();
        return 0;
    }
    
    // Find the filename argument (first non-option argument)
    char* filename = NULL;
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] != '-') {
            filename = argv[i];
            break;
        }
    }
    
    // File processing mode
    if (filename) {
        
        FILE* file = fopen(filename, "r");
        if (!file) {
            printf("Error: Cannot open file '%s'\n", filename);
            return 1;
        }
        
        char input[1024] = {0};
        size_t bytesRead = fread(input, 1, sizeof(input) - 1, file);
        if (bytesRead == 0) {
            printf("Error: Cannot read from file '%s'\n", filename);
            fclose(file);
            return 1;
        }
        fclose(file);
        
        // Process file content
        Lexer lexer;
        lexer_init(&lexer, input);
        
        Parser parser;
        parser_init(&parser, &lexer);
        
        // Show tokens if requested
        if (opts.show_tokens || opts.verbose_all) {
            debug_tokens(input);
        }
        
        ASTNode* ast = parser_program(&parser);
        
        if (!ast) {
            printf("❌ Parse error in file '%s'\n", filename);
            return 1;
        }
        
        // Show AST if requested
        if (opts.show_ast || opts.verbose_all) {
            debug_ast(ast);
        }
        
        Bytecode bc;
        bytecode_init(&bc);
        
        static Compiler persistent_comp;
        static int compiler_initialized = 0;
        if (!compiler_initialized) {
            compiler_init(&persistent_comp, &bc);
            compiler_initialized = 1;
        } else {
            persistent_comp.bc = &bc;
            persistent_comp.next_register = 0;
        }
        compile_ast(&persistent_comp, ast);
        
        // Show bytecode if requested
        if (opts.show_bytecode || opts.verbose_all) {
            debug_bytecode(&bc);
        }
        
        VM vm;
        vm_init(&vm);
        
        if (opts.show_execution || opts.verbose_all) {
            debug_execution(&vm, &bc);
        } else {
            double result = vm_execute(&vm, &bc);
            printf("🎯 Result: %.2f\n", result);
        }
        
        ast_free(ast);
        bytecode_free(&bc);
        vm_free(&vm);
        return 0;
    }
    
    // REPL mode - no filename provided
    repl_mode(&opts);
    return 0;
}