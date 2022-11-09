/*
  ESP32     display
  3v3         VCC
  GND         GND
  5           Display_CS
  25          Display_RESET
  2           Display_DC
  23          MOSI
  18          SCK
  3v3         LED
  19          MISO

  ESP32         Encoder
  32            select button 1
  GND           select button 2
  27            encoder direction 1
  33            encoder direction 2
  GND           encoder dir ground

*/

// required libraries

#include <DallasTemperature.h>
#include <OneWire.h>

#include "MCP23008.h"
#include "menu.h"
#include "pin.h"

volatile bool flagSecond = false;
volatile bool flagInterruptMCP23008 = false;

volatile char secondCounter = 0;

unsigned char MCP23008Inputs = 0;

int MenuOption = 0;

// must have variables for each menu item
// best to have these global so you can use them in processing functions
int MenuOption1 = 0, MenuOption2 = 0, MenuOption3 = 0, MenuOption4 = 0;

int OptionOption1 = 0, OptionOption2 = 0, OptionOption3 = 0, OptionOption4 = 0, OptionOption5 = 0;
int OptionOption6 = 0, OptionOption7 = 0, OptionOption8 = 0, OptionOption9 = 0;

int BlueatoothOption1 = 0;

int WirelessOption1 = 0, WirelessOption2 = 0, WirelessOption3 = 0;

// variables to store some of the options, you will probably want a var for each
// note the menu code ONLY supports floats
// if you want to edit an int in the menu, still pass in a float and set decimal readout to 0
// the recast the float to an int upon menu comletion processing
float pad = 1, lineLvl = 0, linePos = 0;

// encoder stuff
long Position = 0, oldPosition = 0;

// create some selectable menu sub-items, these are lists inside a menu item

const char *OffOnItems[] = {"Off", "On"};
const char *OutLinePlaceItems[] = {"Direct", "P. Pre.", "P. Comp.", "P. Eq."};

const char *DataRateItems[] = {"300 baud", "1.2 kbd", "2.4 kbd", "4.8 kbd", "9.6 kbd", "19.2 kbd", "56 kbd"};

float temperature = 0;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// real code starts here
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

OneWire oneWire(ONE_WIRE_PIN);
DallasTemperature sensors(&oneWire);

// you know the drill
Adafruit_ILI9341 Display = Adafruit_ILI9341(Display_CS, Display_DC, Display_RST);

// required, you must create either an Item menu (no inline editing) or an EditMenu (allows inline editing)
// ClassName YourMenuName(&DisplayObject, True=Touch input, False(Default)=mechanical input);
ItemMenu MainMenu(&Display);

// since we're showing both menu types, create an object for each where the item menu is the main and calls edit menus
// you can have an item menu call other item menus an edit menu can call an edit menu but in a round about way--not recommended
// ClassName YourMenuName(&DisplayObject, True=Touch input, False(Default)=mechanical input);
EditMenu OptionMenu(&Display);
EditMenu BluetoothMenu(&Display);
EditMenu WirelessMenu(&Display);
EditMenu AboutMenu(&Display);

ESP32Encoder encoder;

hw_timer_t *timer = NULL;

TaskHandle_t Task0, Task1;

portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;

void drawCentreString(const String &buf, int x, int y) {
    int16_t x1, y1;
    uint16_t w, h;
    Display.getTextBounds(buf, x, y, &x1, &y1, &w, &h); // calc width of new string
    Display.setCursor(x - w / 2, y);
    Display.print(buf);
}

void drawPreset(int index, const String &preset_name) {
    Display.fillRect(0, 0, 320, 50, ILI9341_LIGHTGREY);
    Display.fillRoundRect(7, 7, 63, 40, 10, ILI9341_BLUE);

    Display.setCursor(10, 33);
    Display.setTextColor(ILI9341_WHITE);
    Display.setFont(&FreeSans18pt7b);
    Display.print(index);

    Display.setCursor(90, 38);
    Display.setTextColor(ILI9341_BLACK);
    Display.setFont(&FreeSans18pt7b);
    Display.print(preset_name);
}

