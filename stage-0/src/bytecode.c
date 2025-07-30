#include "minic/bytecode.h"
#include <stdlib.h>
#include <stdio.h>

void bytecode_init(Bytecode* bc) {
    bc->code = NULL;
    bc->count = 0;
    bc->capacity = 0;
    bc->constants = NULL;
    bc->constants_count = 0;
    bc->constants_capacity = 0;
}

int bytecode_add_constant(Bytecode* bc, double value) {
    if (bc->constants_count >= bc->constants_capacity) {
        bc->constants_capacity = bc->constants_capacity == 0 ? 8 : bc->constants_capacity * 2;
        bc->constants = realloc(bc->constants, bc->constants_capacity * sizeof(double));
    }
    bc->constants[bc->constants_count] = value;
    return bc->constants_count++;
}

void bytecode_add_instruction(Bytecode* bc, Opcode op, int a, int b, int c) {
    if (bc->count >= bc->capacity) {
        bc->capacity = bc->capacity == 0 ? 16 : bc->capacity * 2;
        bc->code = realloc(bc->code, bc->capacity * sizeof(Instruction));
    }
    bc->code[bc->count].op = op;
    bc->code[bc->count].a = a;
    bc->code[bc->count].b = b;
    bc->code[bc->count].c = c;
    bc->count++;
}

const char* opcode_name(Opcode op) {
    switch(op) {
        case OP_LOADK: return "LOADK";
        case OP_ADD: return "ADD";
        case OP_SETGLOBAL: return "SETGLOBAL";
        case OP_GETGLOBAL: return "GETGLOBAL";
        case OP_RETURN: return "RETURN";
        default: return "UNKNOWN";
    }
}

void bytecode_print(Bytecode* bc) {
    printf("=== Bytecode ===\n");
    for (int i = 0; i < bc->constants_count; i++) {
        printf("CONSTANT[%d] = %.2f\n", i, bc->constants[i]);
    }
    printf("\n");
    for (int i = 0; i < bc->count; i++) {
        Instruction* instr = &bc->code[i];
        printf("%03d: %-12s %d %d %d\n", i, opcode_name(instr->op), instr->a, instr->b, instr->c);
    }
}

void bytecode_free(Bytecode* bc) {
    free(bc->code);
    free(bc->constants);
}