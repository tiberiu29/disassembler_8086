#include "disassembler.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

char *disassemble(uint16_t instruction) {
    uint8_t op_code = instruction >> 10 & 0b111111;
    bool direction_flag = instruction >> 9 & 0b1;
    bool width_flag = instruction >> 8 & 0b1;
    uint8_t source;
    uint8_t destination;

    uint8_t mod_flag = instruction >> 6 &0b11;

    uint8_t reg_operand = instruction >> 3 & 0b111; 
    uint8_t rm_operand = instruction & 0b111; 

    if(direction_flag) {
       source = rm_operand;
       destination = reg_operand;
    } else {
       source = reg_operand;
       destination = rm_operand;
    }

    printf("Op_Code: %d \n", op_code);
    printf("Direction_Flag: %s \n", direction_flag ? "true" : "false");
    printf("Width_Flag: %s \n", width_flag ? "true" : "false");
    printf("Source: %d \n", source);
    printf("Destination: %d \n", destination);
    printf("Mod_Flag: %d \n", mod_flag);

    if(op_code == 34) {
        return "mov";
    }

    return "NO-OP";
}

