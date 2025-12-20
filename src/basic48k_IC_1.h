/*
 * File:	C:\Users\damla\OneDrive\Bureau\MIDSPampBasicV02Copy\basic48k_IC_1.h
 * Created:	Saturday, 20 December 2025 21:46 PM
 * Description:	ADAU146xSchematic_0 program data.
 *
 * This software is distributed in the hope that it will be useful,
 * but is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * This software may only be used to program products purchased from
 * Analog Devices for incorporation by you into audio products that
 * are intended for resale to audio product end users.This software
 * may not be distributed whole or in any part to third parties.
 *
 * Copyright © 2025 Analog Devices, Inc. All rights reserved.
 */

#ifndef __BASIC48K_IC_1_H__
#define __BASIC48K_IC_1_H__

#include "SigmaStudioFW.h"
#include "basic48k_IC_1_REG.h"

#define DEVICE_ARCHITECTURE_IC_1 "ADAU1466"
#define DEVICE_ADDR_IC_1 0x0
/* DSP Ram Data */
#define DM1_DATA_SIZE_IC_1 96
#define DM1_DATA_ADDR_IC_1 24576
ADI_REG_TYPE DM1_DATA_IC_1_Data[DM1_DATA_SIZE_IC_1] = {
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
};

/* DSP Program Data */
#define PROGRAM_DATA_SIZE_IC_1 552
#define PROGRAM_DATA_ADDR_IC_1 49152
ADI_REG_TYPE PROGRAM_DATA_IC_1_Data[PROGRAM_DATA_SIZE_IC_1] = {
    0x00,
    0x00,
    0x00,
    0x02,
    0x0C,
    0x00,
    0xDC,
    0xDC,
    0x0D,
    0x00,
    0xFF,
    0xD2,
    0x0D,
    0x00,
    0xFF,
    0xD0,
    0x0D,
    0x00,
    0xF4,
    0x50,
    0x0D,
    0x00,
    0xF4,
    0x00,
    0xC0,
    0x00,
    0x23,
    0x80,
    0x80,
    0x00,
    0x00,
    0x00,
    0xC0,
    0x00,
    0x23,
    0x00,
    0x80,
    0x00,
    0x00,
    0x00,
    0xC0,
    0x00,
    0x23,
    0xC0,
    0x80,
    0x00,
    0x00,
    0x10,
    0xC0,
    0x00,
    0x22,
    0x00,
    0x80,
    0x00,
    0x00,
    0x00,
    0x08,
    0x80,
    0xDC,
    0xE0,
    0x0C,
    0x00,
    0xDC,
    0xDC,
    0x0A,
    0x21,
    0x00,
    0x12,
    0x08,
    0x00,
    0x00,
    0x10,
    0x01,
    0x00,
    0x00,
    0x14,
    0x06,
    0x40,
    0x50,
    0x10,
    0xC0,
    0x00,
    0x20,
    0x00,
    0x80,
    0x00,
    0x00,
    0x27,
    0x0D,
    0x00,
    0xFF,
    0xC1,
    0xC0,
    0x00,
    0x20,
    0x00,
    0x80,
    0x00,
    0x00,
    0x01,
    0x0D,
    0x00,
    0xF4,
    0x62,
    0xC0,
    0x00,
    0x20,
    0x00,
    0x80,
    0x00,
    0x00,
    0x00,
    0x0D,
    0x00,
    0xF4,
    0x62,
    0xC0,
    0x00,
    0x20,
    0x00,
    0x80,
    0x00,
    0x00,
    0x02,
    0x0D,
    0x00,
    0xFF,
    0xD1,
    0x00,
    0x00,
    0x00,
    0x03,
    0x0D,
    0x00,
    0xFF,
    0xD2,
    0x00,
    0x00,
    0x00,
    0x05,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x02,
    0x01,
    0x00,
    0x22,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x08,
    0x9E,
    0xDC,
    0xE0,
    0x08,
    0x9C,
    0x00,
    0x10,
    0x00,
    0x00,
    0x00,
    0x00,
    0xC0,
    0x00,
    0x00,
    0x00,
    0x82,
    0x4F,
    0x00,
    0x00,
    0x08,
    0x8A,
    0xDC,
    0xE0,
    0x0A,
    0x23,
    0x00,
    0x06,
    0x0A,
    0x2B,
    0x00,
    0x07,
    0x00,
    0x88,
    0x20,
    0x00,
    0x0A,
    0xA7,
    0x00,
    0x05,
    0x00,
    0x00,
    0x00,
    0x22,
    0xC0,
    0x00,
    0x2D,
    0x30,
    0x80,
    0x00,
    0x50,
    0x00,
    0x30,
    0x00,
    0xB4,
    0x6A,
    0x00,
    0x88,
    0x20,
    0x00,
    0xC0,
    0x00,
    0x28,
    0x70,
    0x80,
    0x00,
    0x60,
    0x00,
    0x02,
    0x09,
    0x00,
    0x47,
    0x00,
    0x8C,
    0x11,
    0x91,
    0x00,
    0x00,
    0x00,
    0x24,
    0x00,
    0x8C,
    0x2A,
    0x02,
    0x30,
    0x00,
    0xBC,
    0xE9,
    0x00,
    0x84,
    0x0D,
    0x9C,
    0x00,
    0x20,
    0x0B,
    0x2D,
    0x00,
    0x00,
    0xC2,
    0xF1,
    0x01,
    0x00,
    0x00,
    0x45,
    0x06,
    0x00,
    0x50,
    0x14,
    0x36,
    0x40,
    0x50,
    0x15,
    0x26,
    0x40,
    0x40,
    0x15,
    0x09,
    0x2B,
    0x00,
    0x06,
    0x09,
    0x2B,
    0x00,
    0x07,
    0x00,
    0x00,
    0x00,
    0x00,
    0x08,
    0x90,
    0x00,
    0x1B,
    0x0C,
    0x70,
    0x00,
    0x14,
    0x0E,
    0x3D,
    0x00,
    0x17,
    0x00,
    0xF4,
    0xAE,
    0x0F,
    0x0A,
    0x25,
    0xDC,
    0xDC,
    0x0A,
    0xE1,
    0x00,
    0x15,
    0x00,
    0x00,
    0xDC,
    0x70,
    0x00,
    0x00,
    0xA4,
    0xD8,
    0x00,
    0xD6,
    0x21,
    0x01,
    0x00,
    0x00,
    0xE0,
    0x29,
    0x07,
    0x05,
    0x88,
    0x08,
    0x00,
    0x84,
    0x19,
    0xB3,
    0x00,
    0x04,
    0x45,
    0x90,
    0x00,
    0x44,
    0x2C,
    0x30,
    0x00,
    0x04,
    0x49,
    0x28,
    0x00,
    0x94,
    0x08,
    0x87,
    0x0B,
    0xE1,
    0x00,
    0x15,
    0x05,
    0x4D,
    0x10,
    0x2E,
    0x0C,
    0x00,
    0xFC,
    0x40,
    0x06,
    0x40,
    0x10,
    0x0E,
    0x0C,
    0x00,
    0xFC,
    0x41,
    0x06,
    0x40,
    0x10,
    0x1E,
    0x0C,
    0x20,
    0x00,
    0x23,
    0x06,
    0x10,
    0x10,
    0x0E,
    0x06,
    0x10,
    0x90,
    0x1E,
    0x06,
    0x11,
    0x10,
    0x2E,
    0x00,
    0x06,
    0x40,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x05,
    0x4C,
    0x10,
    0x5E,
    0xC0,
    0x00,
    0x00,
    0x00,
    0x82,
    0x0E,
    0x00,
    0x06,
    0xC0,
    0x00,
    0x00,
    0x00,
    0x82,
    0x1F,
    0x00,
    0x1E,
    0x06,
    0x08,
    0x10,
    0x3E,
    0x06,
    0x18,
    0x40,
    0x31,
    0xF1,
    0x6C,
    0x80,
    0x01,
    0x88,
    0x00,
    0x01,
    0x22,
    0xFC,
    0x6C,
    0x80,
    0x21,
    0x81,
    0x82,
    0x04,
    0x23,
    0x00,
    0x84,
    0x00,
    0x08,
    0x05,
    0x4C,
    0x50,
    0x00,
    0x06,
    0x00,
    0x10,
    0x8E,
    0x0D,
    0x00,
    0xFC,
    0xE0,
    0x0C,
    0x40,
    0x00,
    0x26,
    0x06,
    0x00,
    0x10,
    0x8E,
    0x00,
    0x04,
    0x00,
    0x80,
    0x00,
    0x00,
    0x00,
    0x00,
    0x05,
    0x4C,
    0x10,
    0x9E,
    0x06,
    0x00,
    0x10,
    0x9E,
    0x0D,
    0x00,
    0xFC,
    0xE1,
    0x06,
    0x00,
    0x10,
    0x8E,
    0x0D,
    0x00,
    0xFC,
    0xE8,
    0x06,
    0x00,
    0x10,
    0x8E,
    0x0D,
    0x00,
    0xFC,
    0xE9,
    0x08,
    0x9C,
    0x00,
    0x10,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x2E,
    0x01,
    0x00,
    0x00,
    0x00,
    0x00,
    0x09,
    0x9C,
    0x00,
    0x10,
    0x00,
    0x00,
    0x00,
    0x02,
    0x0C,
    0x10,
    0xF4,
    0x60,
    0x02,
    0xC2,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
};

