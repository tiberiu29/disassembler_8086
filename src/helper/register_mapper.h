#ifndef REGISTER_MAPPER_H
#define REGISTER_MAPPER_H
#include <stdint.h>
#include <disassembler.h>

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
Operand *map_r_m(uint8_t reg, uint8_t width, uint8_t mod, uint8_t *bytes, uint8_t *count_bytes_read);
Operand *map_reg(uint8_t reg, uint8_t width);
#endif
