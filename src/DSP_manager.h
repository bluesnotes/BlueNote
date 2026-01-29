#ifndef DSP_MANAGER_H
#define DSP_MANAGER_H

#define FREQUENCY_SAMPLING_DSP 48000

// #include "basic48k_IC_1.h"       // .h import default_download_IC_1() and DEVICE_ARCHITECTURE_IC_1
#include "MiDSPAmp48k_IC_1_PARAM.h" // PARAM.h used to access sigmastudio elements
#include "effects.h"
#include "main.h"
#include "pin.h"
#include "sigmadspSPI.h"
#include <Arduino.h>
#include <math.h>

// each user filter definition will be stored in this structure
typedef struct {                            // basic structure requires 16 bytes per user defined filter
    enum propertyValueFilterType ftype : 8; // this is a binary number based on "enum filterTypes" above
    char bypass : 8;                        // 0 : normal  , 1 : not used/bypassed
    char invert : 8;                        // 1 : invert phase by applying negative gain
    char locked : 8;                        // 1 to indicate that the filter should not be changed
    float freq;                             // corner frequency of the filter
    float Q;                                // quality factor of the filter (if relevant)
    float gain;                             // boost gain for this filter (may not be used)
} dspFilter_t;
//_Static_assert(sizeof(dspFilter_t)==16,"dspFilter_t expected to be 16 bytes");

// basic structure for holding the biquad coefficient computed for a given sampling rate
typedef struct {
    float b0; // xn
    float b1; // xn-1
    float b2; // xn-2
    float a1; // yn-1
    float a2; // yn-2
} dspBiquadCoefs_t;

// same structure but as 8.24 integer, compatible with sigmadsp > ADAU1452 (not 1701)
typedef struct {
    long b0;
    long b1;
    long b2;
    long a1;
    long a2;
} dspBiquadCoefs824_t;

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
    void setValueEffect(Effects *effect);
};

// functions
float dB2gain(float db);
void dspFilter(bool bypass, long type, float freq, float Q, float gain, float *p);

#endif