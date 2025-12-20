#ifndef ES9033_H
#define ES9033_H
#include "pin.h"
#include <Wire.h>

#define ADDR_ES9033RW (0x96 >> 1)
#define ADDR_ES9033W (0x9E >> 1)

bool init_ES9033(void);

bool volumeES9033(uint8_t volume);

void write_1_byte_ES9033(uint8_t adress, u_int8_t registerES9033, uint8_t byte);

void write_1_bit_ES9033(uint8_t registerES9033, uint8_t bitPosition, bool value);

uint8_t read_1_byte_ES9033(uint8_t registerES9033);

#endif