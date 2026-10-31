#include "data_mapper.h"
#include "unity.h"
#include <stdint.h>

void setUp(void) {}
void tearDown(void) {}


void test_data_8_bit_with_index_advancement(void) {

    uint8_t current_index = 0;
    uint8_t expected = 0xA;
    uint8_t input_bytes[] = {0x12, expected, 0xB};

    int16_t actual = calculate_data_8_bits(input_bytes, &current_index);
    
    TEST_ASSERT_EQUAL((uint16_t) expected, actual);
    TEST_ASSERT_EQUAL(1, current_index);
}

void test_data_16_bit_with_index_advancement(void) {

    uint8_t current_index = 0;
    uint8_t expected = 0xBA;
    uint8_t input_bytes[] = {0x12, 0xA, 0xB};

    int16_t actual = calculate_data_16_bits(input_bytes, &current_index);
    
    TEST_ASSERT_EQUAL((uint16_t) expected, actual);
    TEST_ASSERT_EQUAL(2, current_index);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_data_8_bit_with_index_advancement);
    return UNITY_END();
}
