#include "preset_menu_manager.h"

#define numb_preset 50

int MenuOption = 0;

// must have variables for each Menu item
// best to have these global so you can use them in processing functions
int MenuOption1 = 0, MenuOption2 = 0, MenuOption3 = 0, MenuOption4 = 0;

int OptionOption1 = 0, OptionOption2 = 0, OptionOption3 = 0;

int BlueatoothOption1 = 0;

int WirelessOption1 = 0, WirelessOption2 = 0, WirelessOption3 = 0;

unsigned char idSel = 0, pageSel = 0;

// variables to store options, ONLY supports floats
// if you want to edit an int in the Menu, still pass in a float and set decimal readout to 0
// the recast the float to an int upon Menu comletion processing
float pad = 1, lineLvl = 0, linePos = 0;

const char *OffOnItems[] = {"Off", "On"};
const char *OutLinePlaceItems[] = {"Direct", "P. Pre.", "P. Comp.", "P. Eq."};

ESP32Encoder encoder;
ESP32Encoder encoderA;
ESP32Encoder encoderB;
ESP32Encoder encoderC;

Preset **Pusr = new Preset *[numb_preset];

// encoder stuff
bool fastInc = false;

long encPos = 0, oldPos = 0, encPos_A = 0, oldPos_A = 0,
     encPos_B = 0, oldPos_B = 0, encPos_C = 0, oldPos_C = 0;

uint64_t encSpeed1, encSpeed2;

Menu::Menu(unsigned char *inputs, float *temp) {
    this->inputs = inputs;
    this->temp = temp;
}

void Menu::countEncoder(bool *fastInc, long *encP, long *encOp, ESP32Encoder *encoderSelect) {
    delay(50);
    while (*encOp != *encP) {
        encSpeed2 = encSpeed1;
        encSpeed1 = esp_timer_get_time();

        uint64_t speEnc = encSpeed1 - encSpeed2;
        *encOp = *encP;
        *encP = encoderSelect->getCount();
        speEnc < 0.15e6 ? *fastInc = true : *fastInc = false;
    }
}

void Menu::incDecItemPreset(bool inc_dec, bool fastInc, unsigned char par) {
    float var = Pusr[idSel]->getValueEffectPreset(pageSel, par);
    if (inc_dec && !fastInc)
        var += 0.1;
    else if (!inc_dec && !fastInc)
        var -= 0.1;
    else if (inc_dec && fastInc)
        var += 1;
    else if (!inc_dec && fastInc)
        var -= 1;
    Pusr[idSel]->setValueEffectPreset(pageSel, par, var);
    Pusr[idSel]->displayMenuPreset(pageSel, par, &display);
}

void Menu::openPresetMenu() {
    bool presetSel = false;
    int inMenuPreset = 1;

    display.fillScreen(MENU_BACKGROUND);

    Pusr[idSel]->displayMenuPreset(0, 4, &display);

    while (inMenuPreset != 0) {
        encPos = encoder.getCount();
        encPos_A = encoderA.getCount();
        encPos_B = encoderB.getCount();
        encPos_C = encoderC.getCount();

        // M encoder action
        if ((encPos - oldPos) > 0) {
            countEncoder(&fastInc, &encPos, &oldPos, &encoder);
            if (presetSel) {
                idSel < numb_preset - 2 ? idSel++ : idSel = 0;
                Pusr[idSel]->displayMenuPreset(pageSel, 4, &display);
            } else {
                if (pageSel < Pusr[idSel]->)
                    pageSel++;
                Pusr[idSel]->displayMenuPreset(pageSel, 3, &display);
            }
        }
        if ((encPos - oldPos) < 0) {
            countEncoder(&fastInc, &encPos, &oldPos, &encoder);
            if (presetSel) {
                idSel > 0 ? idSel-- : idSel = numb_preset - 2;
                Pusr[idSel]->displayMenuPreset(pageSel, 4, &display);
            } else {
                if (pageSel > 0)
                    pageSel--;
                Pusr[idSel]->displayMenuPreset(pageSel, 3, &display);
            }
        }
        // A encoder action
        if ((encPos_A - oldPos_A) > 0) {
            countEncoder(&fastInc, &encPos_A, &oldPos_A, &encoderA);
            incDecItemPreset(1, fastInc, 0);
        }
        if ((encPos_A - oldPos_A) < 0) {
            countEncoder(&fastInc, &encPos_A, &oldPos_A, &encoderA);
            incDecItemPreset(0, fastInc, 0);
        }
        // B encoder action
        if ((encPos_B - oldPos_B) > 0) {
            countEncoder(&fastInc, &encPos_B, &oldPos_B, &encoderB);
            incDecItemPreset(1, fastInc, 1);
        }
        if ((encPos_B - oldPos_B) < 0) {
            countEncoder(&fastInc, &encPos_B, &oldPos_B, &encoderB);
            incDecItemPreset(0, fastInc, 1);
        }
        // C encoder action
        if ((encPos_C - oldPos_C) > 0) {
            countEncoder(&fastInc, &encPos_C, &oldPos_C, &encoderC);
            incDecItemPreset(1, fastInc, 2);
        }
        if ((encPos_C - oldPos_C) < 0) {
            countEncoder(&fastInc, &encPos_C, &oldPos_C, &encoderC);
            incDecItemPreset(0, fastInc, 2);
        }
        switch (*inputs) {
        case enterButton:
            *inputs = 0;
            presetSel = !presetSel;
            break;

        case menuButton:
            *inputs = 0;
            processMainMenu();
            Pusr[idSel]->displayMenuPreset(pageSel, 4, &display);
            break;

        case rightButton:
            *inputs = 0;

            break;

        case leftButton:
            *inputs = 0;

            break;

        default:
            break;
        }
    }
}

