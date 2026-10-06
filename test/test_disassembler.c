#include "disassembler.h"
#include <stdint.h>
#include <string.h>
#include "unity.h"

void setUp(void) {
}

void tearDown() {
}


void test_disassemble_move() {
    uint16_t instruction = 0x89DA;
    char expected_instruction[] = "mov";
    char *dissasembled_instruction = disassemble(instruction);
    int result = strcmp(expected_instruction, dissasembled_instruction);

    TEST_ASSERT_INT_WITHIN(0, 0, result);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_disassemble_move);
    return UNITY_END();
}
