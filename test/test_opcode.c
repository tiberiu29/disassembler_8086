#include "opcode.h"
#include "unity.h"
#include <stdlib.h>

void setUp(void) {}

void tearDown() {}

void test_pattern_families_result() {
    size_t *count = malloc(sizeof(size_t));
    get_available_patterns(count);

    // Currently we support only 2 families MOV + PUSH
    TEST_ASSERT_EQUAL(2, *count);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_pattern_families_result);
  return UNITY_END();
}