void Menu::processOptionMenu() {
    // the entire menu processing are basically 3 calls
    // YourMenu.MoveUp();
    // YourMenu.MoveDown();
    // EditMenuOption = YourMenu.selectRow();

    // set an inital flag that will be used to store what menu item the user exited on
    int EditMenuOption = 1;

    // blank out the screen
    display.fillScreen(MENU_BACKGROUND);

    // draw the main menu
    OptionMenu.draw();

    // run the processing loop until user move selector to title bar (which becomes exit)
    // and selectes it
    while (EditMenuOption != 0) {

        // standard encoder read
        encPos = encoder.getCount();

        // attempt to debouce these darn things...
        if ((encPos - oldPos) > 0) {
            delay(DEBOUNCE_FAST);
            while (oldPos != encPos) {
                oldPos = encPos;
                encPos = encoder.getCount();
            }
            // once encoder calms down and is done cycling, move selector up
            // since encoder reads are increasing
            // any menu wrapping is handled in the library

            // the EditMenu object type is special cased
            // 1. if a row was NOT selected, MoveUp / MoveDown will cycle throuh menu items
            // 2. if a row IS selected, MoveUp / MoveDown will cycle throuh the range of values withing the item

            OptionMenu.MoveUp();
        }

        if ((encPos - oldPos) < 0) {
            delay(DEBOUNCE_FAST);
            while (oldPos != encPos) {
                oldPos = encPos;
                encPos = encoder.getCount();
            }
            // once encoder calms down and is done cycling, move selector up
            // since encoder reads are decreasing
            // any menu wrapping is handled in the library

            // the EditMenu object type is special cased
            // 1. if a row was NOT selected, MoveUp / MoveDown will cycle throuh menu items
            // 2. if a row IS selected, MoveUp / MoveDown will cycle throuh the range of values withing the item
            OptionMenu.MoveDown();
        }

        if (*inputs == enterButton) {
            *inputs = 0;
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
            /*if (EditMenuOption == OptionOption5) { // budget item
                if (OptionMenu.value[OptionOption5] == 0) {
                    OptionMenu.disable(OptionOption4);
                    OptionMenu.setItemText(OptionOption4, "Tune (Alarm OFF)");
                    OptionMenu.drawRow(OptionOption4);
                } else {
                    OptionMenu.enable(OptionOption4);
                    OptionMenu.setItemText(OptionOption4, "Tune");
                    OptionMenu.drawRow(OptionOption4);
                }
            }*/
        }
    }

    // user must have pressed the encorder select button while on the title bar (which returns 0)
    // hence exiting the loop
    // now you can process / store / display the menu selections
    // remember this is from the EditMenu and has associated value property with each menu item
    Serial.println("Option Menu Selections ");
    Serial.println("______________________________");
    Serial.print("Pad -15dB : ");
    Serial.println(OffOnItems[(int)OptionMenu.value[OptionOption1]]);
    Serial.print("Level line out :");
    Serial.println(OptionMenu.value[OptionOption2]);
    Serial.print("Line out :");
    Serial.println(OutLinePlaceItems[(int)OptionMenu.value[OptionOption3]]);

    // an example of how to set other menu values based on selection here
    // remember all menu values passed in or returned are floats
    // so recast to int if you need to
}

