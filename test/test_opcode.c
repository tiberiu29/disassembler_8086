#include "opcode.h"
#include "unity.h"
#include <stdlib.h>

void setUp(void) {}

void tearDown() {}

void test_pattern_families_result() {
    size_t *count = malloc(sizeof(size_t));
    PatternFamily **families = get_supported_pattern_families(count);

    // Currently we support only 2 families MOV + PUSH
    TEST_ASSERT_EQUAL(2, *count);
    // mov size
    TEST_ASSERT_EQUAL(5, families[0]->size);
    // push size
    TEST_ASSERT_EQUAL(3, families[1]->size);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_pattern_families_result);
  return UNITY_END();
}
