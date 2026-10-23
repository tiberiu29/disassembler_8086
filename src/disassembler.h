#ifndef DISASSEMBLER_H
#define DISASSEMBLER_H
#include "instruction.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

InstructionList *disassemble(uint8_t instructions[], size_t length);

void instruction_destroy(InstructionList *instructions);
#endif // !
