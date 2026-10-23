#include "instruction.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BIT_DISABLED UINT8_MAX
#define INITIAL_INSTRUCTION_ARRAY_CAPACITY 10
#define INSTRUCTION_LIST_EXTEND_FACTOR 2

Instruction **initialize_instructions_array(size_t size) {
    Instruction **instructions = malloc(size *sizeof(Instruction *));

    if(instructions == NULL) {
        printf("Coult not initialize instructions list");
        exit(1);
    }

    return instructions;
}

void extend_instruction_list(InstructionList *instruction_list) {
    size_t extended_capacity = instruction_list->capacity * INSTRUCTION_LIST_EXTEND_FACTOR;
    Instruction **extended_instruction_arr = initialize_instructions_array(extended_capacity);
    memcpy(extended_instruction_arr, instruction_list->instructions, instruction_list->size * sizeof(Instruction *));
    instruction_list->capacity = extended_capacity;
}

InstructionList *initialize_result_list() {
    InstructionList *instruction_list = malloc(sizeof(InstructionList));
    if(instruction_list == NULL) {
        printf("Could not initialize instruction list");
        exit(1);
    }

    instruction_list->instructions = initialize_instructions_array(INITIAL_INSTRUCTION_ARRAY_CAPACITY); 
    instruction_list->size = 0;
    instruction_list->capacity = 10;

    return instruction_list;
}

void add_to_result(InstructionList *instruction_list, Instruction *instruction) {
    if(instruction_list->size + 1 == instruction_list->capacity) {
        extend_instruction_list(instruction_list);
    }

    instruction_list->instructions[instruction_list->size] = instruction;    
    instruction_list->size++;
}

void instruction_destroy(InstructionList *instruction_list) {
   for(size_t i = 0; i < instruction_list->size; i++) {
       Instruction *instruction = instruction_list->instructions[i];

       free(instruction->definition);
       operand_destroy(instruction->operands->source);
       operand_destroy(instruction->operands->destination);
       free(instruction);
   }
   free(instruction_list);
}
