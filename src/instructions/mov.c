#include "data_mapper.h"
#include "mask_generator.h"
#include "opcode.h"
#include "mask_generator.h"
#include "operand.h"
#include "register_mapper.h"
#include "decode_result_initializer.h"
#include <stdio.h>
#include <stdlib.h>

#define MOV "mov"

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
    uint8_t current_index = 0;
    uint8_t op_code_byte = bytes[current_index];
    int8_t direction = (op_code_byte & generate_mask(2, 1)) >> 1;
    int8_t width = op_code_byte & generate_mask(1, 0);

    current_index ++;
    uint8_t register_byte = bytes[current_index];

    if(register_byte == 0) {
        printf("Something is wrong with R_M byte");
        exit(1);
    }

    uint8_t mod = (register_byte & generate_mask(8, 6)) >> 6;
    uint8_t reg = (register_byte & generate_mask(6, 3)) >> 3;
    uint8_t r_m = register_byte & generate_mask(3, 0);

     Operands *operands = malloc(sizeof(Operands));
     if(operands == NULL) {
         printf("Could not initialize operands");
         exit(1);
     }

     Operand *reg_operand = map_reg(reg, width);
     Operand *r_m_operand = map_r_m(r_m, width, mod, bytes, &current_index);

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
}


DecodeResult *decode_immediate_to_reg(uint8_t *bytes, size_t capacity) {
    if(capacity < 2) {
        printf("Cannot access immediate byte");
        exit(1);
    }

    DecodeResult *result = initialize(MOV);
    uint8_t current_index = 0;
    uint8_t register_byte = bytes[current_index];

    uint8_t width = register_byte & generate_mask(4, 3);
    uint8_t reg = register_byte & generate_mask(3, 0);

    uint16_t immediate_value = width = 1 ?
        calculate_data_16_bits(bytes, &current_index) :
        calculate_data_8_bits(bytes, &current_index);

     Operands *operands = malloc(sizeof(Operands));
     if(operands == NULL) {
         printf("Could not initialize operands");
         exit(1);
     }

     operands->source = init_immediate_type(immediate_value);
     operands->destination = map_reg(reg, width);;

     result->instruction->operands = operands;
     result->bytes_consumed = current_index + 1;

    return result;
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
        .decode = decode_immediate_to_reg
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
