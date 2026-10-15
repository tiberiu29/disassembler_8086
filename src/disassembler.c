#include "disassembler.h"
#include "mov.h"
#include "opcode.h"
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define BIT_DISABLED UINT8_MAX

InstructionList *initialize_result_list() {
    Instruction **instructions = malloc(10 * sizeof(Instruction *));
    if(instructions == NULL) {
        printf("Could not initialize instruction list");
        exit(1);
    }

    InstructionList *instruction_list = malloc(sizeof(InstructionList));
    if(instruction_list == NULL) {
        printf("Could not initialize instruction list");
        exit(1);
    }

    instruction_list->instructions = instructions; 
    instruction_list->size = 0;
    instruction_list->capacity = 10;

    return instruction_list;
}

void add_to_result(InstructionList *instruction_list, Instruction *instruction) {
    instruction_list->instructions[instruction_list->size] = instruction;    
    instruction_list->size = instruction_list->size + 1;
}

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
                byte_index = byte_index + decoded_instruction->bytes_consumed;
                break;
            } else{
                printf("Invalid Instruction");
                exit(1);
            }
        }
    }

    return instructions_result;
}