void drawEffect(const String &effect) {
    Display.fillRect(0, 50, 320, 30, ILI9341_DARKGREY);
    // Display.setCursor(65, 72);
    Display.setTextColor(ILI9341_WHITE);
    // Display.setTextSize(2);
    Display.setFont(&FreeSans12pt7b);
    drawCentreString(effect, 160, 72);
}

void drawCursor(int value, const String &parameter_name, const String &parameter_unit, int min, int max, int center_x, int center_y) {

    int needle_x = 0;
    int needle_y = 0;
    float angle_needle = 0;
    int radius = 29;
    int percent = 0;

    percent = (value / (max - min)) * 100;

    Display.drawCircle(center_x, center_y, 30, ILI9341_LIGHTGREY);
    Display.drawCircle(center_x, center_y, 31, ILI9341_LIGHTGREY);

    angle_needle = (((percent)*0.01745331 * 2.9) - 4.19);
    needle_x = (center_x + ((radius)*cos(angle_needle)));
    needle_y = (center_y + ((radius)*sin(angle_needle)));
    Display.drawLine(center_x, center_y, needle_x, needle_y, ILI9341_DARKGREY);

    String str = String(value + parameter_unit);

    Display.setTextColor(ILI9341_WHITE);
    Display.setFont(&FreeSans9pt7b);
    drawCentreString(parameter_name, center_x, center_y + 60);

    Display.setTextColor(ILI9341_WHITE);
    Display.setFont(&FreeSansBold9pt7b);
    drawCentreString(str, center_x, center_y + 80);
}

void displayMainScreen() {
    // this is just a processor for when you exit the top level menu

    drawPreset(255, "Rock & roll");

    drawEffect("Compressor");

    int value = 100;
    int y_gauge = 120;

    value = 0;

    drawCursor(value, "threshold", "dB", -100, 0, 54, y_gauge);

    drawCursor(value, "ratio", "", -100, 0, 152, y_gauge);

    drawCursor(value, "make", "dB", -100, 0, 250, y_gauge);

    Display.fillRect(0, 230, 320, 10, ILI9341_RED);
}

