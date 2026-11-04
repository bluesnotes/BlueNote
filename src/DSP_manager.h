#ifndef DSP_MANAGER_H
#define DSP_MANAGER_H

#define FREQUENCY_SAMPLING_DSP 48000

#define OFFSET_HARD_KNEE 0
#define OFFSET_SOFT_KNEE_1 -0.119846
#define OFFSET_SOFT_KNEE_2 -0.185
#define OFFSET_SOFT_KNEE_3 -0.269974

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

    float softKnee_0_119846[33] = {0.000158461325115751, 0.000473078131612718, 0.00141235041702888,
                                   0.00421649948959093, 0.012588142242434, 0.0375812508709979,
                                   0.067654, 0.098904, 0.130154, 0.161404, 0.192654, 0.223904, 0.255154,
                                   0.286404, 0.317654, 0.348904, 0.380154, 0.411404, 0.442654, 0.473904,
                                   0.505154, 0.536404, 0.567654, 0.598904, 0.630154, 0.661404, 0.692654,
                                   0.723904, 0.755154, 0.786404, 0.817654, 0.848904, 0.880154};

    float softKnee_0_185[33] = {0.000124925831258241, 0.000278384224657144, 0.000620350297111565,
                                0.00138238613053727, 0.00308050374570568, 0.00686458227385323,
                                0.015297007789778, 0.0340877912137225, 0.065, 0.09625, 0.1275, 0.15875,
                                0.19, 0.22125, 0.2525, 0.28375, 0.315, 0.34625, 0.3775, 0.40875, 0.44,
                                0.47125, 0.5025, 0.53375, 0.565, 0.59625, 0.6275, 0.65875, 0.69, 0.72125,
                                0.7525, 0.78375, 0.815};

    float softKnee_0_26974[33] = {0.00247875217666636, 0.00338805252183471, 0.00463091873353325,
                                  0.00632971542748575, 0.00865169520312063, 0.0118254652590966,
                                  0.0161634945881659, 0.0220928776650624, 0.0301973834223185,
                                  0.0412749293857976, 0.0564161395037774, 0.0771117199683167,
                                  0.10526, 0.13651, 0.16776, 0.19901, 0.23026, 0.26151, 0.29276,
                                  0.32401, 0.35526, 0.38651, 0.41776, 0.44901, 0.48026, 0.51151,
                                  0.54276, 0.57401, 0.60526, 0.63651, 0.66776, 0.69901, 0.73026};

    float hardKnee[33] = {0, 0.03125, 0.0625, 0.09375, 0.125, 0.15625, 0.1875, 0.21875, 0.25, 0.28125,
                          0.3125, 0.34375, 0.375, 0.40625, 0.4375, 0.46875, 0.5, 0.53125, 0.5625, 0.59375,
                          0.625, 0.65625, 0.6875, 0.71875, 0.75, 0.78125, 0.8125, 0.84375, 0.875, 0.90625, 0.9375, 0.96875, 1};

  public:
    DSP_manager();
    ~DSP_manager();

    void setup(void);
    // Getters

    // Setters
    void setValueEffect(Effects *effect);

    void setMPpin(unsigned char pin, bool state);
};

// functions
float ratioCalc(float ratio);
float dB2gain(float db);
void dspFilter(bool bypass, long type, float freq, float Q, float gain, float *p);

#endif