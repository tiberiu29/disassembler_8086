#include "disassembler.h"
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
    char expected_source[] = "DX";
    char expected_destination[] = "BX";

    char actual_instruction[4];
    char actual_source[3];
    char actual_destination[3];

    // when
    Instruction **dissasembled_instructions = disassemble(instructions, sizeof(instructions));
    Instruction *pInstruction = dissasembled_instructions[0];
    strcpy(actual_instruction, pInstruction->definition->name);
    strcpy(actual_source, pInstruction->operands->source->name);
    strcpy(actual_destination, pInstruction->operands->destination->name);

    // then
    int result_instruction = strcmp(&expected_instruction[0], &actual_instruction[0]);
    int result_source = strcmp(&expected_source[0], &actual_source[0]);
    int result_destination = strcmp(&expected_destination[0], &actual_destination[0]);
    TEST_ASSERT_INT_WITHIN(0, 0, result_instruction);
    TEST_ASSERT_INT_WITHIN(0, 0, result_source);
    TEST_ASSERT_INT_WITHIN(0, 0, result_destination);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_disassemble_move);
    return UNITY_END();
}