void ProcessOptionMenu() {

    // the entire menu processing are basically 3 calls
    // YourMenu.MoveUp();
    // YourMenu.MoveDown();
    // EditMenuOption = YourMenu.selectRow();

    // set an inital flag that will be used to store what menu item the user exited on
    int EditMenuOption = 1;

    // blank out the screen
    Display.fillScreen(MENU_BACKGROUND);

    // draw the main menu
    OptionMenu.draw();

    // run the processing loop until user move selector to title bar (which becomes exit)
    // and selectes it
    while (EditMenuOption != 0) {

        // standard encoder read
        Position = encoder.getCount();

        // attempt to debouce these darn things...
        if ((Position - oldPosition) > 0) {
            delay(DEBOUNCE_FAST);
            while (oldPosition != Position) {
                oldPosition = Position;
                Position = encoder.getCount();
            }
            // once encoder calms down and is done cycling, move selector up
            // since encoder reads are increasing
            // any menu wrapping is handled in the library

            // the EditMenu object type is special cased
            // 1. if a row was NOT selected, MoveUp / MoveDown will cycle throuh menu items
            // 2. if a row IS selected, MoveUp / MoveDown will cycle throuh the range of values withing the item

            OptionMenu.MoveUp();
        }

        if ((Position - oldPosition) < 0) {
            delay(DEBOUNCE_FAST);
            while (oldPosition != Position) {
                oldPosition = Position;
                Position = encoder.getCount();
            }
            // once encoder calms down and is done cycling, move selector up
            // since encoder reads are decreasing
            // any menu wrapping is handled in the library

            // the EditMenu object type is special cased
            // 1. if a row was NOT selected, MoveUp / MoveDown will cycle throuh menu items
            // 2. if a row IS selected, MoveUp / MoveDown will cycle throuh the range of values withing the item
            OptionMenu.MoveDown();
        }

        if (MCP23008Inputs == enterButton) {
            MCP23008Inputs = 0;
            // use the selectRow to
            // 1. select a row for editing
            // a. when a row is selected, moveup, movedown will then scroll through the editable values (values or a list)
            // 2. unselect a row when editing is done
            // 3. when selector is on the title bar annd selecRow is called a 0 is returned

            EditMenuOption = OptionMenu.selectRow();

            // this next section is purely optional and shows how data change can be used
            // the EditMenu object type is special cased where if you select a menu item
            // the library consideres that a desire to start editing the item
            // the menu bar color changes and any MoveUp / MoveDown will then be directed
            // to editing the item value itself
            // once user Selects the selected row, the library will consider editign done
            // and restore menu selection with MoveUp / MoveDown
            // watch the YouTube video for a demo
            // to modify other values
            if (EditMenuOption == OptionOption5) { // budget item
                if (OptionMenu.value[OptionOption5] == 0) {
                    OptionMenu.disable(OptionOption4);
                    OptionMenu.setItemText(OptionOption4, "Tune (Alarm OFF)");
                    OptionMenu.drawRow(OptionOption4);
                } else {
                    OptionMenu.enable(OptionOption4);
                    OptionMenu.setItemText(OptionOption4, "Tune");
                    OptionMenu.drawRow(OptionOption4);
                }
            }
        }
    }

    // user must have pressed the encorder select button while on the title bar (which returns 0)
    // hence exiting the loop
    // now you can process / store / display the menu selections
    // remember this is from the EditMenu and has associated value property with each menu item
    Serial.println("Option Menu Selections ");
    Serial.println("______________________________");
    Serial.print("Color Adj ");
    Serial.println(OptionMenu.value[OptionOption1]);
    Serial.print("Temp2 Adj ");
    Serial.println(OptionMenu.value[OptionOption2]);
    Serial.print("Alarm ");
    Serial.println(OffOnItems[(int)OptionMenu.value[OptionOption5]]);
    Serial.print("Refresh ");
    Serial.println(OptionMenu.value[OptionOption7]);

    // an example of how to set other menu values based on selection here
    // remember all menu values passed in or returned are floats
    // so recast to int if you need to
}

void ProcessBluetoothMenu() {

    // the entire menu processing are basically 3 calls
    // YourMenu.MoveUp();
    // YourMenu.MoveDown();
    // EditMenuOption = YourMenu.selectRow();

    // set an inital flag that will be used to store what menu item the user exited on
    int EditMenuOption = 1;

    // blank out the screen
    Display.fillScreen(MENU_BACKGROUND);

    // draw the main menu
    BluetoothMenu.draw();

    // run the processing loop until user move selector to title bar (which becomes exit)
    // and selectes it
    while (EditMenuOption != 0) {

        delay(50);
        Position = encoder.getCount();
        if ((Position - oldPosition) > 0) {
            delay(DEBOUNCE);
            while (oldPosition != Position) {
                oldPosition = Position;
                Position = encoder.getCount();
            }
            BluetoothMenu.MoveUp();
        }

        if ((Position - oldPosition) < 0) {
            delay(DEBOUNCE);
            while (oldPosition != Position) {
                oldPosition = Position;
                Position = encoder.getCount();
            }
            BluetoothMenu.MoveDown();
        }

        if (MCP23008Inputs == enterButton) {
            MCP23008Inputs = 0;

            EditMenuOption = BluetoothMenu.selectRow();
        }
    }
}

void ProcessWirelessMenu() {

    int EditMenuOption = 1;

    Display.fillScreen(MENU_BACKGROUND);

    WirelessMenu.draw();

    while (EditMenuOption != 0) {
        delay(50);
        Position = encoder.getCount();
        if ((Position - oldPosition) > 0) {
            oldPosition = Position;
            WirelessMenu.MoveUp();
        }

        if ((Position - oldPosition) < 0) {
            oldPosition = Position;
            WirelessMenu.MoveDown();
        }

        if (MCP23008Inputs == enterButton) {
            MCP23008Inputs = 0;

            EditMenuOption = WirelessMenu.selectRow();
        }
    }
}

