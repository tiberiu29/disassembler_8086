#include "mask_generator.h"
#include "opcode.h"
#include "mask_generator.h"
#include "register_mapper.h"
#include "decode_result_initializer.h"
#include <stdio.h>
#include <stdlib.h>

#define MOV "mov"

uint8_t mod_value(uint8_t byte) {
    return (byte & generate_mask(8, 6)) >> 6;
}

uint8_t reg_value(uint8_t byte) {
    return (byte & generate_mask(6, 3)) >> 3;
}

uint8_t r_m_value(uint8_t byte) {
    return byte & generate_mask(3, 0);
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
DecodeResult *decode_r_m(uint8_t *bytes, size_t capacity) {
    if(capacity < 2) {
        printf("Cannot access R_M byte");
        exit(1);
    }

    DecodeResult *result = initialize(MOV);
    int current_index = 0;
    uint8_t op_code_byte = bytes[current_index];
    int8_t direction = (op_code_byte & generate_mask(2, 1)) >> 1;
    int8_t width = op_code_byte & generate_mask(1, 0);

    current_index ++;
    uint8_t register_byte = bytes[current_index];

    if(register_byte == 0) {
        printf("Something is wrong with R_M byte");
        exit(1);
    }

    uint8_t mod = mod_value(register_byte);

    if(mod == 0b00 || mod == 0b11) {
        uint8_t reg = reg_value(register_byte);
        uint8_t r_m = r_m_value(register_byte);

         Operands *operands = malloc(sizeof(Operands));
         if(operands == NULL) {
             printf("Could not initialize operands");
             exit(1);
         }

         Operand *reg_operand = map_register(reg, width);
         Operand *r_m_operand = map_register(r_m, width);

         if(direction == 0) {
             operands->source=reg_operand;
             operands->destination=r_m_operand;
         } else {
             operands->source=r_m_operand;
             operands->destination=reg_operand;
         }

         result->instruction->operands = operands;
         result->bytes_consumed = current_index + 1;

         return result;

    } else {
        // TODO: deal with displacement later
        return NULL;
    }

}

static const OpcodePattern mov_patterns[] = {
    {
        .mask = 0b11111100,
        .value = 0b10001000, // r_m to/from register
        .decode = decode_r_m
    },
    {
        .mask = 0b11111110,
        .value = 0b11000110, // immediate to r_m
        .decode = NULL
    },
    {
        .mask = 0b11110000,
        .value = 0b10110000, // immediate to register
        .decode = NULL
    },
    {
        .mask = 0b11111110,
        .value = 0b10100000, // memory to accumulator
        .decode = NULL
    },
    {
        .mask = 0b11111110,
        .value = 0b10100010, // accumulator to memory
        .decode = NULL
    }
};

// count will be mutated with size of array
const OpcodePattern *get_mov_patterns(size_t *count) {
    *count = sizeof(mov_patterns) / sizeof(mov_patterns[0]);
    return mov_patterns;
}
