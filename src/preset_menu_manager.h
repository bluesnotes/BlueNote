#ifndef PRESET_MENU_MANAGER_H
#define PRESET_MENU_MANAGER_H

#include "Adafruit_ILI9341_Menu.h"
#include "ESP32Encoder.h" // https://github.com/madhephaestus/ESP32Encoder
#include "pin.h"
#include "preset.h"

#include "FreeSans12pt7b.h"
#include "FreeSans18pt7b.h"
#include "FreeSans9pt7b.h"
#include "FreeSansBold12pt7b.h"
#include "FreeSansBold9pt7b.h"

#define ROW_HEIGHT 35
#define ROWS 5
#define DATA_COLUMN 180

#define FONT_SMALL FreeSans9pt7b      // font for menus
#define FONT_EDITTITLE FreeSans18pt7b // font for menus
#define FONT_ITEM FreeSans12pt7b      // font for menus
#define FONT_TITLE FreeSans18pt7b     // font for all headings

#define DEBOUNCE 150
#define DEBOUNCE_FAST 50

// set colors Menu
#define MENU_TEXT 0XFFFF
#define MENU_TEXT_BCK 0X4c94 // blue clear
#define MENU_BACKGROUND 0X0000
#define MENU_HIGHLIGHTTEXT 0X0000
#define MENU_HIGHLIGHT 0X4c94
#define MENU_HIGHBORDER 0X0000
#define MENU_SELECTTEXT 0XFFFF
#define MENU_SELECT 0X018C // dark blue
#define MENU_SELECTBORDER 0X0000
#define MENU_DISABLE 0XC618
#define TITLE_TEXT 0X0000
#define TITLE_BACK 0X4c94

class Menu {
  private:
    unsigned char *inputs;
    float *temp;

    ItemMenu MainMenu = ItemMenu(&this->display);

    EditMenu OptionMenu = EditMenu(&this->display);
    EditMenu BluetoothMenu = EditMenu(&this->display);
    EditMenu WirelessMenu = EditMenu(&this->display);
    EditMenu AboutMenu = EditMenu(&this->display);

    void processOptionMenu();
    void processBluetoothMenu();
    void processWirelessMenu();
    void displayAboutScreen();

    void countEncoder(bool *fastInc, long *encP, long *encOp, ESP32Encoder *encoderSelect);

    void incDecItemPreset(bool inc_dec, bool fastInc, unsigned char par);

  public:
    Menu(unsigned char *inputs, float *temp);
    ~Menu();

    Adafruit_ILI9341 display = Adafruit_ILI9341(Display_CS, Display_DC, Display_RST);

    void setupMenu();

    void openPresetMenu();

    void processMainMenu();
};

#endif