void DisplayAboutScreen() {
    float displayTemp = -1024;

    Display.fillScreen(MENU_BACKGROUND);
    Display.fillRect(0, 0, 320, 40, TITLE_BACK);

    Display.setTextColor(MENU_HIGHLIGHTTEXT);
    Display.setFont(&FONT_TITLE);
    drawCentreString("Blue Note Amp", 160, 30);

    int EditMenuOption = 1;
    while (EditMenuOption != 0) {
        if (displayTemp != temperature) {
            displayTemp = temperature;
            Display.fillRect(0, 40, 320, 80, MENU_BACKGROUND);
            Display.setCursor(0, 68);
            Display.setTextColor(MENU_TEXT_BCK);
            Display.setFont(&FONT_SMALL);
            Display.print("Version : ");
            Display.println("Alpha");
            Display.print("Temperature : ");
            Display.print(displayTemp);
            Display.println(" degC");
            Display.print("Fan speed : ");
            Display.println("0 RPM");
        }
        if (MCP23008Inputs == enterButton) {
            MCP23008Inputs = 0;

            EditMenuOption = AboutMenu.selectRow();
        }
    }
}

// function to process main menu iteraction ideally this implementation makes it easy to launch your menu from anywhere in th
void ProcessMainMenu() {

    // set an inital flag that will be used to store what menu item the user exited on
    int MainMenuOption = 1;

    // blank out the screen
    Display.fillScreen(MENU_BACKGROUND);

    // draw the main menu
    MainMenu.draw();

    // run the processing loop until user move selector to title bar (which becomes exit, i.e. 0 return val)
    // and selectes it
    // note menu code can return - 1 for errors so run unitl non zero

    while (MainMenuOption != 0) {

        // standard encoder read
        Position = encoder.getCount();

        // attempt to debouce these darn things...
        if ((Position - oldPosition) > 0) {
            delay(DEBOUNCE);
            while (oldPosition != Position) {
                oldPosition = Position;
                Position = encoder.getCount();
            }

            // once encoder calms down and is done cycling, move selector up
            // since encoder reads are increasing
            // any menu wrapping is handled in the library
            MainMenu.MoveUp();
        }
        // attempt to debouce these darn things...
        if ((Position - oldPosition) < 0) {
            delay(DEBOUNCE);
            while (oldPosition != Position) {
                oldPosition = Position;
                Position = encoder.getCount();
            }
            // once encoder calms down and is done cycling, move selector up
            // since encoder reads are decreasing
            // any menu wrapping is handled in the library
            MainMenu.MoveDown();
        }

        // but wait...the user pressed the button on the encoder
        if (MCP23008Inputs == enterButton) {
            MCP23008Inputs = 0;
            // get the row the selector is on
            MainMenuOption = MainMenu.selectRow();

            // here is where you process accordingly
            // remember on pressing button on title bar 0 is returned and will exit the loop

            if (MainMenuOption == MenuOption1) {
                // item 1 was the Option menu
                ProcessOptionMenu();
                // when done processing that menu, return here
                // clear display and redraw this main menu
                Display.fillScreen(MENU_BACKGROUND);
                MainMenu.draw();
            }
            if (MainMenuOption == MenuOption2) {
                ProcessBluetoothMenu();
                Display.fillScreen(MENU_BACKGROUND);
                MainMenu.draw();
            }
            if (MainMenuOption == MenuOption3) {
                ProcessWirelessMenu();
                Display.fillScreen(MENU_BACKGROUND);
                MainMenu.draw();
            }

            if (MainMenuOption == MenuOption4) {
                DisplayAboutScreen();
                Display.fillScreen(MENU_BACKGROUND);
                MainMenu.draw();
            }
        }
    }

    // at this point MenuOption better be 0...
}

// menu to handle processing for a sub-menu
// since this menu will be a menu that allows edits (EditMenu object type)
// process is exactly the same as an ItemMenu
// meaning you simply use the same MoveUp, MoveDown and the library will know if you are
// wanting to move the selector or cycle through a range

