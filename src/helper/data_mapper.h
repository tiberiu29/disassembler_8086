#ifndef DATA_MAPPER_H
#define DATA_MAPPER_H
#include <stdint.h>
int16_t calculate_data_8_bits(uint8_t *bytes, uint8_t *current_index);
int16_t calculate_data_16_bits(uint8_t *bytes, uint8_t *current_index);
#endif
