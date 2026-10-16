#ifndef OPERAND_H
#define OPERAND_H
#include <stdint.h>
typedef enum OperandType{
    REGISTER_VALUE,
    REGISTER_MEMORY,
    IMMEDIATE
}OperandType;
typedef struct Operand Operand;
Operand *init_register_type(char *register_name);
Operand *init_memory_register_type(char *register_name);
Operand *init_immediate_type(uint16_t memory_location);
char *get_name(Operand *operand);
OperandType get_type(Operand *operand);
void operand_destroy(Operand *operand);
#endif
