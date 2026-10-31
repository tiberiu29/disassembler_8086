#include "register_mapper.h"
#include "operand.h"
#include "unity.h"
#include <stdint.h>
#include <stdio.h>

const size_t mod_00 = 0b00;
const size_t mod_10 = 0b10;
const size_t mod_11 = 0b11;

void setUp(void) {}
void tearDown(void) {}

void test_map_reg_8_bit(void) {
    const char *expected[] = {"AL", "CL", "DL", "BL", "AH", "CH", "DH", "BH"};
    for (uint8_t reg = 0; reg < 8; ++reg) {
        Operand *op = map_reg(reg, 0);
        TEST_ASSERT_NOT_NULL(op);
        TEST_ASSERT_EQUAL_INT(REGISTER_VALUE, get_type(op));
        TEST_ASSERT_EQUAL_STRING(expected[reg], get_name(op));
        operand_destroy(op);
    }
}

void test_map_reg_16_bit(void) {
    const char *expected[] = {"AX", "CX", "DX", "BX", "SP", "BP", "SI", "DI"};
    for (uint8_t reg = 0; reg < 8; ++reg) {
        Operand *op = map_reg(reg, 1);
        TEST_ASSERT_NOT_NULL(op);
        TEST_ASSERT_EQUAL_INT(REGISTER_VALUE, get_type(op));
        TEST_ASSERT_EQUAL_STRING(expected[reg], get_name(op));
        operand_destroy(op);
    }
}

void test_mod_00(void) {
    const char *expected[] = {
        "[BX+SI]", 
        "[BX+DI]",
        "[BP+SI]",
        "[BP+DI]",
        "[SI]", 
        "[DI]",
        NULL,
        "[BX]"
    };
    uint8_t bytes[] = {0};
    for (uint8_t rm = 0; rm < 8; ++rm) {
        if (rm == 6) continue; /* TODO: after implement */
        uint8_t index = 0;
        Operand *op = map_r_m(rm, 1, mod_00, bytes, &index);
        TEST_ASSERT_NOT_NULL(op);
        TEST_ASSERT_EQUAL_INT(REGISTER_MEMORY, get_type(op));
        TEST_ASSERT_EQUAL_STRING(expected[rm], get_name(op));
        TEST_ASSERT_EQUAL_UINT8(0, index);
        operand_destroy(op);
    }
}

void test_mod_10_all_positive_displacement(void) {
    const char *bases[] = {
        "BX + SI",
        "BX + DI",
        "BP + SI",
        "BP + DI",
        "SI",
        "DI",
        "BP",
        "BX"};
    char expected[64];
    uint8_t bytes[] = {0x00, 0x34, 0x12}; // disp16 = 0x1234 = 4660
    for (uint8_t rm = 0; rm < 8; ++rm) {
        uint8_t index = 0;
        Operand *op = map_r_m(rm, 1, mod_10, bytes, &index);
        TEST_ASSERT_NOT_NULL(op);
        TEST_ASSERT_EQUAL_INT(REGISTER_MEMORY, get_type(op));
        snprintf(expected, sizeof(expected), "[%s + 4660]", bases[rm]);
        TEST_ASSERT_EQUAL_STRING(expected, get_name(op));
        TEST_ASSERT_EQUAL_UINT8(2, index);
        operand_destroy(op);
    }
}

void test_mod_10_negative_displacement(void) {
    uint8_t bytes[] = {0x00, 0xFF, 0xFF}; // disp16 = -1 = ~1 + 1 = 0xFFFF
    uint8_t index = 0;
    Operand *op = map_r_m(0b110, 1, mod_10, bytes, &index);
    TEST_ASSERT_NOT_NULL(op);
    TEST_ASSERT_EQUAL_INT(REGISTER_MEMORY, get_type(op));
    TEST_ASSERT_EQUAL_STRING("[BP - 1]", get_name(op));
    TEST_ASSERT_EQUAL_UINT8(2, index);
    operand_destroy(op);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_map_reg_8_bit);
    RUN_TEST(test_map_reg_16_bit);
    RUN_TEST(test_mod_00);
    RUN_TEST(test_mod_10_all_positive_displacement);
    RUN_TEST(test_mod_10_negative_displacement);
    return UNITY_END();
}
