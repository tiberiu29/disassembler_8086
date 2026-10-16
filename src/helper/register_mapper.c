#include "register_mapper.h"
#include "operand.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

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
 * Source: Intel 8086 Reference, Table 1-20.
 */
Operand *map_r_m(uint8_t reg, uint8_t width, uint8_t mod, uint8_t *bytes, uint8_t *count_bytes_read) {
    //TODO: deal with displacement here.
    char *name;
    if(mod == 0b00) {
        switch(reg){
            case 0b100:
                name = "SI";
                break;
            case 0b101:
                name = "DI";
                break;
            case 0b111:
                name = "BX";
                break;
            default:
                printf("Displacement not supported yet");
                exit(1);
        }                 
        return init_memory_register_type(name);
    }

    if(mod == 0b11){
        return map_reg(reg, width);
    }

    printf("MOD 01/10 NOT SUPPORTED YET");
    exit(1);
}

Operand *map_reg(uint8_t reg, uint8_t width) {
    char *name;
    switch (reg) {
      case 0b00000000:
        if(width == 0) {
            name = "AL";
        } else{
            name = "AX";
        }
        break;
      case 0b00000001:
        if(width == 0) {
            name = "CL";
        } else{
            name = "CX";
        }
        break;
      case 0b00000010:
        if(width == 0) {
            name = "DL";
        } else{
            name = "DX";
        }
        break;
      case 0b00000011:
        if(width == 0) {
            name = "BL";
        } else {
            name = "BX";
        }
        break;
      case 0b00000100:
        if(width == 0) {
            name = "AH";
        } else{
            name = "SP";
        }
        break;
      case 0b00000101:
        if(width == 0) {
            name = "CH";
        } else{
            name = "BP";
        }
        break;
      case 0b00000110:
        if(width == 0) {
            name = "DH";
        } else {
            name = "SI";
        }
        break;
      case 0b00000111:
        if(width == 0) {
            name = "BH";
        } else {
            name = "DI";
        }
        break;
      default:
        printf("No register found");
        exit(1);
    }

    return init_register_type(name);
}
