#include "DSP_manager.h"
#include "basic48k_IC_1.h"

DSP_manager::DSP_manager(/* args */) {
    long tempBiquadIndex;
}

DSP_manager::~DSP_manager() {
}

void DSP_manager::setup(void) {
    SPI.begin();
    DSP.begin(DEVICE_ARCHITECTURE_IC_1, MOD_SAFELOAD_DATA_SAFELOAD0_ADDR, CS_ADAU);
    default_download_IC_1();
    DSP.writeRegister(REG_MP13_WRITE_IC_1_ADDR, 0); /*Reset codec*/
    delay(200);
    DSP.writeRegister(REG_MP13_WRITE_IC_1_ADDR, 1);
    SPI.endTransaction();
    delay(200);
}

void DSP_manager::setValueEffect(Effects *effect) {
}

float dB2gain(float db) {
    db /= 20.0;
    return pow(10, db);
}

long dspQ8_24(float f) {
    float maxf = (1 << 7);
    if (f >= maxf)
        return 0x7fffffff;
    else if (f < (-maxf))
        return 0xffffffff;
    else {
        long mul = 1 << 24;
        f *= mul;
        return f; // will convert to integer
    }
}
// calc the biquad coefficient for a given filter type
void dspFilter(long type,
               float freq,
               float Q,
               float gain,
               float *b0,
               float *b1,
               float *b2,
               float *a1,
               float *a2) {

    if (type == none) {
        *b0 = 1.0;
        *b1 = 0.0;
        *b2 = 0.0;
        *a1 = 0.0;
        *a2 = 0.0;
        return;
    } else if (type == high_shelving_first || type == low_shelving_first) {
        float a0, w0, tw2, alpha;
        w0 = M_PI * 2.0 * freq / FREQUENCY_SAMPLING_DSP;
        tw2 = tan(w0 / 2.0);
        a0 = gain;
        *a2 = 0;
        *b2 = 0;
        switch (type) {
        case high_shelving_first: {
            float A = sqrt(gain);
            a0 = A * tw2 + 1.0;
            *a1 = -(A * tw2 - 1.0) / a0;
            *b0 = (A * tw2 + gain) / a0;
            *b1 = (A * tw2 - gain) / a0;
            break;
        }
        case low_shelving_first: {
            float A = sqrt(gain);
            a0 = tw2 + A;
            *a1 = -(tw2 - A) / a0;
            *b0 = (gain * tw2 + A) / a0;
            *b1 = (gain * tw2 - A) / a0;
            break;
        }
        }
    } else {
        float a0, w0, cw0, sw0, alpha; // tw2
        w0 = M_PI * 2.0 * freq / FREQUENCY_SAMPLING_DSP;
        cw0 = cos(w0);
        sw0 = sin(w0);
        // tw2 = tan(w0/2.0);
        if (Q != 0.0)
            alpha = sw0 / 2.0 / Q;
        else
            alpha = 1;
        a0 = (1.0 + alpha);
        *a1 = -(-2.0 * cw0) / a0;  // sign is changed to accomodate convention
        *a2 = -(1.0 - alpha) / a0; // and coeficients are normalized vs a0
        switch (type) {
        case low_pass: {
            *b1 = (1.0 - cw0) / a0 * gain;
            *b0 = *b1 / 2.0;
            *b2 = *b0;
            break;
        }
        case high_pass: {
            *b1 = -(1.0 + cw0) / a0 * gain;
            *b0 = -*b1 / 2.0;
            *b2 = *b0;
            break;
        }
        case notch: {
            *b0 = 1.0 / a0 * gain;
            *b1 = -*a1 * gain;
            *b2 = *b0;
            break;
        }
        case peaking: {
            float A = sqrt(gain);
            a0 = 1.0 + alpha / A;
            *a1 = 2.0 * cw0 / a0;
            *a2 = -(1.0 - alpha / A) / a0;
            *b0 = (1.0 + alpha * A) / a0;
            *b1 = -2.0 * cw0 / a0;
            *b2 = (1.0 - alpha * A) / a0;
            break;
        }
        case low_shelving: {
            float A = sqrt(gain);
            float sqA = sqrt(A);
            a0 = (A + 1.0) + (A - 1.0) * cw0 + 2.0 * sqA * alpha;
            *a1 = -(-2.0 * ((A - 1.0) + (A + 1.0) * cw0)) / a0;
            *a2 = -((A + 1.0) + (A - 1.0) * cw0 - 2.0 * sqA * alpha) / a0;
            *b0 = (A * ((A + 1.0) - (A - 1.0) * cw0 + 2.0 * sqA * alpha)) / a0;
            *b1 = (2.0 * A * ((A - 1.0) - (A + 1.0) * cw0)) / a0;
            *b2 = (A * ((A + 1.0) - (A - 1.0) * cw0 - 2.0 * sqA * alpha)) / a0;
            ;
            break;
        }
        case high_shelving: {
            float A = sqrt(gain);
            float sqA = sqrt(A);
            a0 = (A + 1.0) - (A - 1.0) * cw0 + 2.0 * sqA * alpha;
            *a1 = -(2.0 * ((A - 1.0) - (A + 1.0) * cw0)) / a0;
            *a2 = -((A + 1.0) - (A - 1.0) * cw0 - 2.0 * sqA * alpha) / a0;
            *b0 = (A * ((A + 1.0) + (A - 1.0) * cw0 + 2.0 * sqA * alpha)) / a0;
            *b1 = (-2.0 * A * ((A - 1.0) + (A + 1.0) * cw0)) / a0;
            *b2 = (A * ((A + 1.0) + (A - 1.0) * cw0 - 2.0 * sqA * alpha)) / a0;
            break;
        }
        } // switch
    }
}

int dsp_filter(enum propertyValueFilterType type, float freq, float Q, float gain) {
    int tmp = 0;
    dspBiquadCoefs_t coefs;

    dspFilter(type, freq, Q, gain, &coefs.b0, &coefs.b1, &coefs.b2, &coefs.a1, &coefs.a2);

    if (tempBiquadIndex < tempBiquadMax)
        tempBiquad[tempBiquadIndex++] = coefs;

    return tmp;
}

int dspFilterConvert(dspFilter_t filter) {
    if (filter.bypass)
        filter = {none, 0, 0, 0, 0, 0, 0};
    tempBiquadIndex = 0;
    int result = dsp_filter(filter.ftype, filter.freq, filter.Q, filter.gain);
    if (filter.invert) {
        tempBiquad[0].b0 = -tempBiquad[0].b0;
        tempBiquad[0].b1 = -tempBiquad[0].b1;
        tempBiquad[0].b2 = -tempBiquad[0].b2;
    }
    return result;
}