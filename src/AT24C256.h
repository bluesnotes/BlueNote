#ifndef Eeprom_at24c256_h
#define Eeprom_at24c256_h

#include "Arduino.h"
#include "Wire.h"

class AT24C256 {
  public:
    void init_AT24C256(int address);
    void write(unsigned int writeAddress, byte *data, byte len);
    void read(unsigned int readAdress, byte *buffer, byte len);

  private:
    int _address;
};

#endif