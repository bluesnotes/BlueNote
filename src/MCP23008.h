#ifndef MCP23008_H
#define MCP23008_H
#include "pin.h"
#include <Wire.h>

#define ADDR_MCP23008 0b0100000

bool init_MCP23008(void);

unsigned char read_MCP23008(void);

void write_MCP23008(bool reset_ADAU1701);

#endif