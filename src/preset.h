#ifndef PRESET_H
#define PRESET_H

#include "Display_Preset.h"
#include "effects.h"
#include "pin.h"

#include <Adafruit_ILI9341.h>

using namespace std;

class Preset {
  protected:
    int identify;
    String presetName;

    vector<Effects *>
        effects;

  public:
    Preset(int id, char *prtName);

    // Getters
    int getID();
    String getPresetName();
    float getValueEffectPreset(unsigned char page, unsigned char parameter);
    float getIncFactor(unsigned char page, unsigned char parameter);

    // Setters
    void setPreseName(String s);
    void setValueEffectPreset(unsigned char page, unsigned char parameter, float value);

    int getLenghtEffect(unsigned char page);

    void displayMenuPreset(unsigned char page, unsigned char parameter, Adafruit_ILI9341 *d);
};

#endif