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
#ifndef ESTIMATORSWITCH_FIP32_H
#define ESTIMATORSWITCH_FIP32_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(ESTIMATORSWITCH_FIP32_ISLINKED)
#define ESTIMATORSWITCH_FIP32_ID ((uint16)9714)

#if !defined(X2C_USE_UNION_FOR_POINTER)
typedef struct {
    uint16          ID;
    int32           *phi_H;
    int32           *phi_L;
    int32           *n_H;
    int32           *n_L;
    int32           phi;
    int32           n;
    bool            Enable_H;
    bool            Enable_L;
    int32           thresh_up;
    int32           thresh_down;
    int8            status;
} ESTIMATORSWITCH_FIP32;
#else
typedef struct {
    uint16          ID;
    INT32_PTR       phi_H;
    INT32_PTR       phi_L;
    INT32_PTR       n_H;
    INT32_PTR       n_L;
    int32           phi;
    int32           n;
    bool            Enable_H;
    bool            Enable_L;
    int32           thresh_up;
    int32           thresh_down;
    int8            status;
} ESTIMATORSWITCH_FIP32;
#endif

#define ESTIMATORSWITCH_FIP32_FUNCTIONS { \
    ESTIMATORSWITCH_FIP32_ID, \
    (void (*)(void*))EstimatorSwitch_FiP32_Update, \
    (void (*)(void*))EstimatorSwitch_FiP32_Init, \
    (tLoadImplementationParameter)EstimatorSwitch_FiP32_Load, \
    (tSaveImplementationParameter)EstimatorSwitch_FiP32_Save, \
    (void* (*)(const void*, uint16))EstimatorSwitch_FiP32_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void EstimatorSwitch_FiP32_Update(ESTIMATORSWITCH_FIP32 *pTEstimatorSwitch_FiP32);
void EstimatorSwitch_FiP32_Init(ESTIMATORSWITCH_FIP32 *pTEstimatorSwitch_FiP32);
uint8 EstimatorSwitch_FiP32_Load(const ESTIMATORSWITCH_FIP32 *pTEstimatorSwitch_FiP32, uint8 data[], uint16 *dataLength, uint16 maxSize);
uint8 EstimatorSwitch_FiP32_Save(ESTIMATORSWITCH_FIP32 *pTEstimatorSwitch_FiP32, const uint8 data[], uint16 dataLength);
void* EstimatorSwitch_FiP32_GetAddress(const ESTIMATORSWITCH_FIP32 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
