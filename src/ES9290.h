#ifndef ES9290_H
#define ES9290_H
#include "pin.h"
#include <HardwareSerial.h>
#include <Wire.h>
#include <esp32-hal-gpio.h>
#include <esp32-hal.h>
#include <math.h>

#define ADDR_ES9290 (0x30 >> 1)

bool init_ES9290(void);

// 0xFF mute /0xFE-126dB /0x02 0dB /0x00 +1dB
void volume_ES9290_line(u_int8_t volume);

void volume_ES9290_send(u_int8_t volume);

bool PGA_ES9290_instrument(u_int8_t gain);

bool PGA_ES9290_return(u_int8_t gain);

void return_in_impedance_line(bool onOff);

void instrument_in_impedance_line(bool onOff);

void return_in_pad_line(bool onOffon);

void instrument_in_pad_line(bool onOff);

void write_1_byte_ES9290(u_int8_t registerES9290, uint8_t byte);

void write_1_bit_ES9290(uint8_t registerES9290, uint8_t bitPosition, bool value);

uint8_t read_1_byte_ES9290(uint8_t registerES9290);

#endif