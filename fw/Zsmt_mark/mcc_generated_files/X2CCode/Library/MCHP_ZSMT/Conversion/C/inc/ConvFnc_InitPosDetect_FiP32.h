/**
 * @file
 * @brief Load, save and conversion function for mask parameter.
 * 
 * Loading of mask parameter from target, saving of mask parameter on target and conversion of mask parameter to implementation parameter.
 */
/*
 * Copyright (c) 2018, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
/*
 * This file is part of X2C. http://x2c.lcm.at/
 * $LastChangedRevision: 2108 $
 * $LastChangedDate:: 2020-12-07 19:09:57 +0100#$
 */
/* USERCODE-BEGIN:Description                                                                                         */
/* Description: */
/* USERCODE-END:Description                                                                                           */
#ifndef CONVFNC_INITPOSDETECT_FIP32_H
#define CONVFNC_INITPOSDETECT_FIP32_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"
#include "InitPosDetect_FiP32.h"

/** Mask parameter data structure */
typedef struct {
    float64 U_pulse;
    float64 T_pulse;
    float64 T_pause;
    float64 U_max;
    float64 ts_fact;
} INITPOSDETECT_FIP32_MASK_PARAM;

/* public prototypes */
uint8 InitPosDetect_FiP32_LoadMP(const INITPOSDETECT_FIP32_MASK_PARAM *maskParam, uint8 data[], uint16* dataLen, uint16 maxSize);
uint8 InitPosDetect_FiP32_SaveMP(INITPOSDETECT_FIP32 *block, INITPOSDETECT_FIP32_MASK_PARAM *maskParam, const uint8 data[], uint16 dataLen);
uint8 InitPosDetect_FiP32_InitMP(INITPOSDETECT_FIP32 *block, const INITPOSDETECT_FIP32_MASK_PARAM *maskParam);
uint8 InitPosDetect_FiP32_ConvertMP(INITPOSDETECT_FIP32 *block, INITPOSDETECT_FIP32_MASK_PARAM *maskParam);
void InitPosDetect_FiP32_BackupMP(INITPOSDETECT_FIP32_MASK_PARAM *maskParam);
void InitPosDetect_FiP32_RestoreMP(INITPOSDETECT_FIP32_MASK_PARAM *maskParam);

#ifdef __cplusplus
}
#endif

#endif
