#ifndef INSTRUCTION_H
#define INSTRUCTION_H
#include "operand.h"
#include <stdio.h>
typedef struct Definition {
  char *name;
} Definition;

typedef struct Operands {
  Operand *source;
  Operand *destination;
  int16_t displacement_value;
} Operands;

typedef struct Instruction {
  Definition *definition;
  Operands *operands;
} Instruction;

typedef struct InstructionList {
  Instruction **instructions;
  size_t size;
  size_t capacity;
} InstructionList;

InstructionList *initialize_result_list();
void add_to_result(InstructionList *instruction_list, Instruction *instruction);
#endif
