#ifndef MCP3221_H
#define MCP3221_H
#include "pin.h"
#include <Wire.h>

#define ADDR_MCP3221 0b1001101
#define DATA_BYTES 2

#define ALPHA 90     // adjust
#define MAXALPHA 256 // const
#define NUMSAMPLES 4 // const

unsigned char read_MCP3221(void);

unsigned char ping(void);

unsigned char smoothVolume(char lastSmoothedData);

#endif