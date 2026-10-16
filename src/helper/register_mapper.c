#include "register_mapper.h"
#include "operand.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

Operand *map_register(uint8_t reg, uint8_t width, bool is_register_memory) {
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

    if(is_register_memory) {
        return init_memory_register_type(name);
    }
    return init_register_type(name);
}
