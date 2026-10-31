#include "decode_result_initializer.h"
#include "unity.h"
#include <stdint.h>

void setUp(void) {}
void tearDown(void) {}


//todo: add a destructor as well
void test_initialize(void) {
    char *expected_name = "test";
    DecodeResult *actual_result = initialize(expected_name);
    TEST_ASSERT_EQUAL(expected_name, actual_result->instruction->definition->name);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_initialize);
    return UNITY_END();
}
