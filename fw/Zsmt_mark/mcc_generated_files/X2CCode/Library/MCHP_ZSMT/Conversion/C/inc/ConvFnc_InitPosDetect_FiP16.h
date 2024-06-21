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
#ifndef CONVFNC_INITPOSDETECT_FIP16_H
#define CONVFNC_INITPOSDETECT_FIP16_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"
#include "InitPosDetect_FiP16.h"

/** Mask parameter data structure */
typedef struct {
    float64 U_pulse;
    float64 T_pulse;
    float64 T_pause;
    float64 U_max;
    float64 ts_fact;
} INITPOSDETECT_FIP16_MASK_PARAM;

/* public prototypes */
uint8 InitPosDetect_FiP16_LoadMP(const INITPOSDETECT_FIP16_MASK_PARAM *maskParam, uint8 data[], uint16* dataLen, uint16 maxSize);
uint8 InitPosDetect_FiP16_SaveMP(INITPOSDETECT_FIP16 *block, INITPOSDETECT_FIP16_MASK_PARAM *maskParam, const uint8 data[], uint16 dataLen);
uint8 InitPosDetect_FiP16_InitMP(INITPOSDETECT_FIP16 *block, const INITPOSDETECT_FIP16_MASK_PARAM *maskParam);
uint8 InitPosDetect_FiP16_ConvertMP(INITPOSDETECT_FIP16 *block, INITPOSDETECT_FIP16_MASK_PARAM *maskParam);
void InitPosDetect_FiP16_BackupMP(INITPOSDETECT_FIP16_MASK_PARAM *maskParam);
void InitPosDetect_FiP16_RestoreMP(INITPOSDETECT_FIP16_MASK_PARAM *maskParam);

#ifdef __cplusplus
}
#endif

#endif
