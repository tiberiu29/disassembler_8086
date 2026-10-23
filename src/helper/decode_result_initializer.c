#include "decode_result_initializer.h"
#include <stdio.h>
#include <stdlib.h>

DecodeResult *initialize(char *name) {
  DecodeResult *result = malloc(sizeof(DecodeResult));
  if (result == NULL) {
    printf("Could not initialize Decode Result");
    exit(1);
  }

  Instruction *instruction = malloc(sizeof(Instruction));

  if (instruction == NULL) {
    printf("Could not initialize Instruction");
    exit(1);
  }

  Definition *definition = malloc(sizeof(Definition));
  if (definition == NULL) {
    printf("Could not initialize Instruction Definition");
    exit(1);
  }

  result->instruction = instruction;
  instruction->definition = definition;
  instruction->definition->name = name;

  return result;
}
