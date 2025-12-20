#include "DSP_manager.h"
#include "basic48k_IC_1.h"

DSP_manager::DSP_manager(/* args */) {
}

DSP_manager::~DSP_manager() {
}

void DSP_manager::setup(void) {
    SPI.begin();
    DSP.begin(DEVICE_ARCHITECTURE_IC_1, MOD_SAFELOADMODULE_DATA_SAFELOAD0_ADDR, CS_ADAU);
    default_download_IC_1();
    DSP.writeRegister(REG_MP5_WRITE_IC_1_ADDR, 0); /*Reset codec*/
    delay(2);
    DSP.writeRegister(REG_MP5_WRITE_IC_1_ADDR, 1);
    SPI.endTransaction();
    delay(1);
}