void Menu::processBluetoothMenu() {
    int EditMenuOption = 1;

    display.fillScreen(MENU_BACKGROUND);

    BluetoothMenu.draw();

    while (EditMenuOption != 0) {

        delay(50);
        encPos = encoder.getCount();
        if ((encPos - oldPos) > 0) {
            delay(DEBOUNCE);
            while (oldPos != encPos) {
                oldPos = encPos;
                encPos = encoder.getCount();
            }
            BluetoothMenu.MoveUp();
        }
        if ((encPos - oldPos) < 0) {
            delay(DEBOUNCE);
            while (oldPos != encPos) {
                oldPos = encPos;
                encPos = encoder.getCount();
            }
            BluetoothMenu.MoveDown();
        }
        if (*inputs == enterButton) {
            *inputs = 0;

            EditMenuOption = BluetoothMenu.selectRow();
        }
    }
}

void Menu::processWirelessMenu() {

    int EditMenuOption = 1;

    display.fillScreen(MENU_BACKGROUND);

    WirelessMenu.draw();

    while (EditMenuOption != 0) {
        delay(50);
        encPos = encoder.getCount();
        if ((encPos - oldPos) > 0) {
            oldPos = encPos;
            WirelessMenu.MoveUp();
        }

        if ((encPos - oldPos) < 0) {
            oldPos = encPos;
            WirelessMenu.MoveDown();
        }

        if (*inputs == enterButton) {
            *inputs = 0;

            EditMenuOption = WirelessMenu.selectRow();
        }
    }
}

void Menu::displayAboutScreen() {
    float displayTemp = -1024;

    display.fillScreen(MENU_BACKGROUND);
    display.fillRect(0, 0, 320, 40, TITLE_BACK);

    display.setTextColor(MENU_HIGHLIGHTTEXT);
    display.setFont(&FONT_TITLE);
    display.setCursor(64, 30);
    display.print("About");

    int EditMenuOption = 1;
    int64_t refreshTime = esp_timer_get_time() - 6 * 1e6;
    while (EditMenuOption != 0) {
        if ((displayTemp != *temp) && (esp_timer_get_time() - refreshTime >= (5 * 1e6))) {
            displayTemp = *temp;
            refreshTime = esp_timer_get_time();
            display.fillRect(0, 40, 320, 200, MENU_BACKGROUND);
            display.setCursor(0, 68);
            display.setTextColor(MENU_TEXT);
            display.setFont(&FONT_SMALL);
            display.println("Blue Note Amplifier");
            display.println("2022-2023");
            display.print("Version : ");
            display.println("Alpha");
            display.print("temp : ");
            display.print(displayTemp);
            display.println(" degC");
            display.print("Fan speed : ");
            display.println("0 RPM");
        }
        if (*inputs == enterButton) {
            *inputs = 0;

            EditMenuOption = AboutMenu.selectRow();
        }
    }
}
// function to process main menu iteraction ideally this implementation makes it easy to launch your menu from anywhere in th
void Menu::processMainMenu() {
    // set an inital flag that will be used to store what menu item the user exited on
    int MainMenuOption = 1;

    display.fillScreen(MENU_BACKGROUND);

    MainMenu.draw();

    // run the processing loop until user move selector to title bar (which becomes exit, i.e. 0 return val)
    // and selectes it
    // note menu code can return - 1 for errors so run unitl non zero

    while (MainMenuOption != 0) {
        encPos = encoder.getCount();

        if ((encPos - oldPos) > 0) {
            delay(DEBOUNCE);
            while (oldPos != encPos) {
                oldPos = encPos;
                encPos = encoder.getCount();
            }
            MainMenu.MoveUp();
        }

        if ((encPos - oldPos) < 0) {
            delay(DEBOUNCE);
            while (oldPos != encPos) {
                oldPos = encPos;
                encPos = encoder.getCount();
            }
            MainMenu.MoveDown();
        }

        if (*inputs == enterButton) {
            *inputs = 0;
            MainMenuOption = MainMenu.selectRow();

            if (MainMenuOption == MenuOption1) {
                this->processOptionMenu();
                display.fillScreen(MENU_BACKGROUND);
                MainMenu.draw();
            }
            if (MainMenuOption == MenuOption2) {
                this->processBluetoothMenu();
                display.fillScreen(MENU_BACKGROUND);
                MainMenu.draw();
            }
            if (MainMenuOption == MenuOption3) {
                this->processWirelessMenu();
                display.fillScreen(MENU_BACKGROUND);
                MainMenu.draw();
            }
            if (MainMenuOption == MenuOption4) {
                this->displayAboutScreen();
                display.fillScreen(MENU_BACKGROUND);
                MainMenu.draw();
            }
        }
    }
    display.fillScreen(MENU_BACKGROUND);
    MenuOption = 0;
}

