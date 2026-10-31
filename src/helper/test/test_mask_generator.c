#include "mask_generator.h"
#include "unity.h"
#include <stdint.h>

void setUp(void) {}
void tearDown(void) {}

void test_generate_mask(void) {
    uint8_t expected_mask = 0b00111000;
    uint8_t actual_mask = generate_mask(6, 3);

    TEST_ASSERT_EQUAL(expected_mask, actual_mask);
}

void test_generate_mask_edge(void) {
    uint8_t expected_mask = 0b11111000;
    uint8_t actual_mask = generate_mask(8, 3);

    TEST_ASSERT_EQUAL(expected_mask, actual_mask);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_generate_mask);
    RUN_TEST(test_generate_mask_edge);
    return UNITY_END();
}
