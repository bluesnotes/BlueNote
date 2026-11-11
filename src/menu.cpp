#include "menu.h"

#define NUMB_PRESET 15

int MenuOption = 0;

// must have variables for each Menu item
// best to have these global so you can use them in processing functions
int MenuOption1 = 0, MenuOption2 = 0, MenuOption3 = 0, MenuOption4 = 0;

int OptionOption1 = 0, OptionOption2 = 0, OptionOption3 = 0, OptionOption4 = 0, OptionOption5 = 0;

int BlueatoothOption1 = 0;

int WirelessOption1 = 0, WirelessOption2 = 0, WirelessOption3 = 0;

unsigned char idSel = 0, pageSel = 0;

// variables to store options, ONLY supports floats
// if you want to edit an int in the Menu, still pass in a float and set decimal readout to 0
// the recast the float to an int upon Menu comletion processing
float pad = 1, impedance = 0, phantom = 0, lineLvl = 0, linePos = 0;

const char *OffOnItems[] = {"Off", "On"};
const char *impedanceItems[] = {"500k", "47k"};
const char *OutLinePlaceItems[] = {"Direct", "P. Pre.", "P. Comp.", "P. Eq."};

ESP32Encoder encoder;

ExternalEEPROM myMem;

#define LOCATION_SETTINGS 0

#define VALID_DATA __TIME__

Preset **Pusr = new Preset *[NUMB_PRESET];

namespace {
constexpr uint32_t PRESET_EEPROM_BASE = 1024;
constexpr uint32_t PRESET_MAGIC = 0x50525354;
constexpr uint16_t PRESET_VERSION = 2;
constexpr unsigned int PRESET_MAX_VALUES = 80;
constexpr size_t PRESET_NAME_LENGTH = 20;
constexpr unsigned char FIXED_PRESET_COUNT = 6;
constexpr const char *FIXED_PRESET_NAMES[FIXED_PRESET_COUNT] = {
    "Rock", "Jazz", "RnB", "Metal", "Raggae", "Pop"};

struct PresetRecord {
    uint32_t magic;
    uint16_t version;
    uint16_t count;
    char name[PRESET_NAME_LENGTH];
    float values[PRESET_MAX_VALUES];
};

uint32_t presetAddress(unsigned char id) {
    return PRESET_EEPROM_BASE + id * sizeof(PresetRecord);
}

bool savePresetToEEPROM(unsigned char id) {
    if (id >= NUMB_PRESET || Pusr[id] == nullptr)
        return false;

    const unsigned int count = Pusr[id]->getValueCount();
    if (count > PRESET_MAX_VALUES)
        return false;

    PresetRecord record = {};
    record.magic = PRESET_MAGIC;
    record.version = PRESET_VERSION;
    record.count = count;
    Pusr[id]->getPresetName().toCharArray(record.name, sizeof(record.name));

    if (!Pusr[id]->copyEffectValues(record.values, PRESET_MAX_VALUES)) {
        return false;
    }

    myMem.write(presetAddress(id),
                reinterpret_cast<uint8_t *>(&record),
                sizeof(record));

    return true;
}

bool loadPresetFromEEPROM(unsigned char id) {
    if (id >= NUMB_PRESET || Pusr[id] == nullptr)
        return false;

    PresetRecord record = {};

    myMem.read(presetAddress(id),
               reinterpret_cast<uint8_t *>(&record),
               sizeof(record));

    if (record.magic != PRESET_MAGIC ||
        record.version != PRESET_VERSION ||
        record.count != Pusr[id]->getValueCount() ||
        record.count > PRESET_MAX_VALUES ||
        !Pusr[id]->applyEffectValues(record.values, record.count)) {
        return false;
    }

    if (id >= FIXED_PRESET_COUNT && record.name[0] != '\0')
        Pusr[id]->setPreseName(String(record.name));
    return true;
}

void drawSplashScreen(Adafruit_ILI9341 &screen) {
    screen.fillScreen(ILI9341_BLACK);
    screen.setTextWrap(false);

    const int logoX = (screen.width() - BLUE_NOTE_LOGO_WIDTH) / 2;
    const int logoY = 8;

    screen.drawRGBBitmap(
        logoX,
        logoY,
        reinterpret_cast<const uint16_t *>(blueNoteLogo),
        BLUE_NOTE_LOGO_WIDTH,
        BLUE_NOTE_LOGO_HEIGHT);

    screen.drawRect(35, 182, screen.width() - 70, 18, MENU_TEXT);
}

void updateSplashProgress(Adafruit_ILI9341 &screen, uint8_t progress) {
    if (progress > 100)
        progress = 100;

    const int barX = 35;
    const int barY = 185;
    const int barWidth = screen.width() - 74;
    const int barHeight = 14;

    int fillWidth = (barWidth * progress) / 100;
    screen.fillRect(barX, barY, fillWidth, barHeight, MENU_HIGHLIGHT);

    screen.fillRect(0, 205, screen.width(), 35, MENU_BACKGROUND);
    screen.setFont(&FONT_SMALL);
    screen.setTextColor(MENU_TEXT);

    char percentage[6];
    snprintf(percentage, sizeof(percentage), "%u%%", progress);

    int16_t x1, y1;
    uint16_t textWidth, textHeight;
    screen.getTextBounds(percentage, 0, 0, &x1, &y1, &textWidth, &textHeight);
    screen.setCursor((screen.width() - textWidth) / 2 - x1, 225 - y1);
    screen.print(percentage);
}
} // namespace

