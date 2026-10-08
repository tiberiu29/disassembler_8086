#include "disassembler.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

uint8_t mask_of_n_bits(uint8_t n){
    if(n < 1 || n > 8) {
        printf("mask for 1 byte cannot be higher than 8 bits or lower than 1 bit");
        exit(1);
    }
    return ((1u << n) - 1u) << (8 - n);
}

// NOTE: op-code is variable size
// NOTE: currently target only the mov instruction
bool is_complex_instruction(uint8_t instruction) {
   // 100010dw -> register/memory to/from register
   // 1100011w -> immediate to register/memory
   // 1011wreg -> immediate to register
   // 1010000w -> memory to accumulator
   // 1010001w -> accumulator to memory
   if((instruction & mask_of_n_bits(6)) == 0b10001000 ||
       (instruction & mask_of_n_bits(7)) == 0b11000110) {
       return true;
   }

   if((instruction & mask_of_n_bits(4)) == 0b10110000 ||
        (instruction & mask_of_n_bits(7)) == 0b10100000 ||
        (instruction & mask_of_n_bits(7)) == 0b10100010){
        return false;
   }

   printf("Unrecognized instruction");
   exit(1);

}

char *disassemble(uint8_t instructions[], size_t length){
    // start with a simple 1 element char* array
    char **decoded_instructions = malloc(sizeof(char *));
    int instruction_number = 0;
    for(int instruction_index = 0; instruction_index < length; instruction_index ++) {
        uint8_t byte_1 = instructions[instruction_index];
        //TODO: figure out the op-code to map to mov
        bool is_complex = is_complex_instruction(byte_1);

        if(is_complex) {
            uint8_t byte_2 = instructions[instruction_index + 1];
            instruction_index++;
            //TODO: determine whether displacement or immediate bytes exist, extract and advance instruction_index
        } else {
            printf("Not implemented yet simple instructions");
            exit(1);
        }
        instruction_number++;
    }
    return "";
}