void setupMenu() {

    MainMenu.init(MENU_TEXT, MENU_BACKGROUND, MENU_HIGHLIGHTTEXT, MENU_HIGHLIGHT, 64, 3, "Main Menu", FONT_TITLE, FONT_TITLE);

    MenuOption1 = MainMenu.addNI("Options");
    MenuOption2 = MainMenu.addNI("Bluetooth");
    MenuOption3 = MainMenu.addNI("Wireless");
    MenuOption4 = MainMenu.addNI("About");

    Serial.print("Enable State for MainMenu, MenuOption3: ");
    Serial.println(MainMenu.getEnableState(MenuOption3));

    MainMenu.setTitleColors(TITLE_TEXT, TITLE_BACK);
    MainMenu.setTitleBarSize(0, 0, 320, 40);
    MainMenu.setTitleTextMargins(60, 30);
    MainMenu.setIconMargins(0, 0);
    MainMenu.setMenuBarMargins(15, 310, 15, 4);
    MainMenu.setItemColors(MENU_DISABLE, MENU_HIGHBORDER);
    MainMenu.setItemTextMargins(45, 45, 5);

    OptionMenu.init(MENU_TEXT, MENU_BACKGROUND, MENU_HIGHLIGHTTEXT, MENU_HIGHLIGHT, MENU_SELECTTEXT, MENU_SELECT,
                    DATA_COLUMN, ROW_HEIGHT, ROWS, "Option Menu", FONT_ITEM, FONT_TITLE);

    OptionOption1 = OptionMenu.addNI("Pad -15dB : ", pad, 0, sizeof(OffOnItems) / sizeof(OffOnItems[0]), 1, 0, OffOnItems);
    OptionOption2 = OptionMenu.addNI("Level line out :", lineLvl, -40.0, 0.0, .5, 2, NULL);
    OptionOption3 = OptionMenu.addNI("Line out :", linePos, 0, sizeof(OutLinePlaceItems) / sizeof(OutLinePlaceItems[0]), 1, 0, OutLinePlaceItems);

    OptionMenu.SetItemValue(OptionOption1, 0);
    OptionMenu.SetItemValue(OptionOption3, 0); // the 2nd element in the ReadoutItems array

    OptionMenu.setTitleColors(TITLE_TEXT, TITLE_BACK);
    OptionMenu.setTitleBarSize(0, 0, 320, 40);
    OptionMenu.setTitleTextMargins(60, 30);
    OptionMenu.setItemTextMargins(12, 25, 10);
    OptionMenu.setItemColors(MENU_DISABLE, MENU_HIGHBORDER, MENU_SELECTBORDER);

    BluetoothMenu.init(MENU_TEXT, MENU_BACKGROUND, MENU_HIGHLIGHTTEXT, MENU_HIGHLIGHT, MENU_SELECTTEXT, MENU_SELECT,
                       170, 30, 6, "Color Menu", FONT_ITEM, FONT_TITLE);

    BlueatoothOption1 = BluetoothMenu.addNI("Enable", 0, 0, 1, 1, 0, OffOnItems);

    // all these are optional, but you will most likely need to set the margins, the library will not look at text height and
    // row height and attempt to center
    BluetoothMenu.setTitleTextMargins(50, 30);
    BluetoothMenu.setItemTextMargins(16, 15, 5);
    BluetoothMenu.setMenuBarMargins(10, 305, 4, 2);

    // optional but showing how you can have several small items and not large pretty icons
    WirelessMenu.init(MENU_TEXT, MENU_BACKGROUND, ILI9341_WHITE, ILI9341_BLUE, MENU_SELECTTEXT, MENU_SELECT,
                      DATA_COLUMN, 20, 9, "Wireless Menu", FONT_SMALL, FONT_ITEM);
    WirelessOption1 = WirelessMenu.addNI("Enable", 0, 0, 1, 1, 0, OffOnItems);
    WirelessOption2 = WirelessMenu.addNI("Network1", 0, 0, 255, 1, 0);
    WirelessOption3 = WirelessMenu.addNI("Network2", 2, 0, sizeof(DataRateItems) / sizeof(DataRateItems[0]), 1, 0, DataRateItems);

    WirelessMenu.setTitleTextMargins(50, 30);
    WirelessMenu.setItemTextMargins(16, 15, 5);
    WirelessMenu.setMenuBarMargins(10, 305, 4, 2);

    // I'm so not a fan on my API for setting select border color... this arguement should have been in the menubar thingy...
    // code is implemented in probably millions of projects around the world so no sense breaking them :)

    WirelessMenu.setItemColors(MENU_DISABLE, MENU_HIGHBORDER, MENU_SELECTBORDER);

    WirelessMenu.setTitleColors(TITLE_TEXT, TITLE_BACK);

    // optional but you can set the speed in which press and hold the up / down arrows increments the values
    // default is 50ms and while snappy, can be hard to stop on the desired value
    WirelessMenu.setIncrementDelay(150);
}