// encoder stuff
bool fastInc = false;

long encPos = 0, oldPos = 0;
uint32_t pot1 = 0, oldPot1 = 0, pot2 = 0, oldPot2 = 0, pot3 = 0, oldPot3 = 0;

uint64_t encSpeed1, encSpeed2;

Menu::Menu(INOUTVAR *processVar) {
    this->temp = temp;
    this->processVar = processVar;
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

uint32_t Menu::readAdcOversampled(int pin) {
    uint32_t sum = 0;
    int samples = 64;

    for (int i = 0; i < samples; i++) {
        // analogReadMilliVolts applique automatiquement la calibration eFuse
        sum += analogReadMilliVolts(pin);

        // Un micro-délai laisse le temps au convertisseur de se stabiliser
        delayMicroseconds(50);
    }

    return sum / samples;
}

void Menu::incDecItemPreset(uint32_t valueCmd, unsigned char par) {
    if (par < Pusr[idSel]->getLenghtEffect(pageSel)) {
        float incFact = Pusr[idSel]->getIncFactor(pageSel, par);
        float min = Pusr[idSel]->getMinValueEffectPreset(pageSel, par);
        float max = Pusr[idSel]->getMaxValueEffectPreset(pageSel, par);

        float percentCmd = 0.1 + ((3000.0 - ((float)valueCmd) - 145.0) / (3000.0));
        percentCmd = percentCmd < 0 ? 0 : percentCmd;
        percentCmd = percentCmd > 1 ? 1 : percentCmd;

        float newValue;

        // ---  LOG MANAGE ---
        if (incFact < 0) {
            // Transformation de la course linéaire du potard en courbe logarithmique (base 10)
            // percentCmd va de 0 à 1 -> logPercent va de 0 à 1
            float baseExp = 500.0f;
            float expPercent = (powf(baseExp, percentCmd) - 1.0f) / (baseExp - 1.0f);

            float range = max - min;
            newValue = (range * expPercent) + min;

            if (newValue < 1.0f) {
                newValue = roundf(newValue * 100.0f) / 100.0f;
            } else if (newValue < 10.0f) {
                newValue = roundf(newValue * 10.0f) / 10.0f;
            } else if (newValue < 100.0f) {
                newValue = roundf(newValue);
            } else if (newValue < 1000.0f) {
                newValue = roundf(newValue / 10.0f) * 10.0f;
            } else if (newValue < 10000.0f) {
                newValue = roundf(newValue / 100.0f) * 100.0f;
            } else {
                newValue = roundf(newValue / 1000.0f) * 1000.0f;
            }
        }
        // --- LINEAR MANAGE ---
        else {
            float range = max - min;
            newValue = (range * percentCmd) + min;
            newValue = roundf(newValue / incFact) * incFact;
        }

        newValue = newValue < min ? min : newValue;
        newValue = newValue > max ? max : newValue;

        Pusr[idSel]->setValueEffectPreset(pageSel, par, newValue);
        Pusr[idSel]->displayMenuPreset(pageSel, par, presetDisplay::oneGauge, &display);
    }
}

void Menu::editPresetName() {
    static const char nameCharacters[] = " ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_";
    constexpr size_t maxNameLength = PRESET_NAME_LENGTH - 1;

    char name[PRESET_NAME_LENGTH] = {};
    String currentName = Pusr[idSel]->getPresetName();
    currentName.toCharArray(name, sizeof(name));

    size_t cursor = strlen(name);
    if (cursor >= maxNameLength)
        cursor = maxNameLength - 1;
    if (name[cursor] == '\0') {
        name[cursor] = ' ';
        name[cursor + 1] = '\0';
    }

    long position = encoder.getCount();
    oldPos = position;
    bool editing = true;
    bool redraw = true;

    while (editing) {
        if (redraw) {
            display.fillScreen(MENU_BACKGROUND);
            display.setTextColor(MENU_HIGHLIGHTTEXT);
            display.setFont(&FONT_TITLE);
            display.setCursor(20, 42);
            display.printf("Rename preset %u", idSel);

            display.setFont(&FONT_EDITTITLE);
            display.setTextColor(MENU_TEXT);
            display.setCursor(20, 120);
            display.print(name);

            char prefix[PRESET_NAME_LENGTH] = {};
            memcpy(prefix, name, cursor);
            int16_t textX, textY;
            uint16_t textWidth, textHeight;
            display.getTextBounds(prefix, 20, 120, &textX, &textY, &textWidth, &textHeight);
            display.drawFastHLine(20 + textWidth, 124, 15, MENU_HIGHLIGHT);

            display.setFont(&FONT_SMALL);
            display.setTextColor(MENU_TEXT);
            display.setCursor(20, 190);
            display.print("Rotate: character   Left/Right: cursor");
            display.setCursor(20, 215);
            display.print("Enter: save   Save/Exit: cancel");
            redraw = false;
        }

        delay(50);
        long newPosition = encoder.getCount();
        long delta = newPosition - position;
        if (delta != 0) {
            position = newPosition;
            oldPos = newPosition;
            long characterCount = sizeof(nameCharacters) - 1;
            long characterIndex = 0;
            while (nameCharacters[characterIndex] != name[cursor] && characterIndex < characterCount)
                characterIndex++;
            characterIndex = (characterIndex + delta) % characterCount;
            if (characterIndex < 0)
                characterIndex += characterCount;
            name[cursor] = nameCharacters[characterIndex];
            redraw = true;
        }

        if (processVar->MCP23008Inputs == leftButton) {
            processVar->MCP23008Inputs = 0;
            if (cursor > 0) {
                cursor--;
                redraw = true;
            }
        } else if (processVar->MCP23008Inputs == rightButton) {
            processVar->MCP23008Inputs = 0;
            if (cursor < maxNameLength - 1) {
                cursor++;
                if (name[cursor] == '\0') {
                    name[cursor] = ' ';
                    name[cursor + 1] = '\0';
                }
                redraw = true;
            }
        } else if (processVar->MCP23008Inputs == enterButton) {
            processVar->MCP23008Inputs = 0;
            String editedName(name);
            editedName.trim();
            if (editedName.length() > 0) {
                Pusr[idSel]->setPreseName(editedName);
                savePresetToEEPROM(idSel);
                editing = false;
            }
        } else if (processVar->MCP23008Inputs == saveExitButton) {
            processVar->MCP23008Inputs = 0;
            editing = false;
        }
    }
}

void Menu::openPresetMenu() {
    bool presetUnsel = false;
    unsigned char paramSel = 0;
    int inMenuPreset = 1;

    display.fillScreen(MENU_BACKGROUND);

    Pusr[idSel]->displayMenuPreset(pageSel, paramSel, presetDisplay::selectPresetAllDisplay, &display);

    while (inMenuPreset != 0) {
        encPos = encoder.getCount();
        pot1 = readAdcOversampled(PIN_POT1);
        pot2 = readAdcOversampled(PIN_POT2);
        pot3 = readAdcOversampled(PIN_POT3);
        delay(50); // debounce delay

        // M encoder action
        if ((encPos - oldPos) > 0) {
            countEncoder(&fastInc, &encPos, &oldPos, &encoder);
            paramSel = 0;
            if (presetUnsel) {
                idSel < NUMB_PRESET - 1 ? idSel++ : idSel = 0;
                Pusr[idSel]->displayMenuPreset(pageSel, paramSel, presetDisplay::allDisplay, &display); // change preset sel
            } else if (pageSel < Pusr[idSel]->getSizePreset()) {
                pageSel++;
                Pusr[idSel]->displayMenuPreset(pageSel, paramSel, presetDisplay::effectDisplay, &display); // change effect sel
            }
        }
        if ((encPos - oldPos) < 0) {
            countEncoder(&fastInc, &encPos, &oldPos, &encoder);
            paramSel = 0;
            if (presetUnsel) {
                idSel > 0 ? idSel-- : idSel = NUMB_PRESET - 1;
                Pusr[idSel]->displayMenuPreset(pageSel, paramSel, presetDisplay::allDisplay, &display);
            } else if (pageSel > 0) {
                pageSel--;
                Pusr[idSel]->displayMenuPreset(pageSel, paramSel, presetDisplay::effectDisplay, &display);
            }
        }
        // pot1 action
        if (labs(pot1 - oldPot1) > 5) {
            oldPot1 = pot1;
            incDecItemPreset(pot1, paramSel);
        }

        // pot2 action
        if (labs(pot2 - oldPot2) > 5) {
            oldPot2 = pot2;
            incDecItemPreset(pot2, 1 + paramSel);
        }

        // pot3 action
        if (labs(pot3 - oldPot3) > 5) {
            oldPot3 = pot3;
            incDecItemPreset(pot3, 2 + paramSel);
        }

        int lenghtEffect = 0;
        switch (processVar->MCP23008Inputs) {
        case saveExitButton:
            processVar->MCP23008Inputs = 0;
            if (savePresetToEEPROM(idSel))
                Serial.printf("Preset %u saved to EEPROM\n", idSel);
            else
                Serial.printf("Failed to save preset %u\n", idSel);

            break;
        case enterButton:
            processVar->MCP23008Inputs = 0;
            presetUnsel = !presetUnsel;
            if (presetUnsel) {
                Pusr[idSel]->displayMenuPreset(pageSel, paramSel, presetDisplay::allDisplay, &display); // change preset sel
            } else
                Pusr[idSel]->displayMenuPreset(pageSel, paramSel, presetDisplay::selectPresetAllDisplay, &display); // change effect sel

            break;
        case menuButton:
            processVar->MCP23008Inputs = 0;
            if (presetUnsel) {
                processMainMenu();
            } else {
                editPresetName();
            }
            Pusr[idSel]->displayMenuPreset(pageSel, paramSel, presetDisplay::selectPresetAllDisplay, &display);
            break;
        case rightButton:
            processVar->MCP23008Inputs = 0;
            lenghtEffect = Pusr[idSel]->getLenghtEffect(pageSel);
            if (paramSel < lenghtEffect - 3) {
                paramSel += 3;
                Pusr[idSel]->displayMenuPreset(pageSel, paramSel, presetDisplay::effectDisplay, &display);
            }
            break;
        case leftButton:
            processVar->MCP23008Inputs = 0;
            if (paramSel > 0) {
                paramSel -= 3;
                Pusr[idSel]->displayMenuPreset(pageSel, paramSel, presetDisplay::effectDisplay, &display);
            }
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

            OptionMenu.MoveDown();
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
            OptionMenu.MoveUp();
        }

        if (processVar->MCP23008Inputs == enterButton) {
            processVar->MCP23008Inputs = 0;
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
        } else if (processVar->MCP23008Inputs == saveExitButton) {
            processVar->MCP23008Inputs = 0;
            EditMenuOption = BluetoothMenu.backwardMenu();
        }
    }

    // user must have pressed the encorder select button while on the title bar (which returns 0)
    // hence exiting the loop
    // now you can process / store / display the menu selections
    // remember this is from the EditMenu and has associated value property with each menu item
    Serial.print("Pad -15dB : ");
    Serial.println(OffOnItems[(int)OptionMenu.value[OptionOption1]]);
    Serial.print("impedance :");
    Serial.println(impedanceItems[(int)OptionMenu.value[OptionOption2]]);
    Serial.print("Phantom :");
    Serial.println(OffOnItems[(int)OptionMenu.value[OptionOption3]]);
    Serial.print("Line out lvl:");
    Serial.println((int)OptionMenu.value[OptionOption4]);

    processVar->changeVariable = true;
    processVar->padInst = (char)OptionMenu.value[OptionOption1];
    processVar->impedanceInst = (char)OptionMenu.value[OptionOption2];
    processVar->phantom = (char)OptionMenu.value[OptionOption3];
    processVar->volumeLineOut = (unsigned char)(-(OptionMenu.value[OptionOption4] * 2)) + 2;

    Serial.print("Line out lvl:");
    Serial.println(processVar->volumeLineOut);

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
            BluetoothMenu.MoveDown();
        }
        if ((encPos - oldPos) < 0) {
            delay(DEBOUNCE);
            while (oldPos != encPos) {
                oldPos = encPos;
                encPos = encoder.getCount();
            }
            BluetoothMenu.MoveUp();
        }
        if (processVar->MCP23008Inputs == enterButton) {
            processVar->MCP23008Inputs = 0;

            EditMenuOption = BluetoothMenu.selectRow();
        } else if (processVar->MCP23008Inputs == saveExitButton) {
            processVar->MCP23008Inputs = 0;
            EditMenuOption = BluetoothMenu.backwardMenu();
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
            WirelessMenu.MoveDown();
        }

        if ((encPos - oldPos) < 0) {
            oldPos = encPos;
            WirelessMenu.MoveUp();
        }

        if (processVar->MCP23008Inputs == enterButton) {
            processVar->MCP23008Inputs = 0;

            EditMenuOption = WirelessMenu.selectRow();
        } else if (processVar->MCP23008Inputs == saveExitButton) {
            processVar->MCP23008Inputs = 0;
            EditMenuOption = MainMenu.backwardMenu();
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
        if ((displayTemp != processVar->temperature) && (esp_timer_get_time() - refreshTime >= (5 * 1e6))) {
            displayTemp = processVar->temperature;
            refreshTime = esp_timer_get_time();
            display.fillRect(0, 40, 320, 200, MENU_BACKGROUND);
            display.setCursor(0, 68);
            display.setTextColor(MENU_TEXT);
            display.setFont(&FONT_SMALL);
            display.println("Blue Note Amplifier");
            display.println("2022-2026");
            display.print("Version : ");
            display.println(VERSION_STRING);
            display.print("Temp : ");
            display.print(displayTemp);
            display.println(" degC");
            display.print("Fan speed : ");
            display.println("0 RPM");
        }
        if (processVar->MCP23008Inputs == saveExitButton) {
            processVar->MCP23008Inputs = 0;

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
            MainMenu.MoveDown();
        }

        if ((encPos - oldPos) < 0) {
            delay(DEBOUNCE);
            while (oldPos != encPos) {
                oldPos = encPos;
                encPos = encoder.getCount();
            }
            MainMenu.MoveUp();
        }

        if (processVar->MCP23008Inputs == enterButton) {
            processVar->MCP23008Inputs = 0;
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
        } else if (processVar->MCP23008Inputs == saveExitButton) {
            processVar->MCP23008Inputs = 0;
            MainMenuOption = MainMenu.backwardMenu();
        }
    }
    display.fillScreen(MENU_BACKGROUND);
    MenuOption = 0;
}

