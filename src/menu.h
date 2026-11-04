#ifndef MENU_H
#define MENU_H

#include "Adafruit_ILI9341_Menu.h"

#include "ESP32Encoder.h" // https://github.com/madhephaestus/ESP32Encoder
#include "global_struct.h"
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
    INOUTVAR *processVar;

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

    uint32_t readAdcOversampled(int pin);

    void incDecItemPreset(uint32_t valueCmd, unsigned char par);

  public:
    Menu(INOUTVAR *processVar);
    //~Menu();

    Adafruit_ILI9341 display = Adafruit_ILI9341(Display_CS, Display_DC, Display_RST);

    void setupMenu();

    void openPresetMenu();

    void processMainMenu();
};

#endif