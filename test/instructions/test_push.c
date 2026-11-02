#include "push.h"
#include "operand.h"
#include "unity.h"

void setUp(void) {}

void tearDown() {}

void test_push_to_reg() {
  uint8_t instructions[] = {0X52};

  char expected_instruction[] = "push";
  char expected_source[] = "DX";

  // when
  DecodeResult *actual_result = 
      get_push_patterns()->opcodePatterns[1].decode(instructions, sizeof(instructions));
  Instruction *actual_instruction = actual_result->instruction;
  
  // then
  TEST_ASSERT_EQUAL(REGISTER_VALUE, get_type(actual_instruction->operands->source));

  // assert operands
  TEST_ASSERT_EQUAL_STRING(expected_instruction, actual_instruction->definition->name);
  TEST_ASSERT_EQUAL_STRING(expected_source, get_name(actual_instruction->operands->source));

}
int main(void) {
  RUN_TEST(test_push_to_reg);
  return UNITY_END();
}
