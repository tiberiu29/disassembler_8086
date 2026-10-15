#ifndef OP_CODE_PATTERN_H
#define OP_CODE_PATTERN_H
#include "disassembler.h"

typedef struct DecodeResult{
    Instruction *instruction;
    size_t bytes_consumed;
} DecodeResult;

typedef struct OpcodePattern{
    uint8_t mask;
    uint8_t value;
    DecodeResult *(*decode)(uint8_t *bytes, size_t length);
} OpcodePattern;
#endif

