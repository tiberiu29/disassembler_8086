#include "register_mapper.h"
#include "operand.h"
#include "data_mapper.h"
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

/*
 * R/M | MOD=10          
 * ----+----------------
 * 000 | [BX+SI+disp16]  
 * 001 | [BX+DI+disp16]  
 * 010 | [BP+SI+disp16]  
 * 011 | [BP+DI+disp16]  
 * 100 | [SI+disp16]     
 * 101 | [DI+disp16]     
 * 110 | [BP+disp16]     
 * 111 | [BX+disp16]     
 *
 * Source: Intel 8086 Reference, Table 1-20.
 */
Operand *map_r_m_mod_10(uint8_t reg, uint8_t *bytes, uint8_t *current_index) {
    //TODO rest later
    char *name;
    int displacement = calculate_data_16_bits(bytes, current_index);
    switch(reg){
        case 0b000:
            name = calculate_register("BX + SI", displacement);
            break;
        case 0b001:
            name = calculate_register("BX + DI", displacement);
            break;
        case 0b010:
            name = calculate_register("BP + SI", displacement);
            break;
        case 0b011:
            name = calculate_register("BP + DI", displacement);
            break;
        case 0b100:
            name = calculate_register("SI", displacement);
            break;
        case 0b101:
            name = calculate_register("DI", displacement);
            break;
        case 0b110:
            name = calculate_register("BP", displacement);
            break;
        case 0b111:
            name = calculate_register("BX", displacement);
            break;
        default:
            printf("R_M not valid");
            exit(1);
    }
        return init_memory_register_type(name);
}


/*
 * R/M | MOD=00   
 * ----+---------
 * 000 | [BX+SI]  
 * 001 | [BX+DI]  
 * 010 | [BP+SI]  
 * 011 | [BP+DI]  
 * 100 | [SI]     
 * 101 | [DI]     
 * 110 | [disp16] 
 * 111 | [BX]     
 *
 * Source: Intel 8086 Reference, Table 1-20.
 */
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

Operand *map_r_m(uint8_t reg, uint8_t width, uint8_t mod, uint8_t *bytes, uint8_t *current_index) {
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

