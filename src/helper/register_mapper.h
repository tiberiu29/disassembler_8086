#ifndef REGISTER_MAPPER_H
#define REGISTER_MAPPER_H
#include <stdint.h>
#include <disassembler.h>

/*
 * R/M | MOD=00   | MOD=01          | MOD=10          | MOD=11 (W=0 / W=1)
 * ----+----------+-----------------+-----------------+------------------
 * 000 | [BX+SI]  | [BX+SI+disp8]   | [BX+SI+disp16]  | AL / AX
 * 001 | [BX+DI]  | [BX+DI+disp8]   | [BX+DI+disp16]  | CL / CX
 * 010 | [BP+SI]  | [BP+SI+disp8]   | [BP+SI+disp16]  | DL / DX
 * 011 | [BP+DI]  | [BP+DI+disp8]   | [BP+DI+disp16]  | BL / BX
 * 100 | [SI]     | [SI+disp8]      | [SI+disp16]     | AH / SP
 * 101 | [DI]     | [DI+disp8]      | [DI+disp16]     | CH / BP
 * 110 | [disp16] | [BP+disp8]      | [BP+disp16]     | DH / SI
 * 111 | [BX]     | [BX+disp8]      | [BX+disp16]     | BH / DI
 *
 * MOD=00: Memory addressing, no displacement (except R/M=110).
 * MOD=01: Memory addressing, signed 8-bit displacement.
 * MOD=10: Memory addressing, 16-bit displacement.
 * MOD=11: Register addressing, selected using R/M and W.
 *
 * Special case:
 *   [BP] is encoded as MOD=01, R/M=110, disp8=0.
 *
 */
Operand *map_r_m(uint8_t reg, uint8_t width, uint8_t mod, uint8_t *bytes, uint8_t *count_bytes_read);

/*
 *
 * REG | W = 0 | W = 1
 * ----+-------+-------
 * 000 |  AL   |  AX
 * 001 |  CL   |  CX
 * 010 |  DL   |  DX
 * 011 |  BL   |  BX
 * 100 |  AH   |  SP
 * 101 |  CH   |  BP
 * 110 |  DH   |  SI
 * 111 |  BH   |  DI
 */
Operand *map_reg(uint8_t reg, uint8_t width);
#endif
