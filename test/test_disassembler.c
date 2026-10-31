#include "disassembler.h"
#include "operand.h"
#include "unity.h"
#include <stdint.h>

void setUp(void) {}

void tearDown() {}

void test_disassemble_move_reg_to_memory_with_displacement() {
  // given
  uint8_t instructions[] = {
      0X8b, 0x97, 0xd2, 0x04,
      0X8b, 0x97, 0x2e, 0xfb
  };

  char expected_instruction[] = "mov";
  char expected_destination[] = "DX";
  char expected_source_1[] = "[BX + 1234]";
  char expected_source_2[] = "[BX - 1234]";


  // when
  InstructionList *instruction_list = disassemble(instructions, sizeof(instructions));
  Instruction *actual_instruction_1 = instruction_list->instructions[0];
  Instruction *actual_instruction_2 = instruction_list->instructions[1];

  // then
  // assert instructions

  // verify this is memory -> reg instruction
  TEST_ASSERT_EQUAL(REGISTER_MEMORY, get_type(actual_instruction_1->operands->source));
  TEST_ASSERT_EQUAL(REGISTER_VALUE, get_type(actual_instruction_1->operands->destination));
  TEST_ASSERT_EQUAL(REGISTER_MEMORY, get_type(actual_instruction_2->operands->source));
  TEST_ASSERT_EQUAL(REGISTER_VALUE, get_type(actual_instruction_2->operands->destination));

  // verify reg and r_m names
  TEST_ASSERT_INT_WITHIN(0, 2, instruction_list->size);

  // assert operands
  TEST_ASSERT_EQUAL_STRING(expected_instruction, actual_instruction_1->definition->name);
  TEST_ASSERT_EQUAL_STRING(expected_destination, get_name(actual_instruction_1->operands->destination));
  TEST_ASSERT_EQUAL_STRING(expected_source_1, get_name(actual_instruction_1->operands->source));

  TEST_ASSERT_EQUAL_STRING(expected_instruction, actual_instruction_2->definition->name);
  TEST_ASSERT_EQUAL_STRING(expected_destination, get_name(actual_instruction_2->operands->destination));
  TEST_ASSERT_EQUAL_STRING(expected_source_2, get_name(actual_instruction_2->operands->source));
  instruction_destroy(instruction_list);
}

void test_instruction_list_growth() {
  // given
  uint8_t instructions[] = {
      0X8b, 0x97, 0xd2, 0x04,
      0X8b, 0x97, 0xd2, 0x04,
      0X8b, 0x97, 0xd2, 0x04,
      0X8b, 0x97, 0xd2, 0x04,
      0X8b, 0x97, 0xd2, 0x04,
      0X8b, 0x97, 0xd2, 0x04,
      0X8b, 0x97, 0xd2, 0x04,
      0X8b, 0x97, 0xd2, 0x04,
      0X8b, 0x97, 0xd2, 0x04,
      0X8b, 0x97, 0xd2, 0x04,
      0X8b, 0x97, 0xd2, 0x04,
  };


  // when
  InstructionList *instruction_list = disassemble(instructions, sizeof(instructions));

  // then
  TEST_ASSERT_INT_WITHIN(0, 11, instruction_list->size);
  TEST_ASSERT_INT_WITHIN(0, 20, instruction_list->capacity);

  instruction_destroy(instruction_list);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_instruction_list_growth);
  RUN_TEST(test_disassemble_move_reg_to_memory_with_displacement);
  return UNITY_END();
}
