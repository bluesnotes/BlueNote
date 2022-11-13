#include "MCP23008.h"

bool init_MCP23008(void) {
    Wire.begin();
    Wire.setClock(100000L);
    Wire.beginTransmission(ADDR_MCP23008);
    Wire.write(0x00); // input/output settings
    Wire.write(0b10111111);
    Wire.endTransmission();

    Wire.beginTransmission(ADDR_MCP23008);
    Wire.write(0x06); // pull-up resistor
    Wire.write(0b00111111);
    Wire.endTransmission();

    Wire.beginTransmission(ADDR_MCP23008);
    Wire.write(0x04); // INTCON
    Wire.write(0b00111111);
    Wire.endTransmission();

    Wire.beginTransmission(ADDR_MCP23008);
    Wire.write(0x03); // DEFVAL
    Wire.write(0b00111111);
    Wire.endTransmission();

    Wire.beginTransmission(ADDR_MCP23008);
    Wire.write(0x05); // int out at 1 or 0
    Wire.write(0b00000010);
    Wire.endTransmission();

    Wire.beginTransmission(ADDR_MCP23008);
    Wire.write(0x02); // pin interrupt on change enable
    Wire.write(0b00011111);
    Wire.endTransmission();

    Wire.beginTransmission(ADDR_MCP23008);
    Wire.write(0x08); // INT CAP register
    Wire.endTransmission();
    Wire.requestFrom(ADDR_MCP23008, 1);
    Wire.read();

    pinMode(INT_MCP23008_PIN, INPUT);

    return true;
}

unsigned char read_MCP23008(void) {
    char inputs = 0;
    Wire.beginTransmission(ADDR_MCP23008);
    Wire.write(0x07); // INT CAP register
    Wire.endTransmission();
    Wire.requestFrom(ADDR_MCP23008, 1);
    inputs = Wire.read();
    inputs &= 0b00111111;

    delay(250);

    Wire.beginTransmission(ADDR_MCP23008);
    Wire.write(0x08); // INT CAP register
    Wire.endTransmission();
    Wire.requestFrom(ADDR_MCP23008, 1);

    return inputs;
}

void write_MCP23008(bool reset_ADAU1701) {
    char portRegister = 0;
    char output = reset_ADAU1701 << 6;
    Wire.beginTransmission(ADDR_MCP23008);
    Wire.write(0x09); // PORT register
    Wire.requestFrom(ADDR_MCP23008, 1);
    portRegister = Wire.read() & 0b00111111;
    Wire.beginTransmission(ADDR_MCP23008);
    Wire.write(0x09); // PORT register
    Wire.write(output | portRegister);
}