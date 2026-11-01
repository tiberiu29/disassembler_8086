#include "push.h"
#include "opcode.h"
#include <stdlib.h>

static const OpcodePattern push_patterns[] = {
    {
        .mask = 0b11111111,
        .value = 0b11111111, // r_m
        .decode = NULL
    },
    {
        .mask = 0b11111000,
        .value = 0b01010000, // register
        .decode = NULL
    },
    {
        .mask = 0b11100111,
        .value = 0b00000110, // segment register
        .decode = NULL 
    },
};

// count will be mutated with size of array
const OpcodePatternList *get_push_patterns() {
    size_t size = sizeof(push_patterns) / sizeof(push_patterns[0]);
    
    OpcodePatternList *patterns = malloc(sizeof(OpcodePatternList));

    patterns->opcodePatterns = push_patterns;
    patterns->size = size;
    return patterns;
}
