#include "DSP_manager.h"
#include "MiDSPAmp48k_IC_1.h"

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
    switch (effect->name) {
    case pre: {
        // gain
        float gain = -dB2gain(effect->properties[0]->value);
        DSP.writeValueFloat(MOD_PRE_GAIN_GAIN_ADDR, gain);

        Serial.println(effect->properties[0]->value);
        Serial.println(gain);

        // clipUp
        float tau = effect->properties[1]->value;
        DSP.writeValueFloat(MOD_PRE_CLIPPER_TAU1_ADDR, tau);
        tau = 1 - tau;
        DSP.writeValueFloat(MOD_PRE_CLIPPER_ONEMTAU1_ADDR, tau);
        tau = 1 / tau;
        DSP.writeValueFloat(MOD_PRE_CLIPPER_INV_ONEMTAU1_ADDR, tau);

        // clipDown
        tau = effect->properties[2]->value;
        DSP.writeValueFloat(MOD_PRE_CLIPPER_TAU1_ADDR, tau);
        tau = 1 - tau;
        DSP.writeValueFloat(MOD_PRE_CLIPPER_ONEMTAU1_ADDR, tau);
        tau = 1 / tau;
        DSP.writeValueFloat(MOD_PRE_CLIPPER_INV_ONEMTAU1_ADDR, tau);

        // bypass
        DSP.writeValueFloat(MOD_PRE_CLIPPER_BYPASS_INDEX_ADDR, 1 - (effect->properties[3]->value));

    } break;

    case oct: {
        // blend
        DSP.writeValueFloat(MOD_OCTAVER_BLEND_DCVALUE_ADDR, dB2gain(effect->properties[0]->value));

        // bypass
        DSP.writeValueFloat(MOD_OCTAVER_BYPASS_INDEX_ADDR, 1 - effect->properties[1]->value);

    } break;

    case env_filter: {
        // strength
        float strength = dB2gain(20 + effect->properties[0]->value);
        DSP.writeValueFloat(MOD_ENVELOPEFILTER_POSTGAIN_SIGNALENVELOPE_GAIN_ADDR, strength);

        // decay
        float decay = 2 * sin((PI * effect->properties[1]->value) / FREQUENCY_SAMPLING_DSP);
        DSP.writeValueFloat(MOD_ENVELOPEFILTER_FREQMIN_DCVALUE_ADDR, decay);

        // Q
        float q = 1 / effect->properties[2]->value;
        DSP.writeValueFloat(MOD_ENVELOPEFILTER_Q_DCVALUE_ADDR, q);

        // dry filter
        float coeffBiquads[6];
        dspFilter(0, low_pass, effect->properties[3]->value,
                  0.7, 0, &coeffBiquads[0]);
        DSP.writeBiquads(MOD_ENVELOPFILTER_DRYFILTER_STAGE0_B2_ADDR, 1, &coeffBiquads[0]);

        // blend
        DSP.writeValueFloat(MOD_ENVELOPEFILTER_BLEND_DCVALUE_ADDR, dB2gain(effect->properties[4]->value));

        // bypass
        DSP.writeValueFloat(MOD_ENVELOPFILTER_BYPASS_INDEX_ADDR, 1 - effect->properties[1]->value);

    } break;

    case fuzz_od: {

    } break;

    case eq + 0x100:
    case eq + 0x200:
    case eq + 0x300:
    case eq + 0x400: {
        int numberEq = effect->name >> 8;
        bool bypass = !(effect->properties[4]->value);
        float coeffBiquads[6];

        Serial.print("Eq:");
        Serial.println(numberEq);
        Serial.print("Bypass:");
        Serial.println(bypass);
        Serial.print("type:");
        Serial.println(effect->properties[3]->value);
        Serial.print("freq:");
        Serial.println(effect->properties[1]->value);
        Serial.print("Q:");
        Serial.println(effect->properties[2]->value);
        Serial.print("gain:");
        Serial.println(effect->properties[0]->value);

        dspFilter(bypass,
                  (propertyValueFilterType)effect->properties[3]->value,
                  effect->properties[1]->value,
                  effect->properties[2]->value,
                  effect->properties[0]->value,
                  &coeffBiquads[0]);

        Serial.print("b0:");
        Serial.println(coeffBiquads[0], 6);
        Serial.print("b1:");
        Serial.println(coeffBiquads[1], 6);
        Serial.print("b2:");
        Serial.println(coeffBiquads[2], 6);
        Serial.print("a1:");
        Serial.println(coeffBiquads[3], 6);
        Serial.print("a2:");
        Serial.println(coeffBiquads[4], 6);

        switch (numberEq) {
        case 1:
            DSP.writeBiquads(MOD_GLOBAL_EQ_STAGE0_B2_ADDR, 1, &coeffBiquads[0]);
            break;
        case 2:
            DSP.writeBiquads(MOD_GLOBAL_EQ_STAGE1_B2_ADDR, 1, &coeffBiquads[0]);
            break;
        case 3:
            DSP.writeBiquads(MOD_GLOBAL_EQ_STAGE2_B2_ADDR, 1, &coeffBiquads[0]);
            break;
        case 4:
            DSP.writeBiquads(MOD_GLOBAL_EQ_STAGE3_B2_ADDR, 1, &coeffBiquads[0]);
            break;

        default:
            break;
        }
    } break;

    default:
        break;
    }
}

float dB2gain(float db) {
    db /= 20.0;
    return pow(10, db);
}

// calc the biquad coefficient for a given filter type
void dspFilter(bool bypass, long type, float freq, float Q, float gain, float *p) {
    float *b0 = &p[0];
    float *b1 = &p[1];
    float *b2 = &p[2];
    float *a1 = &p[3];
    float *a2 = &p[4];
    gain = dB2gain(gain);

    if (bypass)
        type = none;

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
            Serial.println("PeakingFilter");
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