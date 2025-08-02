#ifndef MCP23008_H
#define MCP23008_H
#include "pin.h"
#include <Wire.h>

#define ADDR_MCP23008 0b0100000

#define IODIR 0x00
#define IOPOL 0x01
#define GPINT 0x02
#define DEFVAL 0x03
#define INTCON 0x04
#define IOCON 0x05
#define GPPU 0x06
#define INTF 0x07
#define INTCAP 0x08
#define GPIO 0x09
#define OLAT 0x0A

bool init_MCP23008(void);

uint8_t read_Int_MCP23008(void);

void write_1_byte_MCP23008(u_int8_t registerMCP23008, uint8_t byte);

void write_1_bit_MCP23008(u_int8_t registerMCP23008, uint8_t bitPosition, bool value);

uint8_t read_1_byte_MCP23008(uint8_t registerMCP23008);

#endif