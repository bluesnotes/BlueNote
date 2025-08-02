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

    pinMode(PWM_FAN_PIN, PULLUP);
    pinMode(PWM_FAN_PIN, OUTPUT);
    digitalWrite(PWM_FAN_PIN, HIGH);

    ledcAttachPin(PWM_FAN_PIN, 1);
    ledcSetup(1, 30000, 8);
    ledcWrite(1, 128);

    // pinMode(TACH_FAN_PIN, INPUT);

    return temperature = 0;
}
float Temp_Control::temperatureControl(void) {
    float temperature = 0;

    temperature = sensors.getTempCByIndex(0);

    sensors.setWaitForConversion(false); // makes it async
    sensors.requestTemperatures();
    sensors.setWaitForConversion(true);

    uint32_t pwmTemp = roundf(temperature) * 2;

    if (temperature < 30)
        ledcWrite(1, 0);
    else if (temperature >= 30 && temperature < 50)
        ledcWrite(1, pwmTemp);
    else if (temperature >= 50 && temperature < 60)
        ledcWrite(1, 128);
    else if (temperature >= 60 && temperature < 70)
        ledcWrite(1, 192);
    else
        ledcWrite(1, 255);

    return temperature;
}