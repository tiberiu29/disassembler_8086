#include "operand.h"
#include <stdlib.h>

typedef struct Operand{
    OperandType type;
    union {
        char *name;
        uint16_t immediate_value;
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

Operand *init_immediate_type(uint16_t memory_location){
    //TODO implement
    return NULL;
}

char *get_name(Operand *operand) {
    return operand->name;
}

OperandType get_type(Operand *operand){
    return operand->type;
}