void Menu::setupMenu() {
    // fire up the display
    display.begin();
    display.setRotation(1);

    // splashscreen
    drawSplashScreen(display);
    updateSplashProgress(display, 0);
    write_1_bit_MCP23008(GPIO, LED_BCKL, true);

    Wire.begin();
    myMem.setMemorySize(262144);
    myMem.setPageSize(256);

    // Initialize the EEPROM
    if (myMem.begin() == false) {
        Serial.println(F("No memory detected. Freezing."));
        while (true)
            ;
    }
    Serial.println(F("Memory detected!"));
    updateSplashProgress(display, 10);

    char strName[18];
    for (unsigned char i = 0; i < NUMB_PRESET; i++) {
        if (i < FIXED_PRESET_COUNT)
            snprintf(strName, sizeof(strName), "%s", FIXED_PRESET_NAMES[i]);
        else
            snprintf(strName, sizeof(strName), "Usr Preset %d", i);
        Pusr[i] = new Preset(i, strName);
    }

    for (unsigned char i = 0; i < NUMB_PRESET; i++) {
        if (!loadPresetFromEEPROM(i)) {
            Serial.printf("No or invalid preset %u in EEPROM\n", i);
        }
        updateSplashProgress(display, 40 + (55 * (i + 1)) / NUMB_PRESET);
    }
    updateSplashProgress(display, 100);

    // Print out the size of the user settings struct
    Serial.print("Size of user settings in bytes: ");
    Serial.println(Pusr[0]->getLenghtPreset());

    Serial.print("Size of user settings in byteS: ");
    Serial.println(Pusr[0]->getSizePreset());

    MainMenu.init(MENU_TEXT, MENU_BACKGROUND, MENU_HIGHLIGHTTEXT, MENU_HIGHLIGHT, 64, 3, "Main Menu", FONT_TITLE, FONT_TITLE);

    MenuOption1 = MainMenu.addNI("Options");
    MenuOption2 = MainMenu.addNI("Bluetooth");
    MenuOption3 = MainMenu.addNI("Wi-fi");
    MenuOption4 = MainMenu.addNI("About");

    MainMenu.setTitleColors(TITLE_TEXT, TITLE_BACK);
    MainMenu.setTitleBarSize(0, 0, 320, 40);
    MainMenu.setTitleTextMargins(60, 30);
    MainMenu.setIconMargins(0, 0);
    MainMenu.setMenuBarMargins(15, 310, 6, 4);
    MainMenu.setItemColors(MENU_DISABLE, MENU_HIGHBORDER);
    MainMenu.setItemTextMargins(45, 45, 5);

    OptionMenu.init(MENU_TEXT, MENU_BACKGROUND, MENU_HIGHLIGHTTEXT, MENU_HIGHLIGHT, MENU_SELECTTEXT, MENU_SELECT,
                    DATA_COLUMN, ROW_HEIGHT, ROWS, "Option Menu", FONT_ITEM, FONT_TITLE);

    OptionOption1 = OptionMenu.addNI("Pad -15dB : ", pad, 0, sizeof(OffOnItems) / sizeof(OffOnItems[0]), 1, 0, OffOnItems);
    OptionOption2 = OptionMenu.addNI("In. Imp.: ", impedance, 0, sizeof(impedanceItems) / sizeof(impedanceItems[0]), 1, 0, impedanceItems);
    OptionOption3 = OptionMenu.addNI("Phantom (15V): ", phantom, 0, sizeof(OffOnItems) / sizeof(OffOnItems[0]), 1, 0, OffOnItems);
    OptionOption4 = OptionMenu.addNI("Lvl l.o. (dB):", lineLvl, -40.0, 1.0, .5, 2, NULL);
    OptionOption5 = OptionMenu.addNI("Line out :", linePos, 0, sizeof(OutLinePlaceItems) / sizeof(OutLinePlaceItems[0]), 1, 0, OutLinePlaceItems);

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

    analogReadResolution(11);       // resolution (9 à 12 bits)
    analogSetAttenuation(ADC_11db); // read until~3.3V
    oldPot1 = readAdcOversampled(PIN_POT1);
    oldPot2 = readAdcOversampled(PIN_POT2);
    oldPot3 = readAdcOversampled(PIN_POT3);
}

// end