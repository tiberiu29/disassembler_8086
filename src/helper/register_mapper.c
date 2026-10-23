#include "register_mapper.h"
#include "operand.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

char *calculate_register(char *name, int16_t displacement) {
   char *sign = "+";
   if(displacement < 0) {
       // convert to positive complement such that we only manipulate sign
       sign = "-";
       displacement = ~displacement + 1;
   }
   size_t buffer_size = snprintf(NULL, 0, "[%s %s %d]", name, sign, displacement) + 1;
   char *buffer = malloc(buffer_size);

   snprintf(buffer, buffer_size, "[%s %s %d]", name, sign, displacement);

   return buffer;
}

int16_t calculate_displacement_8(uint8_t *bytes, uint8_t *current_index) {
    *current_index = *current_index + 1;
    return bytes[*current_index];
}
// 8086 is little-endian ->lsb will be the first byte and msb the second byte
int calculate_displacement_16(uint8_t *bytes, uint8_t *current_index) {
    *current_index = *current_index + 1;
    int16_t lsb_16_bit = bytes[*current_index];
    *current_index = *current_index + 1;
    int16_t msb_16_bit = bytes[*current_index] << 8;

    return lsb_16_bit | msb_16_bit;
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

Operand *map_r_m_mod_10(uint8_t reg, uint8_t *bytes, uint8_t *current_index) {
    //TODO rest later
    char *name;
    switch(reg){
        case 0b111:
            int displacement = calculate_displacement_16(bytes, current_index);
            name = calculate_register("BX", displacement);
            break;
        default:
            printf("R_M not valid");
            exit(1);
    }
        return init_memory_register_type(name);
}


Operand *map_r_m_mod_00(uint8_t reg, uint8_t *bytes, uint8_t *count_bytes_read) {
    char *name;
    switch(reg){
        case 0b000:
            name = "[BX+SI]";
            break;
        case 0b001:
            name = "[BX+DI]";
            break;
        case 0b010:
            name = "[BP+SI]";
            break;
        case 0b011:
            name = "[BP+DI]";
            break;
        case 0b100:
            name = "[SI]";
            break;
        case 0b101:
            name = "[DI]";
            break;
        case 0b110:
            printf("Special case MOD 00 R_M 110 not supported yet");
            exit(1);
            break;
        case 0b111:
            name = "[BX]";
            break;
        default:
            printf("R_M not valid");
            exit(1);
    }
        return init_memory_register_type(name);
}

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
Operand *map_r_m(uint8_t reg, uint8_t width, uint8_t mod, uint8_t *bytes, uint8_t *current_index) {
    //TODO: deal with displacement here.
    if(mod == 0b00) {
        return map_r_m_mod_00(reg, bytes, current_index);
    }

    if(mod == 0b10){
        return map_r_m_mod_10(reg, bytes, current_index);
    }

    if(mod == 0b11){
        return map_reg(reg, width);
    }

    printf("MOD 01/10 NOT SUPPORTED YET");
    exit(1);
}