/* DSP Parameter (Coefficient) Data */
#define DM0_DATA_SIZE_IC_1 172
#define DM0_DATA_ADDR_IC_1 0
ADI_REG_TYPE DM0_DATA_IC_1_Data[DM0_DATA_SIZE_IC_1] = {
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x08,
    0x00,
    0x00,
    0x00,
    0x08,
    0x00,
    0x00,
    0x00,
    0x0C,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0xB5,
    0x3B,
    0xEF,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x07,
    0xFF,
    0xFF,
    0xFF,
    0xFF,
    0xFF,
    0x00,
    0x05,
    0x55,
    0x55,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0xC0,
    0x00,
    0x00,
    0x00,
    0xC0,
    0x00,
    0x00,
    0x00,
    0x08,
    0x00,
    0x00,
    0xDB,
    0x12,
    0xE7,
    0xFE,
    0x28,
    0xFD,
    0x91,
    0x01,
    0x00,
    0x00,
    0x00,
    0xFF,
    0x24,
    0xED,
    0x19,
    0x01,
    0xD7,
    0x02,
    0x6F,
    0x00,
    0x55,
    0x55,
    0x55,
    0x00,
    0x55,
    0x55,
    0x55,
    0x00,
    0x55,
    0x55,
    0x55,
    0xFF,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
};

/* Register Default - SOFT_RESET */
#define R0_SOFT_RESET_SIZE_IC_1 2
#define R0_SOFT_RESET_ADDR_IC_1 63632
ADI_REG_TYPE R0_SOFT_RESET_IC_1_Data[R0_SOFT_RESET_SIZE_IC_1] = {
    0x00,
    0x00,
};

/* Register Default - SOFT_RESET */
#define R1_SOFT_RESET_SIZE_IC_1 2
#define R1_SOFT_RESET_ADDR_IC_1 63632
ADI_REG_TYPE R1_SOFT_RESET_IC_1_Data[R1_SOFT_RESET_SIZE_IC_1] = {
    0x00,
    0x01,
};

/* Register Default - Reset Delay */
#define R2_RESET_DELAY_SIZE_IC_1 2
#define R2_RESET_DELAY_ADDR_IC_1 0
ADI_REG_TYPE R2_RESET_DELAY_IC_1_Data[R2_RESET_DELAY_SIZE_IC_1] = {
    0x00,
    0xFF,
};

/* Register Default - HIBERNATE */
#define R3_HIBERNATE_SIZE_IC_1 2
#define R3_HIBERNATE_ADDR_IC_1 62464
ADI_REG_TYPE R3_HIBERNATE_IC_1_Data[R3_HIBERNATE_SIZE_IC_1] = {
    0x00,
    0x00,
};

/* Register Default - HIBERNATE */
#define R4_HIBERNATE_SIZE_IC_1 2
#define R4_HIBERNATE_ADDR_IC_1 62464
ADI_REG_TYPE R4_HIBERNATE_IC_1_Data[R4_HIBERNATE_SIZE_IC_1] = {
    0x00,
    0x01,
};

/* Register Default - Hibernate Delay */
#define R5_HIBERNATE_DELAY_SIZE_IC_1 2
#define R5_HIBERNATE_DELAY_ADDR_IC_1 0
ADI_REG_TYPE R5_HIBERNATE_DELAY_IC_1_Data[R5_HIBERNATE_DELAY_SIZE_IC_1] = {
    0x00,
    0xFF,
};

/* Register Default - KILL_CORE */
#define R6_KILL_CORE_SIZE_IC_1 2
#define R6_KILL_CORE_ADDR_IC_1 62467
ADI_REG_TYPE R6_KILL_CORE_IC_1_Data[R6_KILL_CORE_SIZE_IC_1] = {
    0x00,
    0x00,
};

/* Register Default - KILL_CORE */
#define R7_KILL_CORE_SIZE_IC_1 2
#define R7_KILL_CORE_ADDR_IC_1 62467
ADI_REG_TYPE R7_KILL_CORE_IC_1_Data[R7_KILL_CORE_SIZE_IC_1] = {
    0x00,
    0x01,
};

/* Register Default - PLL_ENABLE */
#define R8_PLL_ENABLE_SIZE_IC_1 2
#define R8_PLL_ENABLE_ADDR_IC_1 61443
ADI_REG_TYPE R8_PLL_ENABLE_IC_1_Data[R8_PLL_ENABLE_SIZE_IC_1] = {
    0x00,
    0x00,
};

/* Register Default - PLL_CTRL1 Register */
#define R9_PLL_CTRL1_REGISTER_SIZE_IC_1 2
#define R9_PLL_CTRL1_REGISTER_ADDR_IC_1 61441
ADI_REG_TYPE R9_PLL_CTRL1_REGISTER_IC_1_Data[R9_PLL_CTRL1_REGISTER_SIZE_IC_1] = {
    0x00,
    0x02,
};

