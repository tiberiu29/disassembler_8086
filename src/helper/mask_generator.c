#include <stdio.h>
#include <stdlib.h>
#include "mask_generator.h"

uint8_t generate_mask(uint8_t end, uint8_t start) {
    if(end < 1 || end > 8) {
        printf("Contiguous 1 mask cannot start after bit 8 or before bit 1");
        exit(1);
    }
    uint8_t width = end - start;
    return ((1u << width) - 1u) << start;
}
