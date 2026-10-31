#include "mov.h"
#include "operand.h"
#include "unity.h"
#include <stdlib.h>

void setUp(void) {}

void tearDown() {}

void test_disassemble_move_reg_to_reg() {
  // given
  size_t *count = malloc(sizeof(size_t));
  uint8_t instructions[] = {0X89, 0xDA};

  char expected_instruction[] = "mov";
  char expected_destination[] = "DX";
  char expected_source[] = "BX";

  // when
  DecodeResult *actual_result = 
      get_mov_patterns(count)[0].decode(instructions, sizeof(instructions));

  Instruction *actual_instruction = actual_result->instruction;

  // then
  // verify reg -> reg instruction
  TEST_ASSERT_EQUAL(REGISTER_VALUE, get_type(actual_instruction->operands->source));
  TEST_ASSERT_EQUAL(REGISTER_VALUE, get_type(actual_instruction->operands->destination));

  // assert operands
  TEST_ASSERT_EQUAL_STRING(expected_instruction, actual_instruction->definition->name);
  TEST_ASSERT_EQUAL_STRING(expected_source, get_name(actual_instruction->operands->source));
  TEST_ASSERT_EQUAL_STRING(expected_destination, get_name(actual_instruction->operands->destination));
  free(count);
}

void test_disassemble_move_reg_to_memory() {
  // given
  size_t *count = malloc(sizeof(size_t));
  uint8_t instructions[] = {0X8b, 0x17};

  char expected_instruction[] = "mov";
  char expected_destination[] = "DX";
  char expected_source[] = "[BX]";


  // when
  DecodeResult *actual_result = 
      get_mov_patterns(count)[0].decode(instructions, sizeof(instructions));
  Instruction *actual_instruction = actual_result->instruction;
  
  // then
  // verify mem -> reg instruction
  TEST_ASSERT_EQUAL(REGISTER_MEMORY, get_type(actual_instruction->operands->source));
  TEST_ASSERT_EQUAL(REGISTER_VALUE, get_type(actual_instruction->operands->destination));


  // assert operands
  TEST_ASSERT_EQUAL_STRING(expected_instruction, actual_instruction->definition->name);
  TEST_ASSERT_EQUAL_STRING(expected_destination, get_name(actual_instruction->operands->destination));
  TEST_ASSERT_EQUAL_STRING(expected_source, get_name(actual_instruction->operands->source));
  free(count);
}


void test_disassemble_move_immediate_8_bits_to_reg_positive() {
  // given
  size_t *count = malloc(sizeof(size_t));
  uint8_t instructions[] = {0Xb2, 0xa};

  char expected_instruction[] = "mov";
  // need to use an 8 bit register
  char expected_destination[] = "DL";
  int16_t expected_source = 0xa; //10


  // when
  DecodeResult *actual_result = 
      get_mov_patterns(count)[2].decode(instructions, sizeof(instructions));
  Instruction *actual_instruction = actual_result->instruction;
  
  // then
  // verify mem -> reg instruction
  TEST_ASSERT_EQUAL(IMMEDIATE, get_type(actual_instruction->operands->source));
  TEST_ASSERT_EQUAL(REGISTER_VALUE, get_type(actual_instruction->operands->destination));


  // assert operands
  TEST_ASSERT_EQUAL_STRING(expected_instruction, actual_instruction->definition->name);
  TEST_ASSERT_EQUAL_STRING(expected_destination, get_name(actual_instruction->operands->destination));
  TEST_ASSERT_EQUAL(expected_source, get_immediate_value(actual_instruction->operands->source));
  free(count);
}
void test_disassemble_move_immediate_16_bits_to_reg_negative() {
  size_t *count = malloc(sizeof(size_t));
  uint8_t instructions[] = {0Xba, 0x2e, 0xfb};

  char expected_instruction[] = "mov";
  char expected_destination[] = "DX";
  int16_t expected_source = 0xfb2e; //-1234


  // when
  DecodeResult *actual_result = 
      get_mov_patterns(count)[2].decode(instructions, sizeof(instructions));
  Instruction *actual_instruction = actual_result->instruction;
  
  // then
  // verify mem -> reg instruction
  TEST_ASSERT_EQUAL(IMMEDIATE, get_type(actual_instruction->operands->source));
  TEST_ASSERT_EQUAL(REGISTER_VALUE, get_type(actual_instruction->operands->destination));


  // assert operands
  TEST_ASSERT_EQUAL_STRING(expected_instruction, actual_instruction->definition->name);
  TEST_ASSERT_EQUAL_STRING(expected_destination, get_name(actual_instruction->operands->destination));
  TEST_ASSERT_EQUAL(expected_source, get_immediate_value(actual_instruction->operands->source));
  free(count);

}
int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_disassemble_move_reg_to_reg); 
  RUN_TEST(test_disassemble_move_reg_to_memory);
  RUN_TEST(test_disassemble_move_immediate_8_bits_to_reg_positive);
  RUN_TEST(test_disassemble_move_immediate_16_bits_to_reg_negative);
  return UNITY_END();
}