/* Register Default - PLL_CLK_SRC Register */
#define R10_PLL_CLK_SRC_REGISTER_SIZE_IC_1 2
#define R10_PLL_CLK_SRC_REGISTER_ADDR_IC_1 61442
ADI_REG_TYPE R10_PLL_CLK_SRC_REGISTER_IC_1_Data[R10_PLL_CLK_SRC_REGISTER_SIZE_IC_1] = {
    0x00,
    0x01,
};

/* Register Default - MCLK_OUT Register */
#define R11_MCLK_OUT_REGISTER_SIZE_IC_1 2
#define R11_MCLK_OUT_REGISTER_ADDR_IC_1 61445
ADI_REG_TYPE R11_MCLK_OUT_REGISTER_IC_1_Data[R11_MCLK_OUT_REGISTER_SIZE_IC_1] = {
    0x00,
    0x07,
};

/* Register Default - PLL_ENABLE Register */
#define R12_PLL_ENABLE_REGISTER_SIZE_IC_1 2
#define R12_PLL_ENABLE_REGISTER_ADDR_IC_1 61443
ADI_REG_TYPE R12_PLL_ENABLE_REGISTER_IC_1_Data[R12_PLL_ENABLE_REGISTER_SIZE_IC_1] = {
    0x00,
    0x01,
};

/* Register Default - PLL Lock Delay */
#define R13_PLL_LOCK_DELAY_SIZE_IC_1 2
#define R13_PLL_LOCK_DELAY_ADDR_IC_1 0
ADI_REG_TYPE R13_PLL_LOCK_DELAY_IC_1_Data[R13_PLL_LOCK_DELAY_SIZE_IC_1] = {
    0x00,
    0xFF,
};

/* Register Default - POWER_ENABLE0 Register */
#define R14_POWER_ENABLE0_REGISTER_SIZE_IC_1 2
#define R14_POWER_ENABLE0_REGISTER_ADDR_IC_1 61520
ADI_REG_TYPE R14_POWER_ENABLE0_REGISTER_IC_1_Data[R14_POWER_ENABLE0_REGISTER_SIZE_IC_1] = {
    0x1C,
    0xC1,
};

/* Register Default - POWER_ENABLE1 Register */
#define R15_POWER_ENABLE1_REGISTER_SIZE_IC_1 2
#define R15_POWER_ENABLE1_REGISTER_ADDR_IC_1 61521
ADI_REG_TYPE R15_POWER_ENABLE1_REGISTER_IC_1_Data[R15_POWER_ENABLE1_REGISTER_SIZE_IC_1] = {
    0x00,
    0x00,
};

/* Register Default - MP0_MODE */
#define R16_MP0_MODE_SIZE_IC_1 2
#define R16_MP0_MODE_ADDR_IC_1 62736
ADI_REG_TYPE R16_MP0_MODE_IC_1_Data[R16_MP0_MODE_SIZE_IC_1] = {
    0x00,
    0x05,
};

/* Register Default - MP1_MODE */
#define R17_MP1_MODE_SIZE_IC_1 2
#define R17_MP1_MODE_ADDR_IC_1 62737
ADI_REG_TYPE R17_MP1_MODE_IC_1_Data[R17_MP1_MODE_SIZE_IC_1] = {
    0x00,
    0x05,
};

/* Register Default - MP2_MODE */
#define R18_MP2_MODE_SIZE_IC_1 2
#define R18_MP2_MODE_ADDR_IC_1 62738
ADI_REG_TYPE R18_MP2_MODE_IC_1_Data[R18_MP2_MODE_SIZE_IC_1] = {
    0x00,
    0x05,
};

/* Register Default - MP3_MODE */
#define R19_MP3_MODE_SIZE_IC_1 2
#define R19_MP3_MODE_ADDR_IC_1 62739
ADI_REG_TYPE R19_MP3_MODE_IC_1_Data[R19_MP3_MODE_SIZE_IC_1] = {
    0x00,
    0x01,
};

/* Register Default - MP4_MODE */
#define R20_MP4_MODE_SIZE_IC_1 2
#define R20_MP4_MODE_ADDR_IC_1 62740
ADI_REG_TYPE R20_MP4_MODE_IC_1_Data[R20_MP4_MODE_SIZE_IC_1] = {
    0x00,
    0x05,
};

/* Register Default - MP5_MODE */
#define R21_MP5_MODE_SIZE_IC_1 2
#define R21_MP5_MODE_ADDR_IC_1 62741
ADI_REG_TYPE R21_MP5_MODE_IC_1_Data[R21_MP5_MODE_SIZE_IC_1] = {
    0x00,
    0x05,
};

/* Register Default - MP6_MODE */
#define R22_MP6_MODE_SIZE_IC_1 2
#define R22_MP6_MODE_ADDR_IC_1 62742
ADI_REG_TYPE R22_MP6_MODE_IC_1_Data[R22_MP6_MODE_SIZE_IC_1] = {
    0x00,
    0x05,
};

/* Register Default - MP7_MODE */
#define R23_MP7_MODE_SIZE_IC_1 2
#define R23_MP7_MODE_ADDR_IC_1 62743
ADI_REG_TYPE R23_MP7_MODE_IC_1_Data[R23_MP7_MODE_SIZE_IC_1] = {
    0x00,
    0x05,
};

/* Register Default - MP11_MODE */
#define R24_MP11_MODE_SIZE_IC_1 2
#define R24_MP11_MODE_ADDR_IC_1 62747
ADI_REG_TYPE R24_MP11_MODE_IC_1_Data[R24_MP11_MODE_SIZE_IC_1] = {
    0x00,
    0x07,
};

/* Register Default - MP12_MODE */
#define R25_MP12_MODE_SIZE_IC_1 2
#define R25_MP12_MODE_ADDR_IC_1 62748
ADI_REG_TYPE R25_MP12_MODE_IC_1_Data[R25_MP12_MODE_SIZE_IC_1] = {
    0x00,
    0x05,
};

/* Register Default - MP13_MODE */
#define R26_MP13_MODE_SIZE_IC_1 2
#define R26_MP13_MODE_ADDR_IC_1 62749
ADI_REG_TYPE R26_MP13_MODE_IC_1_Data[R26_MP13_MODE_SIZE_IC_1] = {
    0x00,
    0x07,
};

/* Register Default - MP0_WRITE */
#define R27_MP0_WRITE_SIZE_IC_1 2
#define R27_MP0_WRITE_ADDR_IC_1 62752
ADI_REG_TYPE R27_MP0_WRITE_IC_1_Data[R27_MP0_WRITE_SIZE_IC_1] = {
    0x00,
    0x01,
};

/* Register Default - MP1_WRITE */
#define R28_MP1_WRITE_SIZE_IC_1 2
#define R28_MP1_WRITE_ADDR_IC_1 62753
ADI_REG_TYPE R28_MP1_WRITE_IC_1_Data[R28_MP1_WRITE_SIZE_IC_1] = {
    0x00,
    0x01,
};

/* Register Default - MP2_WRITE */
#define R29_MP2_WRITE_SIZE_IC_1 2
#define R29_MP2_WRITE_ADDR_IC_1 62754
ADI_REG_TYPE R29_MP2_WRITE_IC_1_Data[R29_MP2_WRITE_SIZE_IC_1] = {
    0x00,
    0x01,
};

