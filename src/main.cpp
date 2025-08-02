
#include "DSP_manager.h"
#include "MCP23008.h"
#include "MCP3221.h"
#include "SPI.h"
#include "Temp_Control.h"
#include "preset_menu_manager.h"

volatile bool flagHundredMs = false;
volatile bool flagSecond = false;
volatile bool flagInterruptMCP23008 = false;

// SPISettings SIGMADSP_SPI_fast(4000000, MSBFIRST, SPI_MODE0); //spi settings for ADAU1466
// SPISettings SIGMADSP_SPI_slow(250000, MSBFIRST, SPI_MODE0); //spi settings for ADAU1466

volatile char secondCounter = 0;

uint8_t MCP23008Inputs = 0;

unsigned char volume = 0;

float temperature = 0;

hw_timer_t *timer = NULL;

TaskHandle_t Task0, Task1, Task2;

Temp_Control tempCtrl;

Menu menu(&MCP23008Inputs, &temperature);

DSP_manager dspManager;

portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;

void interruptsSysHp(void *parameter) {
    while (1) {
        if (flagHundredMs) {
            flagHundredMs = false;
            volume = smoothVolume((char)volume);
        }
        if (flagInterruptMCP23008) {
            flagInterruptMCP23008 = false;
            MCP23008Inputs = read_Int_MCP23008();
        }
        delay(10);
    }
}

void interruptsSysLp(void *parameter) {
    for (;;) {
        if (flagSecond) {
            flagSecond = false;

            temperature = tempCtrl.temperatureControl();

            float ramUsePercent = ((float)ESP.getFreeHeap() / 327680) * 100;
            Serial.print("RAM Free: ");
            Serial.print(ramUsePercent);
            Serial.println("%");

            delay(700);
        }
    }
}

void IRAM_ATTR timer1Interrupt() {
    portENTER_CRITICAL_ISR(&mux);
    if (secondCounter > 9) {
        secondCounter = 0;
        flagSecond = true;
    }
    secondCounter++;

    flagHundredMs = true;
    portEXIT_CRITICAL_ISR(&mux);
}

void IRAM_ATTR MCP23008Interrupt() {
    flagInterruptMCP23008 = true;
}

void setup() {
    Serial.begin(115200);

    menu.setupMenu();

    timer = timerBegin(1, 0xC350, true); // timer 1, 80Mhz / 50k = 1.6kHz
    timerAttachInterrupt(timer, &timer1Interrupt, true);
    timerAlarmWrite(timer, 160, true);
    timerAlarmEnable(timer); // interrupt every 100ms

    temperature = tempCtrl.setup();

    xTaskCreatePinnedToCore(interruptsSysHp, "Task1", 15000, NULL, 6, &Task1, 1);
    xTaskCreatePinnedToCore(interruptsSysLp, "Task2", 10000, NULL, 1, &Task2, 0);

    init_MCP23008();
    attachInterrupt(INT_MCP23008_PIN, MCP23008Interrupt, RISING);
    write_1_bit_MCP23008(GPIO, LED_BCKL, true);

    write_1_bit_MCP23008(GPIO, RST_ADAU_PIN, false);
    delay(1);
    write_1_bit_MCP23008(GPIO, RST_ADAU_PIN, true);
    delay(10);

    dspManager.setup();
}

void loop() {
    menu.openPresetMenu();
    vTaskDelay(50);
}
