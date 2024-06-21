/**
 * @file
 * @brief Load, save and conversion function for mask parameter.
 * 
 * Loading of mask parameter from target, saving of mask parameter on target and conversion of mask parameter to implementation parameter.
 */
/*
 * Copyright (c) 2014, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
/*
 * This file is part of X2C. http://www.mechatronic-simulation.org/
 * $LastChangedRevision: 2108 $
 */
/* USERCODE-BEGIN:Description                                                                                         */
/* Description: */
/* USERCODE-END:Description                                                                                           */
#ifndef CONVFNC_ESTIMATORSWITCH_FLOAT32_H
#define CONVFNC_ESTIMATORSWITCH_FLOAT32_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"
#include "EstimatorSwitch_Float32.h"

/** Mask parameter data structure */
typedef struct {
    float64 thresh_up;
    float64 thresh_down;
    float64 n_max;
    float64 ts_fact;
} ESTIMATORSWITCH_FLOAT32_MASK_PARAM;

/* public prototypes */
uint8 EstimatorSwitch_Float32_LoadMP(const ESTIMATORSWITCH_FLOAT32_MASK_PARAM *maskParam, uint8 data[], uint16* dataLen, uint16 maxSize);
uint8 EstimatorSwitch_Float32_SaveMP(ESTIMATORSWITCH_FLOAT32 *block, ESTIMATORSWITCH_FLOAT32_MASK_PARAM *maskParam, const uint8 data[], uint16 dataLen);
uint8 EstimatorSwitch_Float32_InitMP(ESTIMATORSWITCH_FLOAT32 *block, const ESTIMATORSWITCH_FLOAT32_MASK_PARAM *maskParam);
uint8 EstimatorSwitch_Float32_ConvertMP(ESTIMATORSWITCH_FLOAT32 *block, ESTIMATORSWITCH_FLOAT32_MASK_PARAM *maskParam);
void EstimatorSwitch_Float32_BackupMP(ESTIMATORSWITCH_FLOAT32_MASK_PARAM *maskParam);
void EstimatorSwitch_Float32_RestoreMP(ESTIMATORSWITCH_FLOAT32_MASK_PARAM *maskParam);

#ifdef __cplusplus
}
#endif

#endif
