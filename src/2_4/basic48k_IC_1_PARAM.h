/* 
 * File:	C:\Users\damla\OneDrive\Bureau\MIDSPampBasicV02Copy\basic48k_IC_1_PARAM.h
 * Created:	Sunday, 07 December 2025 22:16 PM
 * Description:	ADAU146xSchematic_0 parameter RAM definitions.
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
#ifndef __BASIC48K_IC_1_PARAM_H__
#define __BASIC48K_IC_1_PARAM_H__

/* Module Safeload - Schematic Params */
#define MOD_SAFELOAD_COUNT                          8
#define MOD_SAFELOAD_SCHEMATIC                      "ADAU146xSchematic_0"
#define MOD_SAFELOAD_DATA_SAFELOAD0_ADDR            24576
#define MOD_SAFELOAD_DATA_SAFELOAD0_MEM_PAGE        0
#define MOD_SAFELOAD_DATA_SAFELOAD1_ADDR            24577
#define MOD_SAFELOAD_DATA_SAFELOAD1_MEM_PAGE        0
#define MOD_SAFELOAD_DATA_SAFELOAD2_ADDR            24578
#define MOD_SAFELOAD_DATA_SAFELOAD2_MEM_PAGE        0
#define MOD_SAFELOAD_DATA_SAFELOAD3_ADDR            24579
#define MOD_SAFELOAD_DATA_SAFELOAD3_MEM_PAGE        0
#define MOD_SAFELOAD_DATA_SAFELOAD4_ADDR            24580
#define MOD_SAFELOAD_DATA_SAFELOAD4_MEM_PAGE        0
#define MOD_SAFELOAD_ADDR_SAFELOAD_ADDR             24581
#define MOD_SAFELOAD_ADDR_SAFELOAD_MEM_PAGE         0
#define MOD_SAFELOAD_NUM_SAFELOAD_LOWER_ADDR        24582
#define MOD_SAFELOAD_NUM_SAFELOAD_LOWER_MEM_PAGE    0
#define MOD_SAFELOAD_NUM_SAFELOAD_UPPER_ADDR        24583
#define MOD_SAFELOAD_NUM_SAFELOAD_UPPER_MEM_PAGE    0




/* Module SignalMerger_16 - Signal Merger */
#define MOD_SIGNALMERGER_16_COUNT               1
#define MOD_SIGNALMERGER_16_SCHEMATIC           "ADAU146xSchematic_0"
#define MOD_SIGNALMERGER_16_GAIN_ADDR           30
#define MOD_SIGNALMERGER_16_GAIN_FIXPT          0x005555550055555500555555
#define MOD_SIGNALMERGER_16_GAIN_VALUE          SIGMASTUDIOTYPE_8_24_CONVERT(0)
#define MOD_SIGNALMERGER_16_GAIN_TYPE           SIGMASTUDIOTYPE_8_24
#define MOD_SIGNALMERGER_16_GAIN_DATA_MEMORY    "DM0"
#define MOD_SIGNALMERGER_16_GAIN_MEM_PAGE       0
#define MOD_SIGNALMERGER_16_GAIN_DATA_MEMORY    "DM0"
#define MOD_SIGNALMERGER_16_GAIN_MEM_PAGE       0



/* Module Gain_0 - Gain */
#define MOD_GAIN_0_COUNT               1
#define MOD_GAIN_0_SCHEMATIC           "ADAU146xSchematic_0"
#define MOD_GAIN_0_GAIN_ADDR           33
#define MOD_GAIN_0_GAIN_FIXPT          0xFF000000
#define MOD_GAIN_0_GAIN_VALUE          SIGMASTUDIOTYPE_8_24_CONVERT(-1)
#define MOD_GAIN_0_GAIN_TYPE           SIGMASTUDIOTYPE_8_24
#define MOD_GAIN_0_GAIN_DATA_MEMORY    "DM0"
#define MOD_GAIN_0_GAIN_MEM_PAGE       0
#define MOD_GAIN_0_GAIN_DATA_MEMORY    "DM0"
#define MOD_GAIN_0_GAIN_MEM_PAGE       0

/* Module SineTone_0 - Sine Wave */
#define MOD_SINETONE_0_COUNT                                      3
#define MOD_SINETONE_0_SCHEMATIC                                  "ADAU146xSchematic_0"
#define MOD_SINETONE_0_GAIN_CHANNEL0_ADDR                         20
#define MOD_SINETONE_0_GAIN_CHANNEL0_FIXPT                        0x00B53BEF
#define MOD_SINETONE_0_GAIN_CHANNEL0_VALUE                        SIGMASTUDIOTYPE_8_24_CONVERT(0.707945784384138)
#define MOD_SINETONE_0_GAIN_CHANNEL0_TYPE                         SIGMASTUDIOTYPE_8_24
#define MOD_SINETONE_0_GAIN_CHANNEL0_DATA_MEMORY                  "DM0"
#define MOD_SINETONE_0_GAIN_CHANNEL0_MEM_PAGE                     0
#define MOD_SINETONE_0_GAIN_CHANNEL0_DATA_MEMORY                  "DM0"
#define MOD_SINETONE_0_GAIN_CHANNEL0_MEM_PAGE                     0
#define MOD_SINETONE_0_LOOKUPTABLEINDEXHI_CHANNEL0_ADDR           21
#define MOD_SINETONE_0_LOOKUPTABLEINDEXHI_CHANNEL0_FIXPT          0x0000000000000000
#define MOD_SINETONE_0_LOOKUPTABLEINDEXHI_CHANNEL0_VALUE          SIGMASTUDIOTYPE_INTEGER_CONVERT(0)
#define MOD_SINETONE_0_LOOKUPTABLEINDEXHI_CHANNEL0_TYPE           SIGMASTUDIOTYPE_INTEGER
#define MOD_SINETONE_0_LOOKUPTABLEINDEXHI_CHANNEL0_DATA_MEMORY    "DM0"
#define MOD_SINETONE_0_LOOKUPTABLEINDEXHI_CHANNEL0_MEM_PAGE       0
#define MOD_SINETONE_0_LOOKUPTABLEINDEXHI_CHANNEL0_DATA_MEMORY    "DM0"
#define MOD_SINETONE_0_LOOKUPTABLEINDEXHI_CHANNEL0_MEM_PAGE       0
#define MOD_SINETONE_0_INCREMENT_ADDR                             25
#define MOD_SINETONE_0_INCREMENT_FIXPT                            0x00055555
#define MOD_SINETONE_0_INCREMENT_VALUE                            SIGMASTUDIOTYPE_8_24_CONVERT(0.0208333333333333)
#define MOD_SINETONE_0_INCREMENT_TYPE                             SIGMASTUDIOTYPE_8_24
#define MOD_SINETONE_0_INCREMENT_DATA_MEMORY                      "DM0"
#define MOD_SINETONE_0_INCREMENT_MEM_PAGE                         0
#define MOD_SINETONE_0_INCREMENT_DATA_MEMORY                      "DM0"
#define MOD_SINETONE_0_INCREMENT_MEM_PAGE                         0

#endif
