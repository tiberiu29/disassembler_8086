#include "data_mapper.h"

int16_t calculate_data_8_bits(uint8_t *bytes, uint8_t *current_index) {
    *current_index = *current_index + 1;
    return bytes[*current_index];
}

// 8086 is little-endian ->lsb will be the first byte and msb the second byte
int16_t calculate_data_16_bits(uint8_t *bytes, uint8_t *current_index) {
    *current_index = *current_index + 1;
    int16_t lsb_16_bit = bytes[*current_index];
    *current_index = *current_index + 1;
    int16_t msb_16_bit = bytes[*current_index] << 8;

    return lsb_16_bit | msb_16_bit;
}
