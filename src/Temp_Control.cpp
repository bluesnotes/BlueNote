#include "Temp_Control.h"

OneWire oneWire(ONE_WIRE_PIN);
DallasTemperature sensors(&oneWire);

Temp_Control::Temp_Control() {
}

Temp_Control::~Temp_Control() {
}

float Temp_Control::setup(void) {
    float temperature = 0;
    sensors.begin();
    sensors.requestTemperatures();
    temperature = sensors.getTempCByIndex(0);

    ledcSetup(0, 30000, 8);
    ledcAttachPin(PWM_FAN_PIN, 0);

    pinMode(TACH_FAN_PIN, INPUT);

    return temperature = 0;
}
float Temp_Control::temperatureControl(void) {
    float temperature = 0;
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

    return temperature;
}