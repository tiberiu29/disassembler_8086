#include "disassembler.h"
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define BIT_DISABLED UINT8_MAX

uint8_t create_mask(uint8_t end, uint8_t start){
    if(end < 1 || end > 8) {
        printf("mask for 1 byte cannot be higher than 8 bits or lower than 1 bit");
        exit(1);
    }
    uint8_t width = end - start;
    return ((1u << width) - 1u) << start;
}

uint8_t mod_value(uint8_t byte) {
    return (byte & create_mask(8, 6)) >> 6;
}

uint8_t reg_value(uint8_t byte) {
    return (byte & create_mask(6, 3)) >> 3;
}

uint8_t r_m_value(uint8_t byte) {
    return byte & create_mask(3, 0);
}

/*
 * REG | w=0 (8-bit) | w=1 (16-bit)
 * ----+-------------+-------------
 * 000 | AL          | AX
 * 001 | CL          | CX
 * 010 | DL          | DX
 * 011 | BL          | BX
 * 100 | AH          | SP
 * 101 | CH          | BP
 * 110 | DH          | SI
 * 111 | BH          | DI
 */
Operand *determine_operand(uint8_t reg, uint8_t width) {
    Operand *operand = malloc(sizeof(Operand));
    switch (reg) {
      case 0b00000000:
        if(width == 0) {
            operand->name = "AL";
        } else{
            operand->name = "AX";
        }
        break;
      case 0b00000001:
        if(width == 0) {
            operand->name = "CL";
        } else{
            operand->name = "CX";
        }
        break;
      case 0b00000010:
        if(width == 0) {
            operand->name = "DL";
        } else{
            operand->name = "DX";
        }
        break;
      case 0b00000011:
        if(width == 0) {
            operand->name = "BL";
        } else {
            operand->name = "BX";
        }
        break;
      case 0b00000100:
        if(width == 0) {
            operand->name = "AH";
        } else{
            operand->name = "SP";
        }
        break;
      case 0b00000101:
        if(width == 0) {
            operand->name = "CH";
        } else{
            operand->name = "BP";
        }
        break;
      case 0b00000110:
        if(width == 0) {
            operand->name = "DH";
        } else {
            operand->name = "SI";
        }
        break;
      case 0b00000111:
        if(width == 0) {
            operand->name = "BH";
        } else {
            operand->name = "DI";
        }
        break;
      default:
        printf("No register found");
        exit(1);
    }

    return operand;
}

void populate_definition(
        Definition *empty_definition,
        uint8_t direction_value,
        uint8_t width_value,
        bool has_r_m) {
    empty_definition->has_r_m = has_r_m;
    empty_definition->direction_value = direction_value;
    empty_definition->width_value = width_value;
}

// NOTE: op-code is variable size
// NOTE: currently target only the mov instruction
Definition *instruction_definition(uint8_t instruction) {
   // 100010dw -> register/memory to/from register
   // 1100011w -> immediate to register/memory
   // 1011wreg -> immediate to register
   // 1010000w -> memory to accumulator
   // 1010001w -> accumulator to memory
   
    Definition *definition = malloc(sizeof(Definition));
    if(definition == NULL) {
        printf("Could not allocate instruction definition");
        exit(1);
    }

   if((instruction & create_mask(8, 2)) == 0b10001000) {
       definition->name = "mov";
       // direction is expected to be 0/1 bit, shift bit from pos 2^1 -> 2^0
       int8_t direction = (instruction & create_mask(2, 1)) >> 1;
       int8_t width = instruction & create_mask(1, 0);
       populate_definition(definition, direction, width, true);
   }

   if((instruction & create_mask(8, 1)) == 0b11000110) {
       definition->name = "mov";
       int8_t width = instruction & create_mask(1, 0);
       populate_definition(definition, BIT_DISABLED, width, true);
   }

   if((instruction & create_mask(8, 4)) == 0b10110000) {
       definition->name = "mov";
       // width is expected to be 0/1 bit, shift bit from pos 2^3 -> 2^0
       int8_t width = instruction & create_mask(4, 3) >> 3;
       populate_definition(definition, BIT_DISABLED, width, false);
   }

   if((instruction & create_mask(8, 1)) == 0b10100010 ||
        (instruction & create_mask(8, 1)) == 0b10100000) {
       definition->name = "mov";
       int8_t width = instruction & create_mask(1, 0);
       populate_definition(definition, BIT_DISABLED, width, false);
   }

   return definition;

}

/*
 * mod determines operand type
 * d determines operand direction.
 * w determines operand size.
 *
 * MOD | Mode     | Displacement
 * ----+----------+----------------
 * 00  | Memory   | None (*)
 * 01  | Memory   | 8-bit signed
 * 10  | Memory   | 16-bit signed
 * 11  | Register | None
 *
 * (*) Exception: MOD=00, R/M=110
 *     Direct memory addressing with 16-bit address.
 *
 * d | Destination | Source
 * --+-------------+--------
 * 0 | R/M         | REG
 * 1 | REG         | R/M
 *
 *
 * w = 0: 8-bit register
 * w = 1: 16-bit register
 */
 Operands *instruction_operands(
        Definition *definition,
        uint8_t op_code_byte,
        uint8_t reg,
        uint8_t r_m) {
     Operands *operands = malloc(sizeof(Operands));
     if(operands == NULL) {
         printf("Could not initialize operands");
         exit(1);
     }

     uint8_t direction = definition->direction_value;
     Operand *reg_operand = determine_operand(reg, definition->width_value);
     Operand *r_m_operand = determine_operand(r_m, definition->width_value);

     if(direction == 0) {
         operands->source=reg_operand;
         operands->destination=r_m_operand;
     } else {
         operands->source=r_m_operand;
         operands->destination=reg_operand;
     }
    return operands;
}

Instruction **disassemble(uint8_t instruction_bytes[], size_t length){
    int instruction_number = 0;
    // start with a single element Instruction* array
    Instruction **instructions_result = malloc(sizeof(Instruction *));
    for(size_t instruction_index = 0; instruction_index < length; instruction_index ++) {
        uint8_t op_code_byte = instruction_bytes[instruction_index];
        Definition *definition = instruction_definition(op_code_byte);
        Instruction *instruction = malloc(sizeof(Instruction));
        instruction->definition = definition;

        if(definition->has_r_m) {
            if(instruction_index + 1 < length) {
                uint8_t register_byte = instruction_bytes[instruction_index + 1];
                uint8_t mod = mod_value(register_byte);
                uint8_t reg = reg_value(register_byte);
                uint8_t r_m = r_m_value(register_byte);
                
                if(mod == 0b00000011) {
                    instruction->operands = instruction_operands(definition, op_code_byte, reg, r_m);
                } else {
                    //TODO: add displacement logic as well
                }

                instruction_index++;
            } else {
                printf("Instruction requires next byte but it is missing");
                exit(1);
            }
        } else {
            printf("Not implemented yet simple instructions");
            exit(1);
        }
        instructions_result[instruction_number] = instruction;
        instruction_number++;
    }

    return instructions_result;
}


