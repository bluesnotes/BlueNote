#include "MCP23008.h"
#include <Arduino.h>

bool init_MCP23008(void) {
    Wire.begin();
    Wire.setTimeOut(10);
    Wire.setClock(100000L);

    write_1_byte_MCP23008(IODIR, 0b10011111); // input/output settings

    write_1_byte_MCP23008(GPPU, 0x00); // no pull-up resistor

    write_1_byte_MCP23008(INTCON, 0x00); // Pin value is compared against the previous pin value

    write_1_byte_MCP23008(DEFVAL, 0b00011111); // define std value of bit for interrupt on change

    write_1_byte_MCP23008(IOCON, 0b00000010); // interrupt out active at 1 or 0 (select1)

    write_1_byte_MCP23008(GPIO, 0b01100000); // LED BACKGROUND ON

    write_1_byte_MCP23008(GPINT, 0b00011111); // in interrupt on change enable

    read_1_byte_MCP23008(INTF);

    pinMode(INT_MCP23008_PIN, INPUT);

    return true;
}
uint8_t read_Int_MCP23008(void) {

    delay(10);
    char intInputs = 0, inputs = 0;
    intInputs = read_1_byte_MCP23008(INTF);

    inputs = read_1_byte_MCP23008(GPIO);

    inputs &= intInputs;
    inputs &= 0b00011111;

    read_1_byte_MCP23008(INTCAP);

    return inputs;
}

void write_1_bit_MCP23008(u_int8_t registerMCP23008, uint8_t bitPosition, bool value) {
    uint8_t output = value << bitPosition;
    uint8_t mask = ~(1 << bitPosition);

    uint8_t portRegister = read_1_byte_MCP23008(registerMCP23008);

    Wire.beginTransmission(ADDR_MCP23008);
    Wire.write(registerMCP23008);
    if (value)
        Wire.write(output | portRegister);
    else
        Wire.write(output | portRegister & mask);
    Wire.endTransmission();
}

void write_1_byte_MCP23008(u_int8_t registerMCP23008, uint8_t byte) {
    Wire.beginTransmission(ADDR_MCP23008);
    Wire.write(registerMCP23008);
    Wire.write(byte);
    Wire.endTransmission();
}

uint8_t read_1_byte_MCP23008(uint8_t registerMCP23008) {
    Wire.beginTransmission(ADDR_MCP23008);
    Wire.write(registerMCP23008); // PORT register
    Wire.endTransmission();

    Wire.requestFrom(ADDR_MCP23008, 1, 1);

    return Wire.read();
}
