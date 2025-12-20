#ifndef MCP3221_H
#define MCP3221_H
#include "pin.h"
#include <HardwareSerial.h>
#include <Wire.h>

#define ADDR_MCP3221A5_VOLUME 0b1001101
#define ADDR_MCP3221A6_GAIN 0b1001110
#define DATA_BYTES 2

#define NUMSAMPLES 4 // const

unsigned int read_MCP3221(char addr, unsigned char res);

unsigned char ping(char addr);

unsigned int cmd_potentiometer(unsigned int lastRead, char addr,
                               unsigned char bitResolution);

#endif