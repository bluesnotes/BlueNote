#ifndef MENU_H
#define MENU_H

#include "Adafruit_ILI9341_Menu.h"
#include "ESP32Encoder.h" // https://github.com/madhephaestus/ESP32Encoder
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

// found in \Arduino\libraries\Adafruit-GFX-Library-master
#include "FreeSans12pt7b.h"
#include "FreeSans18pt7b.h"
#include "FreeSans9pt7b.h"
#include "FreeSansBold12pt7b.h"
#include "FreeSansBold9pt7b.h"

#define ROW_HEIGHT 35
#define ROWS 5
#define DATA_COLUMN 200

// easy way to include fonts but change globally
#define FONT_SMALL FreeSans9pt7b      // font for menus
#define FONT_EDITTITLE FreeSans18pt7b // font for menus

#define FONT_ITEM FreeSans12pt7b  // font for menus
#define FONT_TITLE FreeSans18pt7b // font for all headings

#define DEBOUNCE 150
#define DEBOUNCE_FAST 50

// set colors menu
#define MENU_TEXT 0XFFFF
#define MENU_TEXT_BCK 0X335c
#define MENU_BACKGROUND 0X0000
#define MENU_HIGHLIGHTTEXT 0X0000
#define MENU_HIGHLIGHT 0X335c
#define MENU_HIGHBORDER 0X0000
#define MENU_SELECTTEXT 0XFFFF
#define MENU_SELECT 0X018C
#define MENU_SELECTBORDER 0X0000
#define MENU_DISABLE 0XC618
#define TITLE_TEXT 0X0000
#define TITLE_BACK 0X335c

class menu {
  private:
    /* data */
  public:
    menu(/* args */);
    ~menu();
};

menu::menu(/* args */) {
}

menu::~menu() {
}



#endif