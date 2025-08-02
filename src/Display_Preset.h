#ifndef DISPLAY_PRESET_H
#define DISPLAY_PRESET_H
#include "color.h"
#include "preset.h"
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void drawCenterStr(const String &buf, int x, int y, Adafruit_ILI9341 ***d);

void drawPreset(int index, bool unSelect, String &preset_name, Adafruit_ILI9341 **d);

void drawEffect(uint8_t displayIndication, int enumNameStr,
                uint8_t pageNumber, uint8_t numberOfPage, Adafruit_ILI9341 **d);

void drawCursor(float value, int enumName, int enumUnit,
                int min, int max, int log, int center_x, int center_y, Adafruit_ILI9341 **d);

#endif