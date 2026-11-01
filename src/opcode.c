#include "opcode.h"
#include "mov.h"
#include "push.h"
#include <stdlib.h>

OpcodePatternList **get_available_patterns(size_t *count) {
  OpcodePatternList *available_pattern_families[] =
  { get_mov_patterns(), get_push_patterns()};


  *count = sizeof(available_pattern_families) / sizeof(OpcodePatternList*);
  OpcodePatternList **final_list = malloc(*count);

  for(size_t family_i = 0; family_i < *count; family_i++) {
    final_list[family_i] = available_pattern_families[family_i];
  }

  return final_list;
}
