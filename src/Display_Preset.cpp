#include "Display_Preset.h"
#include "FreeSans12pt7b.h"
#include "FreeSans18pt7b.h"
#include "FreeSans9pt7b.h"
#include "FreeSansBold12pt7b.h"
#include "FreeSansBold9pt7b.h"

void drawCenterStr(const String &buf, int x, int y, Adafruit_ILI9341 ***d) {
    int16_t x1, y1;
    uint16_t w, h;
    (***d).getTextBounds(buf, 0, y, &x1, &y1, &w, &h); // calc width of new char*
    (***d).setCursor(x - w / 2, y);
    (***d).print(buf);
};

void drawPreset(int index, String &preset_name, Adafruit_ILI9341 **d) {
    (**d).fillRect(0, 0, 320, 50, ILI9341_LIGHTGREY);
    (**d).fillRoundRect(7, 7, 63, 40, 10, 0x018c);

    (**d).setCursor(10, 38);
    (**d).setTextColor(ILI9341_WHITE);
    (**d).setFont(&FreeSans18pt7b);
    (**d).print(index);

    (**d).setCursor(90, 38);
    (**d).setTextColor(ILI9341_BLACK);
    (**d).setFont(&FreeSans18pt7b);
    (**d).print(preset_name);
}

void drawEffect(int enumNameStr, Adafruit_ILI9341 **d) {

    String effect = effectNameToStr(enumNameStr);
    (**d).fillRect(0, 50, 320, 30, 0x018c);

    (**d).setCursor(65, 72);
    (**d).setTextColor(ILI9341_WHITE);
    (**d).setFont(&FreeSans12pt7b);
    //(**d).print(effect);
    drawCenterStr(effect, 160, 72, &d);
}

void drawCursor(float value, int enumName, int enumUnit,
                int min, int max, int center_x, int center_y, Adafruit_ILI9341 **d) {

    int radius = 29;
    String nameStr = propertyNameToStr(enumName);
    String unitStr = unitToStr(enumUnit);

    float percent = ((value + abs(min)) / (max - min)) * 100;

    (**d).fillRect(center_x - 40, center_y - 32, 80, 140, ILI9341_BLACK);

    (**d).drawCircle(center_x, center_y, 30, ILI9341_LIGHTGREY);
    (**d).drawCircle(center_x, center_y, 31, ILI9341_LIGHTGREY);

    for (int i = -20; i < 21; i++) {
        float angle_needle = (((percent + (i * 0.1)) * 0.01745331 * 2.9) - 4.19);
        int needle_x = (center_x + ((radius)*cos(angle_needle)));
        int needle_y = (center_y + ((radius)*sin(angle_needle)));
        (**d).drawLine(center_x, center_y, needle_x, needle_y, 0X4c94);
    }

    (**d).setTextColor(ILI9341_WHITE);
    (**d).setFont(&FreeSans9pt7b);
    drawCenterStr(nameStr, center_x, center_y + 60, &d);

    String str = String(value + unitStr);
    if (str.length() > 6) {
        str = String(value);
        (**d).setTextColor(ILI9341_WHITE);
        (**d).setFont(&FreeSansBold9pt7b);
        drawCenterStr(str, center_x, center_y + 80, &d);
        drawCenterStr(unitStr, center_x, center_y + 100, &d);
    } else {
        (**d).setTextColor(ILI9341_WHITE);
        (**d).setFont(&FreeSansBold9pt7b);
        drawCenterStr(str, center_x, center_y + 80, &d);
    }
}
