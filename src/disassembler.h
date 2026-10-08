#ifndef DISASSEMBLER_H
#define DISASSEMBLER_H
#include <stdint.h>
#include <stddef.h>
char *disassemble(uint8_t instructions[], size_t length);
#endif // !
