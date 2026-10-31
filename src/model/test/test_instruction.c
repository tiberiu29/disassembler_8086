#include "instruction.h"
#include "operand.h"
#include "unity.h"

void setUp(void) {}

void tearDown() {}

void test_instruction_list_content(){
    Operand *operand = init_register_type("TEST");

    Operands operands = {
        .source=operand,
        .destination=operand,
        .displacement_value=-1
    };

    Definition definition = {
        .name = "TEST"
    };
     
    Instruction instruction = {
        .definition = &definition,
        .operands = &operands
    };

    InstructionList *actual_list = initialize_result_list(); 
    add_to_result(actual_list, &instruction);

    // verify size
    TEST_ASSERT_EQUAL(1, actual_list->size);
    TEST_ASSERT_EQUAL(10, actual_list->capacity);
    // verify content
    Instruction *actual_instruction = actual_list->instructions[0];
    TEST_ASSERT_EQUAL_STRING(definition.name, actual_instruction->definition->name);
}


void test_instruction_list_grows(){
    Operand *operand = init_register_type("TEST");

    Operands operands = {
        .source=operand,
        .destination=operand,
        .displacement_value=-1
    };

    Definition definition = {
        .name = "TEST"
    };
     
    Instruction instruction = {
        .definition = &definition,
        .operands = &operands
    };

    InstructionList *actual_list = initialize_result_list(); 

    for(int i = 0; i < 10; i++){
        add_to_result(actual_list, &instruction);
    }

    // verify size
    TEST_ASSERT_EQUAL(10, actual_list->size);
    TEST_ASSERT_EQUAL(20, actual_list->capacity);

    // verify content
    for(int i = 0; i < 10; i++){
        Instruction *actual_instruction = actual_list->instructions[i];
        TEST_ASSERT_EQUAL_STRING(definition.name, actual_instruction->definition->name);
    }
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_instruction_list_content);
  RUN_TEST(test_instruction_list_grows);
  return UNITY_END();
}
