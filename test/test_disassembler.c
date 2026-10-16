#include "disassembler.h"
#include "operand.h"
#include <stdint.h>
#include <string.h>
#include "unity.h"

void setUp(void) {
}

void tearDown() {
}

void test_disassemble_move() {
    // given
    uint8_t instructions[] = {0X89, 0xDA};

    char expected_instruction[] = "mov";
    char expected_destination[] = "DX";
    char expected_source[] = "BX";

    char actual_instruction[4];
    char actual_destination[3];
    char actual_source[3];

    // when
    InstructionList *instruction_list = disassemble(instructions, sizeof(instructions));
    Instruction *pInstruction = instruction_list->instructions[0];
    strcpy(actual_instruction, pInstruction->definition->name);
    strcpy(actual_source, get_name(pInstruction->operands->source));
    strcpy(actual_destination, get_name(pInstruction->operands->destination));

    // then
    // assert instruction
    
    // verify this is reg -> reg instruction
    TEST_ASSERT_EQUAL(REGISTER_VALUE, get_type(pInstruction->operands->source));
    TEST_ASSERT_EQUAL(REGISTER_VALUE, get_type(pInstruction->operands->destination));
    
    // verify reg and r_m names
    TEST_ASSERT_INT_WITHIN(0, 1, instruction_list->size);
    int result_instruction = strcmp(&expected_instruction[0], &actual_instruction[0]);
    int result_source = strcmp(&expected_source[0], &actual_source[0]);
    int result_destination = strcmp(&expected_destination[0], &actual_destination[0]);
    TEST_ASSERT_INT_WITHIN(0, 0, result_instruction);
    TEST_ASSERT_INT_WITHIN(0, 0, result_source);
    TEST_ASSERT_INT_WITHIN(0, 0, result_destination);

    instruction_destroy(instruction_list);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_disassemble_move);
    return UNITY_END();
}
