/*
 * Copyright (c) 2014, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
/*
 * This file is part of X2C. http://www.mechatronic-simulation.org/
 * $LastChangedRevision: 2108 $
 */
/* USERCODE-BEGIN:Description                                                                                         */
/* Description:
    Implements switching policy between sensorless algorithms for low and high speeds.
    Decision base is the speed magnitude. */
/* USERCODE-END:Description                                                                                           */
#ifndef ESTIMATORSWITCH_FIP16_H
#define ESTIMATORSWITCH_FIP16_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(ESTIMATORSWITCH_FIP16_ISLINKED)
#define ESTIMATORSWITCH_FIP16_ID ((uint16)9713)

#if !defined(X2C_USE_UNION_FOR_POINTER)
typedef struct {
    uint16          ID;
    int16           *phi_H;
    int16           *phi_L;
    int16           *n_H;
    int16           *n_L;
    int16           phi;
    int16           n;
    bool            Enable_H;
    bool            Enable_L;
    int16           thresh_up;
    int16           thresh_down;
    int8            status;
} ESTIMATORSWITCH_FIP16;
#else
typedef struct {
    uint16          ID;
    INT16_PTR       phi_H;
    INT16_PTR       phi_L;
    INT16_PTR       n_H;
    INT16_PTR       n_L;
    int16           phi;
    int16           n;
    bool            Enable_H;
    bool            Enable_L;
    int16           thresh_up;
    int16           thresh_down;
    int8            status;
} ESTIMATORSWITCH_FIP16;
#endif

#define ESTIMATORSWITCH_FIP16_FUNCTIONS { \
    ESTIMATORSWITCH_FIP16_ID, \
    (void (*)(void*))EstimatorSwitch_FiP16_Update, \
    (void (*)(void*))EstimatorSwitch_FiP16_Init, \
    (tLoadImplementationParameter)EstimatorSwitch_FiP16_Load, \
    (tSaveImplementationParameter)EstimatorSwitch_FiP16_Save, \
    (void* (*)(const void*, uint16))EstimatorSwitch_FiP16_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void EstimatorSwitch_FiP16_Update(ESTIMATORSWITCH_FIP16 *pTEstimatorSwitch_FiP16);
void EstimatorSwitch_FiP16_Init(ESTIMATORSWITCH_FIP16 *pTEstimatorSwitch_FiP16);
uint8 EstimatorSwitch_FiP16_Load(const ESTIMATORSWITCH_FIP16 *pTEstimatorSwitch_FiP16, uint8 data[], uint16 *dataLength, uint16 maxSize);
uint8 EstimatorSwitch_FiP16_Save(ESTIMATORSWITCH_FIP16 *pTEstimatorSwitch_FiP16, const uint8 data[], uint16 dataLength);
void* EstimatorSwitch_FiP16_GetAddress(const ESTIMATORSWITCH_FIP16 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
