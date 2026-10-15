#include "register_mapper.h"
#include <stdio.h>
#include <stdlib.h>

Operand *map_register(uint8_t reg, uint8_t width) {
    Operand *operand = malloc(sizeof(Operand));
    switch (reg) {
      case 0b00000000:
        if(width == 0) {
            operand->name = "AL";
        } else{
            operand->name = "AX";
        }
        break;
      case 0b00000001:
        if(width == 0) {
            operand->name = "CL";
        } else{
            operand->name = "CX";
        }
        break;
      case 0b00000010:
        if(width == 0) {
            operand->name = "DL";
        } else{
            operand->name = "DX";
        }
        break;
      case 0b00000011:
        if(width == 0) {
            operand->name = "BL";
        } else {
            operand->name = "BX";
        }
        break;
      case 0b00000100:
        if(width == 0) {
            operand->name = "AH";
        } else{
            operand->name = "SP";
        }
        break;
      case 0b00000101:
        if(width == 0) {
            operand->name = "CH";
        } else{
            operand->name = "BP";
        }
        break;
      case 0b00000110:
        if(width == 0) {
            operand->name = "DH";
        } else {
            operand->name = "SI";
        }
        break;
      case 0b00000111:
        if(width == 0) {
            operand->name = "BH";
        } else {
            operand->name = "DI";
        }
        break;
      default:
        printf("No register found");
        exit(1);
    }

    return operand;
}
