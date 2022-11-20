#ifndef PRESET_H
#define PRESET_H

#include "effects.h"
#include "pin.h"
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

using namespace std;

class Preset {
  private:
    int identify;
    String presetName;

    vector<Effects *> effects;

    void drawCenterStr(const String &buf, int x, int y, Adafruit_ILI9341 ***d);
    void drawPreset(int index, String &preset_name, Adafruit_ILI9341 **d);
    void drawEffect(int enumNameStr, Adafruit_ILI9341 **d);
    void drawCursor(float value, int enumName, int enumUnit,
                    int min, int max, int center_x, int center_y, Adafruit_ILI9341 **d);

  public:
    Preset(int id, char *prtName);

    // Getters
    int getID();
    String getPresetName();
    float getValueEffectPreset(unsigned char page, unsigned char parameter);

    // Setters
    void setPreseName(String s);
    void setValueEffectPreset(unsigned char page, unsigned char parameter, float value);

    void displayMenuPreset(unsigned char page, unsigned char parameter, Adafruit_ILI9341 *d);
};

#endif