/* Register Default - MP4_WRITE */
#define R30_MP4_WRITE_SIZE_IC_1 2
#define R30_MP4_WRITE_ADDR_IC_1 62756
ADI_REG_TYPE R30_MP4_WRITE_IC_1_Data[R30_MP4_WRITE_SIZE_IC_1] = {
    0x00,
    0x01,
};

/* Register Default - MP5_WRITE */
#define R31_MP5_WRITE_SIZE_IC_1 2
#define R31_MP5_WRITE_ADDR_IC_1 62757
ADI_REG_TYPE R31_MP5_WRITE_IC_1_Data[R31_MP5_WRITE_SIZE_IC_1] = {
    0x00,
    0x01,
};

/* Register Default - MP6_WRITE */
#define R32_MP6_WRITE_SIZE_IC_1 2
#define R32_MP6_WRITE_ADDR_IC_1 62758
ADI_REG_TYPE R32_MP6_WRITE_IC_1_Data[R32_MP6_WRITE_SIZE_IC_1] = {
    0x00,
    0x01,
};

/* Register Default - MP7_WRITE */
#define R33_MP7_WRITE_SIZE_IC_1 2
#define R33_MP7_WRITE_ADDR_IC_1 62759
ADI_REG_TYPE R33_MP7_WRITE_IC_1_Data[R33_MP7_WRITE_SIZE_IC_1] = {
    0x00,
    0x01,
};

/* Register Default - MP11_WRITE */
#define R34_MP11_WRITE_SIZE_IC_1 2
#define R34_MP11_WRITE_ADDR_IC_1 62763
ADI_REG_TYPE R34_MP11_WRITE_IC_1_Data[R34_MP11_WRITE_SIZE_IC_1] = {
    0x00,
    0x01,
};

/* Register Default - MP12_WRITE */
#define R35_MP12_WRITE_SIZE_IC_1 2
#define R35_MP12_WRITE_ADDR_IC_1 62764
ADI_REG_TYPE R35_MP12_WRITE_IC_1_Data[R35_MP12_WRITE_SIZE_IC_1] = {
    0x00,
    0x01,
};

/* Register Default - MP13_WRITE */
#define R36_MP13_WRITE_SIZE_IC_1 2
#define R36_MP13_WRITE_ADDR_IC_1 62765
ADI_REG_TYPE R36_MP13_WRITE_IC_1_Data[R36_MP13_WRITE_SIZE_IC_1] = {
    0x00,
    0x01,
};

/* Register Default - BCLK_IN0_PIN */
#define R37_BCLK_IN0_PIN_SIZE_IC_1 2
#define R37_BCLK_IN0_PIN_ADDR_IC_1 63360
ADI_REG_TYPE R37_BCLK_IN0_PIN_IC_1_Data[R37_BCLK_IN0_PIN_SIZE_IC_1] = {
    0x00,
    0x19,
};

/* Register Default - BCLK_OUT0_PIN */
#define R38_BCLK_OUT0_PIN_SIZE_IC_1 2
#define R38_BCLK_OUT0_PIN_ADDR_IC_1 63364
ADI_REG_TYPE R38_BCLK_OUT0_PIN_IC_1_Data[R38_BCLK_OUT0_PIN_SIZE_IC_1] = {
    0x00,
    0x19,
};

/* Register Default - LRCLK_IN0_PIN */
#define R39_LRCLK_IN0_PIN_SIZE_IC_1 2
#define R39_LRCLK_IN0_PIN_ADDR_IC_1 63368
ADI_REG_TYPE R39_LRCLK_IN0_PIN_IC_1_Data[R39_LRCLK_IN0_PIN_SIZE_IC_1] = {
    0x00,
    0x19,
};

/* Register Default - LRCLK_OUT0_PIN */
#define R40_LRCLK_OUT0_PIN_SIZE_IC_1 2
#define R40_LRCLK_OUT0_PIN_ADDR_IC_1 63372
ADI_REG_TYPE R40_LRCLK_OUT0_PIN_IC_1_Data[R40_LRCLK_OUT0_PIN_SIZE_IC_1] = {
    0x00,
    0x19,
};

/* Register Default - SDATA_IN0_PIN */
#define R41_SDATA_IN0_PIN_SIZE_IC_1 2
#define R41_SDATA_IN0_PIN_ADDR_IC_1 63376
ADI_REG_TYPE R41_SDATA_IN0_PIN_IC_1_Data[R41_SDATA_IN0_PIN_SIZE_IC_1] = {
    0x00,
    0x19,
};

/* Register Default - SDATA_OUT0_PIN */
#define R42_SDATA_OUT0_PIN_SIZE_IC_1 2
#define R42_SDATA_OUT0_PIN_ADDR_IC_1 63380
ADI_REG_TYPE R42_SDATA_OUT0_PIN_IC_1_Data[R42_SDATA_OUT0_PIN_SIZE_IC_1] = {
    0x00,
    0x09,
};

/* Register Default - SCLK_SCL_PIN */
#define R43_SCLK_SCL_PIN_SIZE_IC_1 2
#define R43_SCLK_SCL_PIN_ADDR_IC_1 63385
ADI_REG_TYPE R43_SCLK_SCL_PIN_IC_1_Data[R43_SCLK_SCL_PIN_SIZE_IC_1] = {
    0x00,
    0x09,
};

/* Register Default - MISO_SDA_PIN */
#define R44_MISO_SDA_PIN_SIZE_IC_1 2
#define R44_MISO_SDA_PIN_ADDR_IC_1 63386
ADI_REG_TYPE R44_MISO_SDA_PIN_IC_1_Data[R44_MISO_SDA_PIN_SIZE_IC_1] = {
    0x00,
    0x09,
};

/* Register Default - CLKOUT_PIN */
#define R45_CLKOUT_PIN_SIZE_IC_1 2
#define R45_CLKOUT_PIN_ADDR_IC_1 63395
ADI_REG_TYPE R45_CLKOUT_PIN_IC_1_Data[R45_CLKOUT_PIN_SIZE_IC_1] = {
    0x00,
    0x0F,
};

/* Register Default - SOUT_SOURCE16 */
#define R46_SOUT_SOURCE16_SIZE_IC_1 2
#define R46_SOUT_SOURCE16_ADDR_IC_1 61840
ADI_REG_TYPE R46_SOUT_SOURCE16_IC_1_Data[R46_SOUT_SOURCE16_SIZE_IC_1] = {
    0x00,
    0x02,
};

/* Register Default - SOUT_SOURCE20 */
#define R47_SOUT_SOURCE20_SIZE_IC_1 2
#define R47_SOUT_SOURCE20_ADDR_IC_1 61844
ADI_REG_TYPE R47_SOUT_SOURCE20_IC_1_Data[R47_SOUT_SOURCE20_SIZE_IC_1] = {
    0x00,
    0x02,
};

/* Register Default - SERIAL_BYTE_0_0 */
#define R48_SERIAL_BYTE_0_0_SIZE_IC_1 2
#define R48_SERIAL_BYTE_0_0_ADDR_IC_1 61952
ADI_REG_TYPE R48_SERIAL_BYTE_0_0_IC_1_Data[R48_SERIAL_BYTE_0_0_SIZE_IC_1] = {
    0x91,
    0x40,
};

