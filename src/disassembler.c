#include "disassembler.h"
#include "opcode.h"
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

InstructionList *disassemble(uint8_t instruction_bytes[], size_t length){
    size_t *count = malloc(sizeof(size_t));
    OpcodePatternList **pattern_list = get_available_patterns(count);
    InstructionList *instructions_result = initialize_result_list();

    for(size_t byte_index = 0; byte_index < length; byte_index++) {
        uint8_t *instruction_byte = &instruction_bytes[byte_index];
        bool matched_family = false;
        for (size_t family_i = 0; family_i < *count; family_i++){
            OpcodePattern *patterns = pattern_list[family_i]->opcodePatterns;
            const size_t patterns_size = pattern_list[family_i]->size;
            for(size_t pattern_i = 0; pattern_i < patterns_size; pattern_i++) {
                if((*instruction_byte & patterns[pattern_i].mask) == patterns[pattern_i].value) {
                    DecodeResult *decoded_instruction = 
                        patterns[pattern_i].decode(instruction_byte,length - byte_index);

                    add_to_result(instructions_result, decoded_instruction->instruction);
                    byte_index = byte_index + (decoded_instruction->bytes_consumed - 1);
                    matched_family = true;
                    break;
                }
            }
        }
        if(!matched_family) {
            printf("INVALID INSTRUCTION AT POSITION: %zu", byte_index);
            exit(1);
        }
    }

    return instructions_result;
}


