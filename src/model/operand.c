#include "operand.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct Operand{
    OperandType type;
    union {
        char *name;
        int16_t immediate_value;
    };
} Operand;

Operand *init_empty() {
    Operand *empty_op = malloc(sizeof(Operand));
    return empty_op;
}
Operand *init_register_type(char *register_name){
    Operand *op = init_empty();
    op->type=REGISTER_VALUE;
    op->name=register_name;
    return op;
}

Operand *init_memory_register_type(char *register_name){
    Operand *op = init_empty();
    op->type=REGISTER_MEMORY;
    op->name=register_name;
    return op;

}

Operand *init_immediate_type(int16_t immediate_value){
    Operand *op = init_empty();
    op->type = IMMEDIATE;
    op->immediate_value = immediate_value; 
    return op;
}

char *get_name(Operand *operand) {
    if(operand->type == IMMEDIATE){
        printf("This is an immediate type");
        return NULL;
    }
    return operand->name;
}

int16_t get_immediate_value(Operand *operand) {
    if(operand->type != IMMEDIATE){
        printf("This is a register type");
        return 0;
    }
    return operand->immediate_value;
}

OperandType get_type(Operand *operand){
    return operand->type;
}

void operand_destroy(Operand *operand){
    if(operand == NULL) {
        return;
    }
    free(operand);
}