void Menu::setupMenu() {
    // fire up the display
    display.begin();
    display.setRotation(1);

    // menu code done, now proceed to your code
    display.fillScreen(MENU_BACKGROUND);

    char strName[18];
    for (int i = 0; i < numb_preset - 1; i++) {
        sprintf(strName, "Usr Preset %d", i);
        Pusr[i] = new Preset(i, strName);
    }

    MainMenu.init(MENU_TEXT, MENU_BACKGROUND, MENU_HIGHLIGHTTEXT, MENU_HIGHLIGHT, 64, 3, "Main Menu", FONT_TITLE, FONT_TITLE);

    MenuOption1 = MainMenu.addNI("Options");
    MenuOption2 = MainMenu.addNI("Bluetooth");
    MenuOption3 = MainMenu.addNI("Wi-fi");
    MenuOption4 = MainMenu.addNI("About");

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
    OptionOption2 = OptionMenu.addNI("Lvl l.o. (dB):", lineLvl, -40.0, 0.0, .5, 2, NULL);
    OptionOption3 = OptionMenu.addNI("Line out :", linePos, 0, sizeof(OutLinePlaceItems) / sizeof(OutLinePlaceItems[0]), 1, 0, OutLinePlaceItems);

    OptionMenu.SetItemValue(OptionOption1, 0);
    OptionMenu.SetItemValue(OptionOption3, 0); // the 2nd element in the ReadoutItems array

    OptionMenu.setTitleColors(TITLE_TEXT, TITLE_BACK);
    OptionMenu.setTitleBarSize(0, 0, 320, 40);
    OptionMenu.setTitleTextMargins(60, 30);
    OptionMenu.setItemTextMargins(12, 25, 10);
    OptionMenu.setMenuBarMargins(5, 315, 4, 2);
    OptionMenu.setItemColors(MENU_DISABLE, MENU_HIGHBORDER, MENU_SELECTBORDER);

    BluetoothMenu.init(MENU_TEXT, MENU_BACKGROUND, MENU_HIGHLIGHTTEXT, MENU_HIGHLIGHT, MENU_SELECTTEXT, MENU_SELECT,
                       DATA_COLUMN, ROW_HEIGHT, ROWS, "Bluetooth Menu", FONT_ITEM, FONT_TITLE);

    BlueatoothOption1 = BluetoothMenu.addNI("Enable", 0, 0, 1, 1, 0, OffOnItems);

    BluetoothMenu.setTitleColors(TITLE_TEXT, TITLE_BACK);
    BluetoothMenu.setTitleBarSize(0, 0, 320, 40);
    BluetoothMenu.setTitleTextMargins(60, 30);
    BluetoothMenu.setItemTextMargins(12, 25, 10);
    BluetoothMenu.setMenuBarMargins(10, 305, 4, 2);
    BluetoothMenu.setItemColors(MENU_DISABLE, MENU_HIGHBORDER, MENU_SELECTBORDER);

    WirelessMenu.init(MENU_TEXT, MENU_BACKGROUND, MENU_HIGHLIGHTTEXT, MENU_HIGHLIGHT, MENU_SELECTTEXT, MENU_SELECT,
                      DATA_COLUMN, ROW_HEIGHT, ROWS, "Wi-fi Menu", FONT_ITEM, FONT_TITLE);
    WirelessOption1 = WirelessMenu.addNI("Enable", 0, 0, 1, 1, 0, OffOnItems);
    WirelessOption2 = WirelessMenu.addNI("Network1", 0, 0, 255, 1, 0);
    WirelessOption3 = WirelessMenu.addNI("Network2", 0, 0, 255, 1, 0);

    WirelessMenu.setTitleColors(TITLE_TEXT, TITLE_BACK);
    WirelessMenu.setTitleBarSize(0, 0, 320, 40);
    WirelessMenu.setTitleTextMargins(60, 30);
    WirelessMenu.setItemTextMargins(12, 25, 10);
    WirelessMenu.setMenuBarMargins(10, 305, 4, 2);
    WirelessMenu.setItemColors(MENU_DISABLE, MENU_HIGHBORDER, MENU_SELECTBORDER);

    ESP32Encoder::useInternalWeakPullResistors = NONE;
    encoder.attachHalfQuad(ENCM_A_PIN, ENCM_B_PIN);
    encoder.clearCount();
    encoderA.attachHalfQuad(ENCA_A_PIN, ENCA_B_PIN);
    encoderA.clearCount();
    encoderB.attachHalfQuad(ENCB_A_PIN, ENCB_B_PIN);
    encoderB.clearCount();
    encoderC.attachHalfQuad(ENCC_A_PIN, ENCC_B_PIN);
    encoderC.clearCount();
}

// end