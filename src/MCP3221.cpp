/*==============================================================================================================*
    Fork of :
    @file     MCP3221.h
    @author   Nadav Matalon
    @license  MIT (c) 2016 Nadav Matalon

    MCP3221 Driver (12-BIT Single Channel ADC with I2C Interface)

    Ver. 1.0.0 - First release (16.10.16)

 *===============================================================================================================*/

#include "MCP3221.h"

unsigned int read_MCP3221(char addr, unsigned char res) {
    unsigned char rawData = 0;
    unsigned char bit = 12 - res;

    Wire.requestFrom(addr, DATA_BYTES);
    if (Wire.available() == DATA_BYTES)
        rawData = (Wire.read() << 8 - bit) | (Wire.read() >> bit);
    else
        ping(addr);
    return rawData;
}

unsigned char ping(char addr) {
    Wire.beginTransmission(addr);
    return Wire.endTransmission();
}

unsigned int cmd_potentiometer(unsigned int lastRead, char addr,
                               unsigned char bitResolution) {
    long averageData, rawData;

    rawData = read_MCP3221(addr, bitResolution);

    if ((rawData - lastRead) < 2 && (rawData - (int)lastRead) > -2) { // Return last read because no change
        averageData = lastRead;
    } else { // process 4 sample of raw data for debounce potentiometer
        unsigned long sum = rawData;

        for (char i = 1; i < NUMSAMPLES; i++)
            sum += read_MCP3221(addr, bitResolution); // // aggregate all samples

        averageData = sum / NUMSAMPLES; // calculate average
    }
    return (unsigned int)averageData;
}