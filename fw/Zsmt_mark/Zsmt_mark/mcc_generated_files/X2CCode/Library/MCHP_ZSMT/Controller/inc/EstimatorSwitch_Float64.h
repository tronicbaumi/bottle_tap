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
#ifndef ESTIMATORSWITCH_FLOAT64_H
#define ESTIMATORSWITCH_FLOAT64_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(ESTIMATORSWITCH_FLOAT64_ISLINKED)
#define ESTIMATORSWITCH_FLOAT64_ID ((uint16)9716)

#if !defined(X2C_USE_UNION_FOR_POINTER)
typedef struct {
    uint16          ID;
    float64         *phi_H;
    float64         *phi_L;
    float64         *n_H;
    float64         *n_L;
    float64         phi;
    float64         n;
    bool            Enable_H;
    bool            Enable_L;
    float64         thresh_up;
    float64         thresh_down;
    int8            status;
} ESTIMATORSWITCH_FLOAT64;
#else
typedef struct {
    uint16          ID;
    FLOAT64_PTR     phi_H;
    FLOAT64_PTR     phi_L;
    FLOAT64_PTR     n_H;
    FLOAT64_PTR     n_L;
    float64         phi;
    float64         n;
    bool            Enable_H;
    bool            Enable_L;
    float64         thresh_up;
    float64         thresh_down;
    int8            status;
} ESTIMATORSWITCH_FLOAT64;
#endif

#define ESTIMATORSWITCH_FLOAT64_FUNCTIONS { \
    ESTIMATORSWITCH_FLOAT64_ID, \
    (void (*)(void*))EstimatorSwitch_Float64_Update, \
    (void (*)(void*))EstimatorSwitch_Float64_Init, \
    (tLoadImplementationParameter)EstimatorSwitch_Float64_Load, \
    (tSaveImplementationParameter)EstimatorSwitch_Float64_Save, \
    (void* (*)(const void*, uint16))EstimatorSwitch_Float64_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void EstimatorSwitch_Float64_Update(ESTIMATORSWITCH_FLOAT64 *pTEstimatorSwitch_Float64);
void EstimatorSwitch_Float64_Init(ESTIMATORSWITCH_FLOAT64 *pTEstimatorSwitch_Float64);
uint8 EstimatorSwitch_Float64_Load(const ESTIMATORSWITCH_FLOAT64 *pTEstimatorSwitch_Float64, uint8 data[], uint16 *dataLength, uint16 maxSize);
uint8 EstimatorSwitch_Float64_Save(ESTIMATORSWITCH_FLOAT64 *pTEstimatorSwitch_Float64, const uint8 data[], uint16 dataLength);
void* EstimatorSwitch_Float64_GetAddress(const ESTIMATORSWITCH_FLOAT64 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
