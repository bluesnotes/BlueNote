#ifndef PIN_H
#define PIN_H

#define Display_DC 16
#define Display_CS 5
#define Display_RST 17

#define EN1_PIN 26
#define EN2_PIN 25

#define ONE_WIRE_PIN 32
#define PWM_FAN_PIN 2
#define TACH_FAN_PIN 0

#define INT_MCP23008_PIN 4

enum pinMCP23008 {
    rightButton = 1,
    leftButton = 2,
    saveButton = 4,
    menuButton = 8,
    enterButton = 16,
};

#endif