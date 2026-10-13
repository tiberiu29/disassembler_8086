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
    char actual_instruction[4];

    // when
    Instruction **dissasembled_instructions = disassemble(instructions, sizeof(instructions));
    Instruction *pInstruction = dissasembled_instructions[0];
    strcpy(actual_instruction, pInstruction->definition->name);

    // then
    int result = strcmp(&expected_instruction[0], &actual_instruction[0]);
    TEST_ASSERT_INT_WITHIN(0, 0, result);
    TEST_ASSERT_INT_WITHIN(0, 0, pInstruction->definition->width_bit_position);
    TEST_ASSERT_INT_WITHIN(0, 1, pInstruction->definition->direction_bit_position);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_disassemble_move);
    return UNITY_END();
}
