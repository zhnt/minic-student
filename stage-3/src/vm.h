#ifndef MINIC_VM_H
#define MINIC_VM_H

#include "bytecode.h"

typedef struct {
    double* registers;
    int register_count;
    double* variables;
    int variable_count;
    double result;
} VM;

void vm_init(VM* vm);
void vm_free(VM* vm);
double vm_execute(VM* vm, Bytecode* bc);

#endif
