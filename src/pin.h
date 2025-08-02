#ifndef PIN_H
#define PIN_H

#define Display_DC 16  // hardware 27
#define Display_CS 5   // hardware 29
#define Display_RST 17 // hardware 28

#define CS_ADAU 0 // hardware 25

#define ENCM_A_PIN 36 // hardware 3
#define ENCM_B_PIN 39 // hardware 4

#define ENCA_A_PIN 33 // hardware 10 26
#define ENCA_B_PIN 25 // hardware 11 27

#define ENCB_A_PIN 26 // hardware 9 25
#define ENCB_B_PIN 27 // hardware 8 33

#define ENCC_A_PIN 34 // hardware 6
#define ENCC_B_PIN 35 // hardware 5

#define ONE_WIRE_PIN 32    // hardware 7
#define PWM_FAN_PIN 2      // hardware 24
#define INT_MCP23008_PIN 4 // hardware 26

//************MCP23008 PIN*******************//
#define TACH_FAN_PIN 0 // hardware MCP23008 GPIO0
#define LED_BCKL 5
#define RST_ADAU_PIN 6

enum pinMCP23008 {
    rightButton = 2,
    leftButton = 8,
    saveExitButton = 4,
    menuButton = 1,
    enterButton = 16,
};

#endif