/* Register Default - SERIAL_BYTE_1_0 */
#define R49_SERIAL_BYTE_1_0_SIZE_IC_1 2
#define R49_SERIAL_BYTE_1_0_ADDR_IC_1 61956
ADI_REG_TYPE R49_SERIAL_BYTE_1_0_IC_1_Data[R49_SERIAL_BYTE_1_0_SIZE_IC_1] = {
    0x90,
    0x00,
};

/* Register Default - SERIAL_BYTE_1_1 */
#define R50_SERIAL_BYTE_1_1_SIZE_IC_1 2
#define R50_SERIAL_BYTE_1_1_ADDR_IC_1 61957
ADI_REG_TYPE R50_SERIAL_BYTE_1_1_IC_1_Data[R50_SERIAL_BYTE_1_1_SIZE_IC_1] = {
    0x00,
    0x1A,
};

/* Register Default - SERIAL_BYTE_2_0 */
#define R51_SERIAL_BYTE_2_0_SIZE_IC_1 2
#define R51_SERIAL_BYTE_2_0_ADDR_IC_1 61960
ADI_REG_TYPE R51_SERIAL_BYTE_2_0_IC_1_Data[R51_SERIAL_BYTE_2_0_SIZE_IC_1] = {
    0x90,
    0x00,
};

/* Register Default - SERIAL_BYTE_2_1 */
#define R52_SERIAL_BYTE_2_1_SIZE_IC_1 2
#define R52_SERIAL_BYTE_2_1_ADDR_IC_1 61961
ADI_REG_TYPE R52_SERIAL_BYTE_2_1_IC_1_Data[R52_SERIAL_BYTE_2_1_SIZE_IC_1] = {
    0x00,
    0x1A,
};

/* Register Default - SERIAL_BYTE_3_0 */
#define R53_SERIAL_BYTE_3_0_SIZE_IC_1 2
#define R53_SERIAL_BYTE_3_0_ADDR_IC_1 61964
ADI_REG_TYPE R53_SERIAL_BYTE_3_0_IC_1_Data[R53_SERIAL_BYTE_3_0_SIZE_IC_1] = {
    0x90,
    0x00,
};

/* Register Default - SERIAL_BYTE_3_1 */
#define R54_SERIAL_BYTE_3_1_SIZE_IC_1 2
#define R54_SERIAL_BYTE_3_1_ADDR_IC_1 61965
ADI_REG_TYPE R54_SERIAL_BYTE_3_1_IC_1_Data[R54_SERIAL_BYTE_3_1_SIZE_IC_1] = {
    0x00,
    0x1A,
};

/* Register Default - SERIAL_BYTE_4_0 */
#define R55_SERIAL_BYTE_4_0_SIZE_IC_1 2
#define R55_SERIAL_BYTE_4_0_ADDR_IC_1 61968
ADI_REG_TYPE R55_SERIAL_BYTE_4_0_IC_1_Data[R55_SERIAL_BYTE_4_0_SIZE_IC_1] = {
    0x90,
    0x00,
};

/* Register Default - SERIAL_BYTE_4_1 */
#define R56_SERIAL_BYTE_4_1_SIZE_IC_1 2
#define R56_SERIAL_BYTE_4_1_ADDR_IC_1 61969
ADI_REG_TYPE R56_SERIAL_BYTE_4_1_IC_1_Data[R56_SERIAL_BYTE_4_1_SIZE_IC_1] = {
    0x00,
    0x1A,
};

/* Register Default - SERIAL_BYTE_5_0 */
#define R57_SERIAL_BYTE_5_0_SIZE_IC_1 2
#define R57_SERIAL_BYTE_5_0_ADDR_IC_1 61972
ADI_REG_TYPE R57_SERIAL_BYTE_5_0_IC_1_Data[R57_SERIAL_BYTE_5_0_SIZE_IC_1] = {
    0x90,
    0x00,
};

/* Register Default - SERIAL_BYTE_5_1 */
#define R58_SERIAL_BYTE_5_1_SIZE_IC_1 2
#define R58_SERIAL_BYTE_5_1_ADDR_IC_1 61973
ADI_REG_TYPE R58_SERIAL_BYTE_5_1_IC_1_Data[R58_SERIAL_BYTE_5_1_SIZE_IC_1] = {
    0x00,
    0x1A,
};

/* Register Default - SERIAL_BYTE_6_0 */
#define R59_SERIAL_BYTE_6_0_SIZE_IC_1 2
#define R59_SERIAL_BYTE_6_0_ADDR_IC_1 61976
ADI_REG_TYPE R59_SERIAL_BYTE_6_0_IC_1_Data[R59_SERIAL_BYTE_6_0_SIZE_IC_1] = {
    0x90,
    0xC0,
};

/* Register Default - SERIAL_BYTE_7_0 */
#define R60_SERIAL_BYTE_7_0_SIZE_IC_1 2
#define R60_SERIAL_BYTE_7_0_ADDR_IC_1 61980
ADI_REG_TYPE R60_SERIAL_BYTE_7_0_IC_1_Data[R60_SERIAL_BYTE_7_0_SIZE_IC_1] = {
    0x90,
    0xC0,
};

/* Register Default - SPDIF_RX_CTRL */
#define R61_SPDIF_RX_CTRL_SIZE_IC_1 2
#define R61_SPDIF_RX_CTRL_ADDR_IC_1 62977
ADI_REG_TYPE R61_SPDIF_RX_CTRL_IC_1_Data[R61_SPDIF_RX_CTRL_SIZE_IC_1] = {
    0x00,
    0x08,
};

/* Register Default - SPDIF_TX_EN */
#define R62_SPDIF_TX_EN_SIZE_IC_1 2
#define R62_SPDIF_TX_EN_ADDR_IC_1 63120
ADI_REG_TYPE R62_SPDIF_TX_EN_IC_1_Data[R62_SPDIF_TX_EN_SIZE_IC_1] = {
    0x00,
    0x01,
};

/* Register Default - KILL_CORE */
#define R66_KILL_CORE_SIZE_IC_1 2
#define R66_KILL_CORE_ADDR_IC_1 62467
ADI_REG_TYPE R66_KILL_CORE_IC_1_Data[R66_KILL_CORE_SIZE_IC_1] = {
    0x00,
    0x00,
};

/* Register Default - START_ADDRESS */
#define R67_START_ADDRESS_SIZE_IC_1 2
#define R67_START_ADDRESS_ADDR_IC_1 62468
ADI_REG_TYPE R67_START_ADDRESS_IC_1_Data[R67_START_ADDRESS_SIZE_IC_1] = {
    0x00,
    0x00,
};

/* Register Default - START_PULSE */
#define R68_START_PULSE_SIZE_IC_1 2
#define R68_START_PULSE_ADDR_IC_1 62465
ADI_REG_TYPE R68_START_PULSE_IC_1_Data[R68_START_PULSE_SIZE_IC_1] = {
    0x00,
    0x02,
};

