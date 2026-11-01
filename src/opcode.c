#include "opcode.h"
#include "mov.h"
#include "push.h"

OpcodePatternList *get_available_patterns() {
   OpcodePatternList *available_pattern_families[] = {
       get_mov_patterns(),
       get_push_patterns()
   };

   size_t pattern_families_size = sizeof(available_pattern_families);

  return get_mov_patterns();  
}
