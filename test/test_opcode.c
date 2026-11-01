#include "opcode.h"
#include "unity.h"

void setUp(void) {}

void tearDown() {}

void test_pattern_families_result() {
    get_available_patterns();
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_pattern_families_result);
  return UNITY_END();
}
