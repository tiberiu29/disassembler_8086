#include "disassembler.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

//Structure 
// [op-code][d][w][MOD][REG][R/M]
// ---6------1--1---2----3----3-- = 2 BYTES core
//
// Additionally we can also have DISPLACEMENT + ADDITIONAL BYTES
// [Displacement-LOW][DISPLACEMENT-HIGH][IMMEDIATE-LOW][IMMEDIATE-HIGH] = 4 BYTES optional
// ----------8----------------8----------------8------------8----------
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


// There are 8 modes
// 1. Immediate Addresing Mode. EX: MOV CL, 15H
// 2. Register Addressing Mode. EX: MOV CL, DL
// 3. Direct Addresing Mode. EX: MOV CL, [1000H]
// 4. Implied Addresing Mode - still not sure what it is
// 5. Register Indirect Addresing. EX: MOV CL, [BX]
// 6. Register Relative Addresing. EX: MOV CL, [BX + 4] where 4 is DISPLACEMENT
// 7. Base Indexed Addresing. EX: MOV CL, [BX + SI]
// 8. Base Relative + Indexed Addresing. EX: MOV CL, [BX + SI + 4] where 4 is displacement
char *calculate_rm_operator() {
    // Aparently displacement can be up to 16 bits 
    // This mean that my instruction can be 4 bytes so original assumption of 2 bytes is wrong.

    return "";
}

