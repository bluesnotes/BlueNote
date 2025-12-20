#include "ES9033.h"

bool init_ES9033(void) {

    write_1_byte_ES9033(ADDR_ES9033W, 192, 0b00000011);
    write_1_byte_ES9033(ADDR_ES9033W, 193, 0b11000001);
    write_1_byte_ES9033(ADDR_ES9033W, 202, 0b01000000);
    delay(1);

    write_1_byte_ES9033(ADDR_ES9033RW, 51, 0b11000000);
    write_1_byte_ES9033(ADDR_ES9033RW, 2, 0b00000011);
    write_1_byte_ES9033(ADDR_ES9033RW, 4, 0b00000011);
    write_1_byte_ES9033(ADDR_ES9033RW, 0, 0b00111110);

    return 1;
}

bool volumeES9033(uint8_t volume) {
    write_1_byte_ES9033(ADDR_ES9033RW, 46, volume);
    return 1;
}

void write_1_byte_ES9033(uint8_t adress, uint8_t registerES9033, uint8_t byte) {
    Wire.beginTransmission(adress);
    Wire.write(registerES9033);
    Wire.write(byte);
    Wire.endTransmission();
}

void write_1_bit_ES9033(u_int8_t registerES9033, uint8_t bitPosition, bool value) {
    uint8_t output = value << bitPosition;
    uint8_t mask = ~(1 << bitPosition);

    uint8_t portRegister = read_1_byte_ES9033(registerES9033);

    Wire.beginTransmission(ADDR_ES9033RW);
    Wire.write(registerES9033);
    if (value)
        Wire.write(output | portRegister);
    else
        Wire.write(output | portRegister & mask);
    Wire.endTransmission();
}

uint8_t read_1_byte_ES9033(uint8_t registerES9033) {
    Wire.beginTransmission(ADDR_ES9033RW);
    Wire.write(registerES9033); // PORT register
    Wire.endTransmission();

    Wire.requestFrom(ADDR_ES9033RW, 1);
    return Wire.read();
}