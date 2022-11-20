#ifndef DISPLAY_PRESET_H
#define DISPLAY_PRESET_H

#include "preset.h"

#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

void drawCenterStr(const String &buf, int x, int y, Adafruit_ILI9341 ***d);

void drawPreset(int index, String &preset_name, Adafruit_ILI9341 **d);

void drawEffect(int enumNameStr, Adafruit_ILI9341 **d);

void drawCursor(float value, int enumName, int enumUnit,
                int min, int max, int center_x, int center_y, Adafruit_ILI9341 **d);

#endif