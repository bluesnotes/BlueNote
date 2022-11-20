
#include "MCP23008.h"
#include "Temp_Control.h"
#include "preset_menu_manager.h"

volatile bool flagSecond = false;
volatile bool flagInterruptMCP23008 = false;

volatile char secondCounter = 0;

unsigned char MCP23008Inputs = 0;

float temperature = 0;

hw_timer_t *timer = NULL;

TaskHandle_t Task0, Task1;

Temp_Control tempCtrl;

Menu menu(&MCP23008Inputs, &temperature);

portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;

void interruptsSys(void *parameter) {
    while (1) {
        if (flagSecond) {
            flagSecond = false;
            // uint32_t ramfreeb = ;
            float ramUsePercent = ((float)ESP.getFreeHeap() / 327680) * 100;
            Serial.print("RAM Free: ");
            Serial.print(ramUsePercent);
            Serial.println("%");
            temperature = tempCtrl.temperatureControl();
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
    if (secondCounter > 9) {
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

    // disableCore0WDT();

    menu.setupMenu();

    Serial.begin(115200);

    timer = timerBegin(1, 0xC350, true); // timer 1, 80Mhz / 50k = 1.6kHz
    timerAttachInterrupt(timer, &timer1Interrupt, true);
    timerAlarmWrite(timer, 160, true);
    timerAlarmEnable(timer);

    // initPresetUsr();
    temperature = tempCtrl.setup();

    init_MCP23008();
    attachInterrupt(INT_MCP23008_PIN, MCP23008Interrupt, RISING);

    xTaskCreatePinnedToCore(interruptsSys, "Task1", 30000, NULL, 4, &Task1, 1);
}

void loop() {
    menu.openPresetMenu();
    vTaskDelay(50);
}
