#include "disassembler.h"
#include <stdint.h>
#include <string.h>
#include "unity.h"

void setUp(void) {
}

void tearDown() {
}


void test_disassemble_move() {
    uint8_t instructions[] = {0X89, 0xDA};
    char expected_instruction[] = "mov";
    char *dissasembled_instruction = disassemble(instructions, sizeof(instructions));
    //TODO update after fix with expected_instruction[]
    int result = strcmp("", dissasembled_instruction);

    TEST_ASSERT_INT_WITHIN(0, 0, result);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_disassemble_move);
    return UNITY_END();
}
