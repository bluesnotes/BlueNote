#include "AT24C256.h"

void AT24C256::init_AT24C256(int address) {
    Wire.begin();
    _address = address;
}

void AT24C256::write(unsigned int writeAddress, byte *data, byte len) {

    Wire.beginTransmission(_address);
    Wire.write((int)(writeAddress >> 8));
    Wire.write((int)(writeAddress & 0xFF));
    byte c;
    for (c = 0; c < len; c++)
        Wire.write(data[c]);
    Wire.endTransmission();
}

void AT24C256::read(unsigned int readAdress, byte *buffer, byte len) {
    Wire.beginTransmission(_address);
    Wire.write((int)(readAdress >> 8));
    Wire.write((int)(readAdress & 0xFF));
    Wire.endTransmission();
    Wire.requestFrom(_address, len);
    int c = 0;
    for (c = 0; c < len; c++)
        if (Wire.available())
            buffer[c] = Wire.read();
}