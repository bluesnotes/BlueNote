#ifndef TEMP_CONTROL_H
#define TEMP_CONTROL_H
#include "pin.h"
#include <DallasTemperature.h>
#include <OneWire.h>

class Temp_Control {
  private:
  public:
    Temp_Control();
    ~Temp_Control();

    float setup(void);
    float temperatureControl(void);
};

#endif