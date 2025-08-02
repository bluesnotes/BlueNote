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
    //~Menu();

    Adafruit_ILI9341 display = Adafruit_ILI9341(Display_CS, Display_DC, Display_RST);

    void setupMenu();

    void openPresetMenu();

    void processMainMenu();
};

#endif