#ifndef DSP_MANAGER_H
#define DSP_MANAGER_H

// #include "basic48k_IC_1.h"       // .h import default_download_IC_1() and DEVICE_ARCHITECTURE_IC_1
#include "basic48k_IC_1_PARAM.h" // PARAM.h used to access sigmastudio elements
#include "effects.h"
#include "main.h"
#include "pin.h"
#include "sigmadspSPI.h"
#include <Arduino.h>
#include <math.h>

class DSP_manager {
  private:
    /* data */
    Effects effect;

  public:
    DSP_manager();
    ~DSP_manager();

    void setup(void);
    // Getters

    // Setters
    void setValueEffect(const Effects &effect);
};

#endif