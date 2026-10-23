#include "disassembler.h"
#include "mov.h"
#include "opcode.h"
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

InstructionList *disassemble(uint8_t instruction_bytes[], size_t length){
    size_t *patterns_size = malloc(sizeof(size_t));
    const OpcodePattern *patterns = get_mov_patterns(patterns_size);
    InstructionList *instructions_result = initialize_result_list();

    for(size_t byte_index = 0; byte_index < length; byte_index++) {
        uint8_t *instruction_byte = &instruction_bytes[byte_index];
        for(size_t pattern_i = 0; pattern_i < *patterns_size; pattern_i++) {
            if((*instruction_byte & patterns[pattern_i].mask) == patterns[pattern_i].value) {
                DecodeResult *decoded_instruction = patterns->decode(instruction_byte, length - byte_index);
                add_to_result(instructions_result, decoded_instruction->instruction);
                byte_index = byte_index + (decoded_instruction->bytes_consumed - 1);
                break;
            } else{
                printf("Invalid Instruction");
                exit(1);
            }
        }
    }

    return instructions_result;
}