/* Register Default - START_CORE */
#define R69_START_CORE_SIZE_IC_1 2
#define R69_START_CORE_ADDR_IC_1 62466
ADI_REG_TYPE R69_START_CORE_IC_1_Data[R69_START_CORE_SIZE_IC_1] = {
    0x00,
    0x00,
};

/* Register Default - START_CORE */
#define R70_START_CORE_SIZE_IC_1 2
#define R70_START_CORE_ADDR_IC_1 62466
ADI_REG_TYPE R70_START_CORE_IC_1_Data[R70_START_CORE_SIZE_IC_1] = {
    0x00,
    0x01,
};

/* Register Default - Start Delay */
#define R71_START_DELAY_SIZE_IC_1 2
#define R71_START_DELAY_ADDR_IC_1 0
ADI_REG_TYPE R71_START_DELAY_IC_1_Data[R71_START_DELAY_SIZE_IC_1] = {
    0x00,
    0x01,
};

/* Register Default - HIBERNATE */
#define R72_HIBERNATE_SIZE_IC_1 2
#define R72_HIBERNATE_ADDR_IC_1 62464
ADI_REG_TYPE R72_HIBERNATE_IC_1_Data[R72_HIBERNATE_SIZE_IC_1] = {
    0x00,
    0x00,
};

/* Default Download */
#define DEFAULT_DOWNLOAD_SIZE_IC_1 73

