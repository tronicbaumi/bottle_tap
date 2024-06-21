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
/* Description: 
 *  Angle observer based on evaluation of injected high frequency square wave voltage signal.
 */
/* USERCODE-END:Description                                                                                           */
#ifndef HFINJECTIONSQUARE_FLOAT64_H
#define HFINJECTIONSQUARE_FLOAT64_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(HFINJECTIONSQUARE_FLOAT64_ISLINKED)
#define HFINJECTIONSQUARE_FLOAT64_ID ((uint16)9684)

#if !defined(X2C_USE_UNION_FOR_POINTER)
typedef struct {
    uint16          ID;
    float64         *iAlpha;
    float64         *iBeta;
    float64         *n0;
    float64         *phi0;
    bool            *Enable;
    float64         ud;
    float64         i_eps;
    float64         n;
    float64         phi;
    float64         uInjAmp;
    int8            sampleCnt;
    float64         *iyArr;
    bool            enable_old;
    float64         i_old_torque;
    float64         i_old_speed;
    float64         i_old_angle;
    float64         vGain;
    float64         b0_torque;
    float64         b1_torque;
    float64         b0_speed;
    float64         b1_speed;
    float64         b0_angle;
    float64         b1_angle;
    bool            rawSpeed;
} HFINJECTIONSQUARE_FLOAT64;
#else
typedef struct {
    uint16          ID;
    FLOAT64_PTR     iAlpha;
    FLOAT64_PTR     iBeta;
    FLOAT64_PTR     n0;
    FLOAT64_PTR     phi0;
    BOOL_PTR        Enable;
    float64         ud;
    float64         i_eps;
    float64         n;
    float64         phi;
    float64         uInjAmp;
    int8            sampleCnt;
    FLOAT64_PTR     iyArr;
    bool            enable_old;
    float64         i_old_torque;
    float64         i_old_speed;
    float64         i_old_angle;
    float64         vGain;
    float64         b0_torque;
    float64         b1_torque;
    float64         b0_speed;
    float64         b1_speed;
    float64         b0_angle;
    float64         b1_angle;
    bool            rawSpeed;
} HFINJECTIONSQUARE_FLOAT64;
#endif

#define HFINJECTIONSQUARE_FLOAT64_FUNCTIONS { \
    HFINJECTIONSQUARE_FLOAT64_ID, \
    (void (*)(void*))HFInjectionSquare_Float64_Update, \
    (void (*)(void*))HFInjectionSquare_Float64_Init, \
    (tLoadImplementationParameter)HFInjectionSquare_Float64_Load, \
    (tSaveImplementationParameter)HFInjectionSquare_Float64_Save, \
    (void* (*)(const void*, uint16))HFInjectionSquare_Float64_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void HFInjectionSquare_Float64_Update(HFINJECTIONSQUARE_FLOAT64 *pTHFInjectionSquare_Float64);
void HFInjectionSquare_Float64_Init(HFINJECTIONSQUARE_FLOAT64 *pTHFInjectionSquare_Float64);
uint8 HFInjectionSquare_Float64_Load(const HFINJECTIONSQUARE_FLOAT64 *pTHFInjectionSquare_Float64, uint8 data[], uint16 *dataLength, uint16 maxSize);
uint8 HFInjectionSquare_Float64_Save(HFINJECTIONSQUARE_FLOAT64 *pTHFInjectionSquare_Float64, const uint8 data[], uint16 dataLength);
void* HFInjectionSquare_Float64_GetAddress(const HFINJECTIONSQUARE_FLOAT64 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
