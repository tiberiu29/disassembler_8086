#include "push.h"
#include "decode_result_initializer.h"
#include "opcode.h"
#include "mask_generator.h"
#include "register_mapper.h"
#include <stdlib.h>
#define PUSH "push"

DecodeResult *push_to_reg(uint8_t *bytes, size_t length){
    DecodeResult *result = initialize(PUSH);
    uint8_t current_index = 0;

    uint8_t byte = bytes[current_index];
    uint8_t reg= byte & generate_mask(3, 0);

    Operand *operand = map_reg(reg, 1);
    Operands *operands = malloc(sizeof(Operands));
    operands->source=operand;

    result->instruction->operands = operands;
    result->bytes_consumed = current_index + 1;

    return result;
}

static const OpcodePattern push_patterns[] = {
    {
        .mask = 0b11111111,
        .value = 0b11111111, // r_m
        .decode = NULL
    },
    {
        .mask = 0b11111000,
        .value = 0b01010000, // register
        .decode = push_to_reg
    },
    {
        .mask = 0b11100111,
        .value = 0b00000110, // segment register
        .decode = NULL 
    },
};

// count will be mutated with size of array
PatternFamily *get_push_patterns() {
    size_t size = sizeof(push_patterns) / sizeof(push_patterns[0]);
    
    PatternFamily *patterns = malloc(sizeof(PatternFamily));

    patterns->opcodePatterns = push_patterns;
    patterns->size = size;
    return patterns;
}
