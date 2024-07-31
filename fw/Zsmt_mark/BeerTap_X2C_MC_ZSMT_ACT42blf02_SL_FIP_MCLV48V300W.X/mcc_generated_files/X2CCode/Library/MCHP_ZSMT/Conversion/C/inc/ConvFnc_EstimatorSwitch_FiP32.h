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
#ifndef CONVFNC_ESTIMATORSWITCH_FIP32_H
#define CONVFNC_ESTIMATORSWITCH_FIP32_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"
#include "EstimatorSwitch_FiP32.h"

/** Mask parameter data structure */
typedef struct {
    float64 thresh_up;
    float64 thresh_down;
    float64 n_max;
    float64 ts_fact;
} ESTIMATORSWITCH_FIP32_MASK_PARAM;

/* public prototypes */
uint8 EstimatorSwitch_FiP32_LoadMP(const ESTIMATORSWITCH_FIP32_MASK_PARAM *maskParam, uint8 data[], uint16* dataLen, uint16 maxSize);
uint8 EstimatorSwitch_FiP32_SaveMP(ESTIMATORSWITCH_FIP32 *block, ESTIMATORSWITCH_FIP32_MASK_PARAM *maskParam, const uint8 data[], uint16 dataLen);
uint8 EstimatorSwitch_FiP32_InitMP(ESTIMATORSWITCH_FIP32 *block, const ESTIMATORSWITCH_FIP32_MASK_PARAM *maskParam);
uint8 EstimatorSwitch_FiP32_ConvertMP(ESTIMATORSWITCH_FIP32 *block, ESTIMATORSWITCH_FIP32_MASK_PARAM *maskParam);
void EstimatorSwitch_FiP32_BackupMP(ESTIMATORSWITCH_FIP32_MASK_PARAM *maskParam);
void EstimatorSwitch_FiP32_RestoreMP(ESTIMATORSWITCH_FIP32_MASK_PARAM *maskParam);

#ifdef __cplusplus
}
#endif

#endif