void default_download_IC_1() {
    SIGMA_WRITE_REGISTER_BLOCK(DEVICE_ADDR_IC_1, R0_SOFT_RESET_ADDR_IC_1, R0_SOFT_RESET_SIZE_IC_1, R0_SOFT_RESET_IC_1_Data);
    SIGMA_WRITE_REGISTER_BLOCK(DEVICE_ADDR_IC_1, R1_SOFT_RESET_ADDR_IC_1, R1_SOFT_RESET_SIZE_IC_1, R1_SOFT_RESET_IC_1_Data);
    SIGMA_WRITE_DELAY(DEVICE_ADDR_IC_1, R2_RESET_DELAY_ADDR_IC_1, R2_RESET_DELAY_SIZE_IC_1, R2_RESET_DELAY_IC_1_Data);
    SIGMA_WRITE_REGISTER_BLOCK(DEVICE_ADDR_IC_1, R3_HIBERNATE_ADDR_IC_1, R3_HIBERNATE_SIZE_IC_1, R3_HIBERNATE_IC_1_Data);
    SIGMA_WRITE_REGISTER_BLOCK(DEVICE_ADDR_IC_1, R4_HIBERNATE_ADDR_IC_1, R4_HIBERNATE_SIZE_IC_1, R4_HIBERNATE_IC_1_Data);
    SIGMA_WRITE_DELAY(DEVICE_ADDR_IC_1, R5_HIBERNATE_DELAY_ADDR_IC_1, R5_HIBERNATE_DELAY_SIZE_IC_1, R5_HIBERNATE_DELAY_IC_1_Data);
    SIGMA_WRITE_REGISTER_BLOCK(DEVICE_ADDR_IC_1, R6_KILL_CORE_ADDR_IC_1, R6_KILL_CORE_SIZE_IC_1, R6_KILL_CORE_IC_1_Data);
    SIGMA_WRITE_REGISTER_BLOCK(DEVICE_ADDR_IC_1, R7_KILL_CORE_ADDR_IC_1, R7_KILL_CORE_SIZE_IC_1, R7_KILL_CORE_IC_1_Data);
    SIGMA_WRITE_REGISTER_BLOCK(DEVICE_ADDR_IC_1, R8_PLL_ENABLE_ADDR_IC_1, R8_PLL_ENABLE_SIZE_IC_1, R8_PLL_ENABLE_IC_1_Data);
    SIGMA_WRITE_REGISTER_BLOCK(DEVICE_ADDR_IC_1, R9_PLL_CTRL1_REGISTER_ADDR_IC_1, R9_PLL_CTRL1_REGISTER_SIZE_IC_1, R9_PLL_CTRL1_REGISTER_IC_1_Data);
    SIGMA_WRITE_REGISTER_BLOCK(DEVICE_ADDR_IC_1, R10_PLL_CLK_SRC_REGISTER_ADDR_IC_1, R10_PLL_CLK_SRC_REGISTER_SIZE_IC_1, R10_PLL_CLK_SRC_REGISTER_IC_1_Data);
    SIGMA_WRITE_REGISTER_BLOCK(DEVICE_ADDR_IC_1, R11_MCLK_OUT_REGISTER_ADDR_IC_1, R11_MCLK_OUT_REGISTER_SIZE_IC_1, R11_MCLK_OUT_REGISTER_IC_1_Data);
    SIGMA_WRITE_REGISTER_BLOCK(DEVICE_ADDR_IC_1, R12_PLL_ENABLE_REGISTER_ADDR_IC_1, R12_PLL_ENABLE_REGISTER_SIZE_IC_1, R12_PLL_ENABLE_REGISTER_IC_1_Data);
    SIGMA_WRITE_DELAY(DEVICE_ADDR_IC_1, R13_PLL_LOCK_DELAY_ADDR_IC_1, R13_PLL_LOCK_DELAY_SIZE_IC_1, R13_PLL_LOCK_DELAY_IC_1_Data);
    SIGMA_WRITE_REGISTER_BLOCK(DEVICE_ADDR_IC_1, R14_POWER_ENABLE0_REGISTER_ADDR_IC_1, R14_POWER_ENABLE0_REGISTER_SIZE_IC_1, R14_POWER_ENABLE0_REGISTER_IC_1_Data);
    SIGMA_WRITE_REGISTER_BLOCK(DEVICE_ADDR_IC_1, R15_POWER_ENABLE1_REGISTER_ADDR_IC_1, R15_POWER_ENABLE1_REGISTER_SIZE_IC_1, R15_POWER_ENABLE1_REGISTER_IC_1_Data);
    SIGMA_WRITE_REGISTER_BLOCK(DEVICE_ADDR_IC_1, R16_MP0_MODE_ADDR_IC_1, R16_MP0_MODE_SIZE_IC_1, R16_MP0_MODE_IC_1_Data);
    SIGMA_WRITE_REGISTER_BLOCK(DEVICE_ADDR_IC_1, R17_MP1_MODE_ADDR_IC_1, R17_MP1_MODE_SIZE_IC_1, R17_MP1_MODE_IC_1_Data);
    SIGMA_WRITE_REGISTER_BLOCK(DEVICE_ADDR_IC_1, R18_MP2_MODE_ADDR_IC_1, R18_MP2_MODE_SIZE_IC_1, R18_MP2_MODE_IC_1_Data);
    SIGMA_WRITE_REGISTER_BLOCK(DEVICE_ADDR_IC_1, R19_MP3_MODE_ADDR_IC_1, R19_MP3_MODE_SIZE_IC_1, R19_MP3_MODE_IC_1_Data);
    SIGMA_WRITE_REGISTER_BLOCK(DEVICE_ADDR_IC_1, R20_MP4_MODE_ADDR_IC_1, R20_MP4_MODE_SIZE_IC_1, R20_MP4_MODE_IC_1_Data);
    SIGMA_WRITE_REGISTER_BLOCK(DEVICE_ADDR_IC_1, R21_MP5_MODE_ADDR_IC_1, R21_MP5_MODE_SIZE_IC_1, R21_MP5_MODE_IC_1_Data);
    SIGMA_WRITE_REGISTER_BLOCK(DEVICE_ADDR_IC_1, R22_MP6_MODE_ADDR_IC_1, R22_MP6_MODE_SIZE_IC_1, R22_MP6_MODE_IC_1_Data);
    SIGMA_WRITE_REGISTER_BLOCK(DEVICE_ADDR_IC_1, R23_MP7_MODE_ADDR_IC_1, R23_MP7_MODE_SIZE_IC_1, R23_MP7_MODE_IC_1_Data);
    SIGMA_WRITE_REGISTER_BLOCK(DEVICE_ADDR_IC_1, R24_MP11_MODE_ADDR_IC_1, R24_MP11_MODE_SIZE_IC_1, R24_MP11_MODE_IC_1_Data);
    SIGMA_WRITE_REGISTER_BLOCK(DEVICE_ADDR_IC_1, R25_MP12_MODE_ADDR_IC_1, R25_MP12_MODE_SIZE_IC_1, R25_MP12_MODE_IC_1_Data);
    SIGMA_WRITE_REGISTER_BLOCK(DEVICE_ADDR_IC_1, R26_MP13_MODE_ADDR_IC_1, R26_MP13_MODE_SIZE_IC_1, R26_MP13_MODE_IC_1_Data);
    SIGMA_WRITE_REGISTER_BLOCK(DEVICE_ADDR_IC_1, R27_MP0_WRITE_ADDR_IC_1, R27_MP0_WRITE_SIZE_IC_1, R27_MP0_WRITE_IC_1_Data);
    SIGMA_WRITE_REGISTER_BLOCK(DEVICE_ADDR_IC_1, R28_MP1_WRITE_ADDR_IC_1, R28_MP1_WRITE_SIZE_IC_1, R28_MP1_WRITE_IC_1_Data);
    SIGMA_WRITE_REGISTER_BLOCK(DEVICE_ADDR_IC_1, R29_MP2_WRITE_ADDR_IC_1, R29_MP2_WRITE_SIZE_IC_1, R29_MP2_WRITE_IC_1_Data);
    SIGMA_WRITE_REGISTER_BLOCK(DEVICE_ADDR_IC_1, R30_MP4_WRITE_ADDR_IC_1, R30_MP4_WRITE_SIZE_IC_1, R30_MP4_WRITE_IC_1_Data);
    SIGMA_WRITE_REGISTER_BLOCK(DEVICE_ADDR_IC_1, R31_MP5_WRITE_ADDR_IC_1, R31_MP5_WRITE_SIZE_IC_1, R31_MP5_WRITE_IC_1_Data);
    SIGMA_WRITE_REGISTER_BLOCK(DEVICE_ADDR_IC_1, R32_MP6_WRITE_ADDR_IC_1, R32_MP6_WRITE_SIZE_IC_1, R32_MP6_WRITE_IC_1_Data);
    SIGMA_WRITE_REGISTER_BLOCK(DEVICE_ADDR_IC_1, R33_MP7_WRITE_ADDR_IC_1, R33_MP7_WRITE_SIZE_IC_1, R33_MP7_WRITE_IC_1_Data);
    SIGMA_WRITE_REGISTER_BLOCK(DEVICE_ADDR_IC_1, R34_MP11_WRITE_ADDR_IC_1, R34_MP11_WRITE_SIZE_IC_1, R34_MP11_WRITE_IC_1_Data);
    SIGMA_WRITE_REGISTER_BLOCK(DEVICE_ADDR_IC_1, R35_MP12_WRITE_ADDR_IC_1, R35_MP12_WRITE_SIZE_IC_1, R35_MP12_WRITE_IC_1_Data);
    SIGMA_WRITE_REGISTER_BLOCK(DEVICE_ADDR_IC_1, R36_MP13_WRITE_ADDR_IC_1, R36_MP13_WRITE_SIZE_IC_1, R36_MP13_WRITE_IC_1_Data);
    SIGMA_WRITE_REGISTER_BLOCK(DEVICE_ADDR_IC_1, R37_BCLK_IN0_PIN_ADDR_IC_1, R37_BCLK_IN0_PIN_SIZE_IC_1, R37_BCLK_IN0_PIN_IC_1_Data);
    SIGMA_WRITE_REGISTER_BLOCK(DEVICE_ADDR_IC_1, R38_BCLK_OUT0_PIN_ADDR_IC_1, R38_BCLK_OUT0_PIN_SIZE_IC_1, R38_BCLK_OUT0_PIN_IC_1_Data);
    SIGMA_WRITE_REGISTER_BLOCK(DEVICE_ADDR_IC_1, R39_LRCLK_IN0_PIN_ADDR_IC_1, R39_LRCLK_IN0_PIN_SIZE_IC_1, R39_LRCLK_IN0_PIN_IC_1_Data);
    SIGMA_WRITE_REGISTER_BLOCK(DEVICE_ADDR_IC_1, R40_LRCLK_OUT0_PIN_ADDR_IC_1, R40_LRCLK_OUT0_PIN_SIZE_IC_1, R40_LRCLK_OUT0_PIN_IC_1_Data);
    SIGMA_WRITE_REGISTER_BLOCK(DEVICE_ADDR_IC_1, R41_SDATA_IN0_PIN_ADDR_IC_1, R41_SDATA_IN0_PIN_SIZE_IC_1, R41_SDATA_IN0_PIN_IC_1_Data);
    SIGMA_WRITE_REGISTER_BLOCK(DEVICE_ADDR_IC_1, R42_SDATA_OUT0_PIN_ADDR_IC_1, R42_SDATA_OUT0_PIN_SIZE_IC_1, R42_SDATA_OUT0_PIN_IC_1_Data);
    SIGMA_WRITE_REGISTER_BLOCK(DEVICE_ADDR_IC_1, R43_SCLK_SCL_PIN_ADDR_IC_1, R43_SCLK_SCL_PIN_SIZE_IC_1, R43_SCLK_SCL_PIN_IC_1_Data);
    SIGMA_WRITE_REGISTER_BLOCK(DEVICE_ADDR_IC_1, R44_MISO_SDA_PIN_ADDR_IC_1, R44_MISO_SDA_PIN_SIZE_IC_1, R44_MISO_SDA_PIN_IC_1_Data);
    SIGMA_WRITE_REGISTER_BLOCK(DEVICE_ADDR_IC_1, R45_CLKOUT_PIN_ADDR_IC_1, R45_CLKOUT_PIN_SIZE_IC_1, R45_CLKOUT_PIN_IC_1_Data);
    SIGMA_WRITE_REGISTER_BLOCK(DEVICE_ADDR_IC_1, R46_SOUT_SOURCE16_ADDR_IC_1, R46_SOUT_SOURCE16_SIZE_IC_1, R46_SOUT_SOURCE16_IC_1_Data);
    SIGMA_WRITE_REGISTER_BLOCK(DEVICE_ADDR_IC_1, R47_SOUT_SOURCE20_ADDR_IC_1, R47_SOUT_SOURCE20_SIZE_IC_1, R47_SOUT_SOURCE20_IC_1_Data);
    SIGMA_WRITE_REGISTER_BLOCK(DEVICE_ADDR_IC_1, R48_SERIAL_BYTE_0_0_ADDR_IC_1, R48_SERIAL_BYTE_0_0_SIZE_IC_1, R48_SERIAL_BYTE_0_0_IC_1_Data);
    SIGMA_WRITE_REGISTER_BLOCK(DEVICE_ADDR_IC_1, R49_SERIAL_BYTE_1_0_ADDR_IC_1, R49_SERIAL_BYTE_1_0_SIZE_IC_1, R49_SERIAL_BYTE_1_0_IC_1_Data);
    SIGMA_WRITE_REGISTER_BLOCK(DEVICE_ADDR_IC_1, R50_SERIAL_BYTE_1_1_ADDR_IC_1, R50_SERIAL_BYTE_1_1_SIZE_IC_1, R50_SERIAL_BYTE_1_1_IC_1_Data);
    SIGMA_WRITE_REGISTER_BLOCK(DEVICE_ADDR_IC_1, R51_SERIAL_BYTE_2_0_ADDR_IC_1, R51_SERIAL_BYTE_2_0_SIZE_IC_1, R51_SERIAL_BYTE_2_0_IC_1_Data);
    SIGMA_WRITE_REGISTER_BLOCK(DEVICE_ADDR_IC_1, R52_SERIAL_BYTE_2_1_ADDR_IC_1, R52_SERIAL_BYTE_2_1_SIZE_IC_1, R52_SERIAL_BYTE_2_1_IC_1_Data);
    SIGMA_WRITE_REGISTER_BLOCK(DEVICE_ADDR_IC_1, R53_SERIAL_BYTE_3_0_ADDR_IC_1, R53_SERIAL_BYTE_3_0_SIZE_IC_1, R53_SERIAL_BYTE_3_0_IC_1_Data);
    SIGMA_WRITE_REGISTER_BLOCK(DEVICE_ADDR_IC_1, R54_SERIAL_BYTE_3_1_ADDR_IC_1, R54_SERIAL_BYTE_3_1_SIZE_IC_1, R54_SERIAL_BYTE_3_1_IC_1_Data);
    SIGMA_WRITE_REGISTER_BLOCK(DEVICE_ADDR_IC_1, R55_SERIAL_BYTE_4_0_ADDR_IC_1, R55_SERIAL_BYTE_4_0_SIZE_IC_1, R55_SERIAL_BYTE_4_0_IC_1_Data);
    SIGMA_WRITE_REGISTER_BLOCK(DEVICE_ADDR_IC_1, R56_SERIAL_BYTE_4_1_ADDR_IC_1, R56_SERIAL_BYTE_4_1_SIZE_IC_1, R56_SERIAL_BYTE_4_1_IC_1_Data);
    SIGMA_WRITE_REGISTER_BLOCK(DEVICE_ADDR_IC_1, R57_SERIAL_BYTE_5_0_ADDR_IC_1, R57_SERIAL_BYTE_5_0_SIZE_IC_1, R57_SERIAL_BYTE_5_0_IC_1_Data);
    SIGMA_WRITE_REGISTER_BLOCK(DEVICE_ADDR_IC_1, R58_SERIAL_BYTE_5_1_ADDR_IC_1, R58_SERIAL_BYTE_5_1_SIZE_IC_1, R58_SERIAL_BYTE_5_1_IC_1_Data);
    SIGMA_WRITE_REGISTER_BLOCK(DEVICE_ADDR_IC_1, R59_SERIAL_BYTE_6_0_ADDR_IC_1, R59_SERIAL_BYTE_6_0_SIZE_IC_1, R59_SERIAL_BYTE_6_0_IC_1_Data);
    SIGMA_WRITE_REGISTER_BLOCK(DEVICE_ADDR_IC_1, R60_SERIAL_BYTE_7_0_ADDR_IC_1, R60_SERIAL_BYTE_7_0_SIZE_IC_1, R60_SERIAL_BYTE_7_0_IC_1_Data);
    SIGMA_WRITE_REGISTER_BLOCK(DEVICE_ADDR_IC_1, R61_SPDIF_RX_CTRL_ADDR_IC_1, R61_SPDIF_RX_CTRL_SIZE_IC_1, R61_SPDIF_RX_CTRL_IC_1_Data);
    SIGMA_WRITE_REGISTER_BLOCK(DEVICE_ADDR_IC_1, R62_SPDIF_TX_EN_ADDR_IC_1, R62_SPDIF_TX_EN_SIZE_IC_1, R62_SPDIF_TX_EN_IC_1_Data);
    SIGMA_WRITE_REGISTER_BLOCK(DEVICE_ADDR_IC_1, PROGRAM_DATA_ADDR_IC_1, PROGRAM_DATA_SIZE_IC_1, PROGRAM_DATA_IC_1_Data);
    SIGMA_WRITE_REGISTER_BLOCK(DEVICE_ADDR_IC_1, DM0_DATA_ADDR_IC_1, DM0_DATA_SIZE_IC_1, DM0_DATA_IC_1_Data);
    SIGMA_WRITE_REGISTER_BLOCK(DEVICE_ADDR_IC_1, DM1_DATA_ADDR_IC_1, DM1_DATA_SIZE_IC_1, DM1_DATA_IC_1_Data);
    SIGMA_WRITE_REGISTER_BLOCK(DEVICE_ADDR_IC_1, R66_KILL_CORE_ADDR_IC_1, R66_KILL_CORE_SIZE_IC_1, R66_KILL_CORE_IC_1_Data);
    SIGMA_WRITE_REGISTER_BLOCK(DEVICE_ADDR_IC_1, R67_START_ADDRESS_ADDR_IC_1, R67_START_ADDRESS_SIZE_IC_1, R67_START_ADDRESS_IC_1_Data);
    SIGMA_WRITE_REGISTER_BLOCK(DEVICE_ADDR_IC_1, R68_START_PULSE_ADDR_IC_1, R68_START_PULSE_SIZE_IC_1, R68_START_PULSE_IC_1_Data);
    SIGMA_WRITE_REGISTER_BLOCK(DEVICE_ADDR_IC_1, R69_START_CORE_ADDR_IC_1, R69_START_CORE_SIZE_IC_1, R69_START_CORE_IC_1_Data);
    SIGMA_WRITE_REGISTER_BLOCK(DEVICE_ADDR_IC_1, R70_START_CORE_ADDR_IC_1, R70_START_CORE_SIZE_IC_1, R70_START_CORE_IC_1_Data);
    SIGMA_WRITE_DELAY(DEVICE_ADDR_IC_1, R71_START_DELAY_ADDR_IC_1, R71_START_DELAY_SIZE_IC_1, R71_START_DELAY_IC_1_Data);
    SIGMA_WRITE_REGISTER_BLOCK(DEVICE_ADDR_IC_1, R72_HIBERNATE_ADDR_IC_1, R72_HIBERNATE_SIZE_IC_1, R72_HIBERNATE_IC_1_Data);
}
#endif
