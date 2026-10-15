#ifndef DISASSEMBLER_H
#define DISASSEMBLER_H
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
typedef struct Definition {
    char *name;
}Definition;

typedef struct Operand {
    char *name;
} Operand;

typedef struct Operands {
    Operand *source;
    Operand *destination;
    int16_t displacement_value;
    int16_t immediate_value; //TODO: refine later the structure to accomodate imediate values
} Operands;

typedef struct Instruction{
    Definition *definition;
    Operands *operands;
}Instruction;

typedef struct InstructionList{
    Instruction **instructions;
    size_t size;
    size_t capacity;
}InstructionList;

InstructionList *disassemble(uint8_t instructions[], size_t length);
#endif // !
