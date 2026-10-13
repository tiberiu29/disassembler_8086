#ifndef DISASSEMBLER_H
#define DISASSEMBLER_H
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef struct Definition {
    char *name;
    int8_t direction_bit_position;
    int8_t width_bit_position;
    bool has_r_m;
}Definition;

typedef struct Register {
    char *name;
} Register;

typedef struct Operands {
    Register from;
    Register to;
    size_t displacement_value;
    size_t immediate_value; //TODO: refine later the structure to accomodate imediate values
} Operands;

typedef struct Instruction{
    Definition *definition;
    Operands *options;
}Instruction;

Instruction **disassemble(uint8_t instructions[], size_t length);
#endif // !
