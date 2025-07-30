#ifndef MINIC_BYTECODE_H
#define MINIC_BYTECODE_H

typedef enum {
    OP_LOADK,      // 加载常量到寄存器: R[A] = K[B]
    OP_ADD,        // 加法: R[A] = R[B] + R[C]
    OP_SETGLOBAL,  // 设置全局变量: G[A] = R[B]
    OP_GETGLOBAL,  // 获取全局变量: R[A] = G[B]
    OP_RETURN      // 返回: return R[A]
} Opcode;

typedef struct {
    Opcode op;
    int a;
    int b;
    int c;
} Instruction;

typedef struct {
    Instruction* code;
    int count;
    int capacity;
    double* constants;
    int constants_count;
    int constants_capacity;
} Bytecode;

void bytecode_init(Bytecode* bc);
int bytecode_add_constant(Bytecode* bc, double value);
void bytecode_add_instruction(Bytecode* bc, Opcode op, int a, int b, int c);
void bytecode_print(Bytecode* bc);
void bytecode_free(Bytecode* bc);

#endif