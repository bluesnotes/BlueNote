#include "main.h"

volatile bool flagHundredMs = false;
volatile bool flagSecond = false;
volatile bool flagInterruptMCP23008 = false;

// SPISettings SIGMADSP_SPI_fast(4000000, MSBFIRST, SPI_MODE0); //spi settings for ADAU1466
// SPISettings SIGMADSP_SPI_slow(250000, MSBFIRST, SPI_MODE0); //spi settings for ADAU1466

volatile char secondCounter = 0;

unsigned char volumeCmd = 0, gainCmd = 0;

INOUTVAR processVar;

hw_timer_t *timer = NULL;

TaskHandle_t Task0, Task1, Task2;

Temperature_Regulation temperatureCtrl;

Menu menu(&processVar);

DSP_manager dspManager;

portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;

void interruptsSysHp(void *parameter) {
    while (1) {
        if (flagHundredMs) {
            flagHundredMs = false;
            unsigned char read = cmd_potentiometer((unsigned int)volumeCmd, ADDR_MCP3221A5_VOLUME, 8);
            if (volumeCmd != read) {
                volumeCmd = read;
                read = 255 - read;
                volumeES9033(read);
            }
            read = cmd_potentiometer((unsigned int)gainCmd, ADDR_MCP3221A6_GAIN, 8);
            if (gainCmd != read) {
                gainCmd = read;
                read = (unsigned char)floor((float)(255 - read) / 22);
                PGA_ES9290_instrument(read);
            }
        }
        if (flagInterruptMCP23008) {
            flagInterruptMCP23008 = false;
            processVar.MCP23008Inputs = read_Int_MCP23008();
        }
        if (processVar.changeVariable) {
            processVar.changeVariable = false;
            delay(110); // if not delay => ES9290 nak
            instrument_in_pad_line(processVar.padInst);
            instrument_in_impedance_line(processVar.impedanceInst);

            volume_ES9290_line(processVar.volumeLineOut);
            Serial.println(processVar.padInst);
            Serial.println(processVar.impedanceInst);
            Serial.println(processVar.volumeLineOut);
        }

        delay(1);
    }
}

void interruptsSysLp(void *parameter) {
    for (;;) {
        if (flagSecond) {
            flagSecond = false;

            processVar.temperature = temperatureCtrl.process();

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

    processVar.temperature = temperatureCtrl.setup();

    init_MCP23008();
    attachInterrupt(INT_MCP23008_PIN, MCP23008Interrupt, RISING);
    write_1_bit_MCP23008(GPIO, LED_BCKL, true);

    write_1_bit_MCP23008(GPIO, RST_ADAU_PIN, false);
    delay(200);
    write_1_bit_MCP23008(GPIO, RST_ADAU_PIN, true);
    delay(10);

    dspManager.setup();

    init_ES9033();
    init_ES9290();

    xTaskCreatePinnedToCore(interruptsSysHp, "Task1", 15000, NULL, 6, &Task1, 1);
    xTaskCreatePinnedToCore(interruptsSysLp, "Task2", 10000, NULL, 1, &Task2, 0);
}

void loop() {
    menu.openPresetMenu();
    vTaskDelay(50);
}
