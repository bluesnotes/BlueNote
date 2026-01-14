#ifndef PRESET_H
#define PRESET_H

#include "DSP_manager.h"
#include "Display_Preset.h"
#include "effects.h"
#include "pin.h"

#include <Adafruit_ILI9341.h>

using namespace std;



enum presetDisplay : unsigned char {
    allDisplay = 254,
    selectPresetAllDisplay = 253,
    effectTwoArrow = 252,
    effectRightArrow = 251,
    effectLeftArrow = 250,
    effectDisplay = 249,
    oneGauge = 0,
};

class Preset {
  protected:
    unsigned char identify;

    String presetName;

    vector<Effects *>
        effects;

  public:
    Preset(unsigned char id, char *prtName);

    // Getters
    // page select effect
    // parameter select parameter
    int getID();

    String getPresetName();

    float getValueEffectPreset(unsigned char page, unsigned char parameter);

    float getIncFactor(unsigned char page, unsigned char parameter);

    unsigned int getLenghtPreset();

    int getLenghtEffect(unsigned char page);

    // Setters
    void setPreseName(String s);

    void setValueEffectPreset(unsigned char page, unsigned char parameter, float value);

    void displayMenuPreset(unsigned char page, unsigned char parameter, presetDisplay display, Adafruit_ILI9341 *d);
};

#endif