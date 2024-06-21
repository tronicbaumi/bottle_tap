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
#ifndef ESTIMATORSWITCH_FLOAT32_H
#define ESTIMATORSWITCH_FLOAT32_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(ESTIMATORSWITCH_FLOAT32_ISLINKED)
#define ESTIMATORSWITCH_FLOAT32_ID ((uint16)9715)

#if !defined(X2C_USE_UNION_FOR_POINTER)
typedef struct {
    uint16          ID;
    float32         *phi_H;
    float32         *phi_L;
    float32         *n_H;
    float32         *n_L;
    float32         phi;
    float32         n;
    bool            Enable_H;
    bool            Enable_L;
    float32         thresh_up;
    float32         thresh_down;
    int8            status;
} ESTIMATORSWITCH_FLOAT32;
#else
typedef struct {
    uint16          ID;
    FLOAT32_PTR     phi_H;
    FLOAT32_PTR     phi_L;
    FLOAT32_PTR     n_H;
    FLOAT32_PTR     n_L;
    float32         phi;
    float32         n;
    bool            Enable_H;
    bool            Enable_L;
    float32         thresh_up;
    float32         thresh_down;
    int8            status;
} ESTIMATORSWITCH_FLOAT32;
#endif

#define ESTIMATORSWITCH_FLOAT32_FUNCTIONS { \
    ESTIMATORSWITCH_FLOAT32_ID, \
    (void (*)(void*))EstimatorSwitch_Float32_Update, \
    (void (*)(void*))EstimatorSwitch_Float32_Init, \
    (tLoadImplementationParameter)EstimatorSwitch_Float32_Load, \
    (tSaveImplementationParameter)EstimatorSwitch_Float32_Save, \
    (void* (*)(const void*, uint16))EstimatorSwitch_Float32_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void EstimatorSwitch_Float32_Update(ESTIMATORSWITCH_FLOAT32 *pTEstimatorSwitch_Float32);
void EstimatorSwitch_Float32_Init(ESTIMATORSWITCH_FLOAT32 *pTEstimatorSwitch_Float32);
uint8 EstimatorSwitch_Float32_Load(const ESTIMATORSWITCH_FLOAT32 *pTEstimatorSwitch_Float32, uint8 data[], uint16 *dataLength, uint16 maxSize);
uint8 EstimatorSwitch_Float32_Save(ESTIMATORSWITCH_FLOAT32 *pTEstimatorSwitch_Float32, const uint8 data[], uint16 dataLength);
void* EstimatorSwitch_Float32_GetAddress(const ESTIMATORSWITCH_FLOAT32 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
