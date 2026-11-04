#ifndef PIN_H
#define PIN_H

#define Display_DC 16  // hardware 27
#define Display_CS 5   // hardware 29
#define Display_RST 17 // hardware 28

#define ENCM_A_PIN 36 // hardware 3
#define ENCM_B_PIN 39 // hardware 4

#define PIN_POT 33  // hardware 8
#define PIN_POT1 32 // hardware 6
#define PIN_POT2 34 // hardware 5 26
#define PIN_POT3 35 // hardware 7 27

#define CS_ADAU 0 // hardware 25

#define ONE_WIRE_PIN 25    // hardware 7
#define INT_MCP23008_PIN 4 // hardware 26

#define PWM_FAN_PIN 2   // hardware 24
#define TACH_FAN_PIN 26 // hardware MCP23008 GPIO0

//************MCP23008 PIN*******************//
#define LED_BCKL 6
#define RST_ADAU_PIN 5

enum pinMCP23008 {
    saveExitButton = 1,
    menuButton = 2,
    rightButton = 4,
    leftButton = 8,
    enterButton = 16,
};

#endif