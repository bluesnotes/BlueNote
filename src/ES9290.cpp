#include "ES9290.h"

bool init_ES9290(void) {
    uint8_t sysReg;

    write_1_byte_ES9290(139, 0);
    write_1_byte_ES9290(137, 0);

    write_1_byte_ES9290(0, 0x0B);

    write_1_byte_ES9290(39, 0xFF);
    write_1_byte_ES9290(40, 0xFF);
    write_1_byte_ES9290(41, 0b00001111);

    return 1;
}

void volume_ES9290_line(u_int8_t volume) {
    write_1_byte_ES9290(124, volume);
}

void volume_ES9290_send(u_int8_t volume) {
    write_1_byte_ES9290(123, volume);
}

bool PGA_ES9290_instrument(u_int8_t gain) {
    if (gain > 10)
        gain = 10;
    write_1_byte_ES9290(82, gain);
    return 0;
}

bool PGA_ES9290_return(u_int8_t gain) {
    if (gain < 10) {
        write_1_byte_ES9290(82, gain << 4);
        return 1;
    } else
        return 0;
}

void return_in_impedance_line(bool onOff) {
    write_1_bit_ES9290(40, 0, onOff);
}

void instrument_in_impedance_line(bool onOff) {
    write_1_bit_ES9290(40, 4, onOff);
}

void return_in_pad_line(bool onOff) {
    write_1_bit_ES9290(39, 4, onOff);
}

void instrument_in_pad_line(bool onOff) {
    write_1_bit_ES9290(39, 0, onOff);
}

void write_1_byte_ES9290(u_int8_t registerES9290, uint8_t byte) {
    Wire.beginTransmission(ADDR_ES9290);
    Wire.write(registerES9290);
    Wire.write(byte);
    Wire.endTransmission();
}

void write_1_bit_ES9290(u_int8_t registerES9290, uint8_t bitPosition, bool value) {
    uint8_t output = value << bitPosition;
    uint8_t mask = ~(1 << bitPosition);

    uint8_t portRegister = read_1_byte_ES9290(registerES9290);

    Wire.beginTransmission(ADDR_ES9290);
    Wire.write(registerES9290);
    if (value)
        Wire.write(output | portRegister);
    else
        Wire.write(output | portRegister & mask);
    Wire.endTransmission();
}

uint8_t read_1_byte_ES9290(uint8_t registerES9290) {

    Wire.beginTransmission(ADDR_ES9290);
    Wire.write(registerES9290); // PORT register
    Wire.endTransmission();

    Wire.requestFrom(ADDR_ES9290, 1);
    return Wire.read();
}