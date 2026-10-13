#include "disassembler.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define BIT_DISABLED UINT8_MAX

uint8_t mask_of_n_bits(uint8_t n){
    if(n < 1 || n > 8) {
        printf("mask for 1 byte cannot be higher than 8 bits or lower than 1 bit");
        exit(1);
    }
    return ((1u << n) - 1u) << (8 - n);
}

void populate_definition(
        Definition *empty_definition,
        uint8_t direction_bit_position,
        uint8_t width_bit_position,
        bool has_r_m) {
        empty_definition->has_r_m = has_r_m;
        empty_definition->direction_bit_position = direction_bit_position;
        empty_definition->width_bit_position= width_bit_position;
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

    definition->name = "mov";
   if((instruction & mask_of_n_bits(6)) == 0b10001000) {
       populate_definition(definition, 1, 0, true);
   }

   if((instruction & mask_of_n_bits(7)) == 0b11000110) {
       populate_definition(definition, BIT_DISABLED, 0, true);
   }

   if((instruction & mask_of_n_bits(4)) == 0b10110000) {
       populate_definition(definition, BIT_DISABLED, 3, false);
   }

   if((instruction & mask_of_n_bits(7)) == 0b10100010 ||
        (instruction & mask_of_n_bits(7)) == 0b10100000) {
       populate_definition(definition, BIT_DISABLED, 0, false);
   }

   return definition;

}

Instruction **disassemble(uint8_t instruction_bytes[], size_t length){
    int instruction_number = 0;
    // start with a single element Instruction* array
    Instruction **instructions_result = malloc(sizeof(Instruction *));
    for(size_t instruction_index = 0; instruction_index < length; instruction_index ++) {
        uint8_t byte_1 = instruction_bytes[instruction_index];
        //TODO: figure out the op-code to map to mov
        Definition *definition = instruction_definition(byte_1);
        Instruction *instruction = malloc(sizeof(Instruction));
        instruction->definition = definition;

        if(definition->has_r_m) {
            uint8_t byte_2 = instruction_bytes[instruction_index + 1];
            instruction_index++;
            //TODO: determine whether displacement or immediate bytes exist, extract and advance instruction_index
            instruction->options = NULL;
        } else {
            printf("Not implemented yet simple instructions");
            exit(1);
        }
        instructions_result[instruction_number] = instruction;
        instruction_number++;
    }

    return instructions_result;
}


