/*==============================================================================================================*
    Fork of :
    @file     MCP3221.h
    @author   Nadav Matalon
    @license  MIT (c) 2016 Nadav Matalon

    MCP3221 Driver (12-BIT Single Channel ADC with I2C Interface)

    Ver. 1.0.0 - First release (16.10.16)

 *===============================================================================================================*/

#include "MCP3221.h"

unsigned char read_MCP3221(void) {
    unsigned char rawData = 0;
    Wire.requestFrom(ADDR_MCP3221, DATA_BYTES);
    if (Wire.available() == DATA_BYTES)
        rawData = (Wire.read() << 3) | (Wire.read() >> 5);
    else
        ping();
    return rawData;
}

unsigned char ping() {
    Wire.beginTransmission(ADDR_MCP3221);
    return Wire.endTransmission();
}

unsigned char smoothVolume(char lastSmoothedData) {
    long averageData, rawData;

    rawData = read_MCP3221();

    if ((rawData - lastSmoothedData) < 3 && (rawData - lastSmoothedData) > -3) { // Return last smoothed data because no change
        averageData = lastSmoothedData;

    } else { // process 4 sample of raw data for debounce potentiometer
        unsigned long sum = rawData;

        for (char i = 1; i < NUMSAMPLES; i++)
            sum += read_MCP3221(); // // aggregate all samples

        averageData = sum / NUMSAMPLES; // calculate average
    }

    rawData = (unsigned char)((ALPHA * averageData + (MAXALPHA - ALPHA) * (unsigned long)lastSmoothedData) / MAXALPHA);
    return rawData;
}