void interruptsSys(void *parameter) {
    while (1) {
        if (flagSecond) {
            flagSecond = false;
            Serial.print(uxTaskGetStackHighWaterMark(NULL));
            sensors.requestTemperatures();
            temperature = sensors.getTempCByIndex(0);
            if (temperature < 40)
                ledcWrite(PWM_FAN_PIN, 0);
            else if (temperature >= 40 && temperature < 50)
                ledcWrite(PWM_FAN_PIN, 64);
            else if (temperature >= 50 && temperature < 60)
                ledcWrite(PWM_FAN_PIN, 128);
            else if (temperature >= 60 && temperature < 70)
                ledcWrite(PWM_FAN_PIN, 192);
            else
                ledcWrite(PWM_FAN_PIN, 255);
        }
        if (flagInterruptMCP23008) {
            flagInterruptMCP23008 = false;
            MCP23008Inputs = read_MCP23008();
        }
        vTaskDelay(50);
    }
}

void IRAM_ATTR timer1Interrupt() {
    portENTER_CRITICAL_ISR(&mux);
    if (secondCounter > 4) {
        secondCounter = 0;
        flagSecond = true;
    }
    secondCounter++;
    portEXIT_CRITICAL_ISR(&mux);
}

void IRAM_ATTR MCP23008Interrupt() {
    flagInterruptMCP23008 = true;
}

void setup() {

    Serial.begin(115200);

    timer = timerBegin(1, 0xC350, true); // timer 1, 80Mhz / 50k = 1.6kHz
    timerAttachInterrupt(timer, &timer1Interrupt, true);
    timerAlarmWrite(timer, 1600, true);
    timerAlarmEnable(timer);

    // disableCore0WDT();

    ESP32Encoder::useInternalWeakPullResistors = NONE;
    encoder.attachHalfQuad(EN1_PIN, EN2_PIN);
    encoder.clearCount();

    sensors.begin();
    sensors.requestTemperatures();
    temperature = sensors.getTempCByIndex(0);

    ledcSetup(0, 30000, 8);
    ledcAttachPin(PWM_FAN_PIN, 0);

    pinMode(TACH_FAN_PIN, INPUT);

    // fire up the display
    Display.begin();
    Display.setRotation(1);

    setupMenu();

    // ProcessMainMenu();

    init_MCP23008();
    pinMode(INT_MCP23008_PIN, INPUT);
    attachInterrupt(INT_MCP23008_PIN, MCP23008Interrupt, RISING);

    // menu code done, now proceed to your code
    Display.fillScreen(MENU_BACKGROUND);
    displayMainScreen();
    xTaskCreatePinnedToCore(interruptsSys, "Task1", 30000, NULL, 1, &Task1, 1);
}

void loop() {
    if (MCP23008Inputs == enterButton) {
        MCP23008Inputs = 0;
        // debounce the selector button
        ProcessMainMenu();
        Display.fillScreen(MENU_BACKGROUND);
    }
    vTaskDelay(50);
}
