#include "vm.h"
#include "bytecode.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void vm_init(VM* vm) {
    vm->registers = calloc(256, sizeof(double));
    vm->register_count = 256;
    vm->globals = calloc(256, sizeof(double));
    vm->global_count = 256;
    vm->result = 0;
}

void vm_free(VM* vm) {
    free(vm->registers);
    free(vm->globals);
}

double vm_execute(VM* vm, Bytecode* bc) {
    for (int pc = 0; pc < bc->count; pc++) {
        Instruction* instr = &bc->code[pc];
        
        switch (instr->op) {
            case OP_LOADK:
                vm->registers[instr->a] = bc->constants[instr->b];
                break;
                
            case OP_ADD:
                vm->registers[instr->a] = vm->registers[instr->b] + vm->registers[instr->c];
                break;
                
            case OP_SUB:
                vm->registers[instr->a] = vm->registers[instr->b] - vm->registers[instr->c];
                break;
                
            case OP_SETGLOBAL:
                vm->globals[instr->a] = vm->registers[instr->b];
                break;
                
            case OP_GETGLOBAL:
                vm->registers[instr->a] = vm->globals[instr->b];
                break;
                
            case OP_RETURN:
                vm->result = vm->registers[instr->a];
                break;
                
            default:
                printf("VM Error: Unknown opcode %d\n", instr->op);
                return 0;
        }
    }
    return vm->result;
}