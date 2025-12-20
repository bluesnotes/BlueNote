#ifndef TEMPERATURE_REGULATION_H
#define TEMPERATURE_REGULATION_H
#include "pin.h"
#include <DallasTemperature.h>
#include <OneWire.h>

class Temperature_Regulation {
  private:
  public:
    Temperature_Regulation();
    ~Temperature_Regulation();

    float setup(void);
    float process(void);
};

#endif