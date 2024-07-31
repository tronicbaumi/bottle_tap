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
#ifndef CONVFNC_INITPOSDETECT_FLOAT32_H
#define CONVFNC_INITPOSDETECT_FLOAT32_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"
#include "InitPosDetect_Float32.h"

/** Mask parameter data structure */
typedef struct {
    float64 U_pulse;
    float64 T_pulse;
    float64 T_pause;
    float64 U_max;
    float64 ts_fact;
} INITPOSDETECT_FLOAT32_MASK_PARAM;

/* public prototypes */
uint8 InitPosDetect_Float32_LoadMP(const INITPOSDETECT_FLOAT32_MASK_PARAM *maskParam, uint8 data[], uint16* dataLen, uint16 maxSize);
uint8 InitPosDetect_Float32_SaveMP(INITPOSDETECT_FLOAT32 *block, INITPOSDETECT_FLOAT32_MASK_PARAM *maskParam, const uint8 data[], uint16 dataLen);
uint8 InitPosDetect_Float32_InitMP(INITPOSDETECT_FLOAT32 *block, const INITPOSDETECT_FLOAT32_MASK_PARAM *maskParam);
uint8 InitPosDetect_Float32_ConvertMP(INITPOSDETECT_FLOAT32 *block, INITPOSDETECT_FLOAT32_MASK_PARAM *maskParam);
void InitPosDetect_Float32_BackupMP(INITPOSDETECT_FLOAT32_MASK_PARAM *maskParam);
void InitPosDetect_Float32_RestoreMP(INITPOSDETECT_FLOAT32_MASK_PARAM *maskParam);

#ifdef __cplusplus
}
#endif

#endif
