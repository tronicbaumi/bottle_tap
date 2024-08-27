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
 * $LastChangedRevision: 2128 $
 * $LastChangedDate:: 2021-02-02 14:38:09 +0100#$
 */
/* USERCODE-BEGIN:Description                                                                                         */
/* Description: */
/* USERCODE-END:Description                                                                                           */
#ifndef CONVFNC_HFINJECTIONSQUARE_FLOAT64_H
#define CONVFNC_HFINJECTIONSQUARE_FLOAT64_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"
#include "HFInjectionSquare_Float64.h"

/** Mask parameter data structure */
typedef struct {
    float64 U_inj;
    float64 Jp;
    float64 I_inj;
    float64 fo;
    float64 p;
    float64 n_max;
    float64 I_max;
    float64 U_max;
    float64 ts_fact;
    uint8 estimation;
    uint8 method;
} HFINJECTIONSQUARE_FLOAT64_MASK_PARAM;

/* public prototypes */
uint8 HFInjectionSquare_Float64_LoadMP(const HFINJECTIONSQUARE_FLOAT64_MASK_PARAM *maskParam, uint8 data[], uint16* dataLen, uint16 maxSize);
uint8 HFInjectionSquare_Float64_SaveMP(HFINJECTIONSQUARE_FLOAT64 *block, HFINJECTIONSQUARE_FLOAT64_MASK_PARAM *maskParam, const uint8 data[], uint16 dataLen);
uint8 HFInjectionSquare_Float64_InitMP(HFINJECTIONSQUARE_FLOAT64 *block, const HFINJECTIONSQUARE_FLOAT64_MASK_PARAM *maskParam);
uint8 HFInjectionSquare_Float64_ConvertMP(HFINJECTIONSQUARE_FLOAT64 *block, HFINJECTIONSQUARE_FLOAT64_MASK_PARAM *maskParam);
void HFInjectionSquare_Float64_BackupMP(HFINJECTIONSQUARE_FLOAT64_MASK_PARAM *maskParam);
void HFInjectionSquare_Float64_RestoreMP(HFINJECTIONSQUARE_FLOAT64_MASK_PARAM *maskParam);

#ifdef __cplusplus
}
#endif

#endif
