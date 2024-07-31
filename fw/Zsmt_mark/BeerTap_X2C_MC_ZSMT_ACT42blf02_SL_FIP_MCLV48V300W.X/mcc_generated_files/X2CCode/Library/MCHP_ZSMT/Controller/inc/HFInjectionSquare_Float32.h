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
#ifndef HFINJECTIONSQUARE_FLOAT32_H
#define HFINJECTIONSQUARE_FLOAT32_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(HFINJECTIONSQUARE_FLOAT32_ISLINKED)
#define HFINJECTIONSQUARE_FLOAT32_ID ((uint16)9683)

#if !defined(X2C_USE_UNION_FOR_POINTER)
typedef struct {
    uint16          ID;
    float32         *iAlpha;
    float32         *iBeta;
    float32         *n0;
    float32         *phi0;
    bool            *Enable;
    float32         ud;
    float32         i_eps;
    float32         n;
    float32         phi;
    float32         uInjAmp;
    int8            sampleCnt;
    float32         *iyArr;
    bool            enable_old;
    float32         i_old_torque;
    float32         i_old_speed;
    float32         i_old_angle;
    float32         vGain;
    float32         b0_torque;
    float32         b1_torque;
    float32         b0_speed;
    float32         b1_speed;
    float32         b0_angle;
    float32         b1_angle;
    bool            rawSpeed;
} HFINJECTIONSQUARE_FLOAT32;
#else
typedef struct {
    uint16          ID;
    FLOAT32_PTR     iAlpha;
    FLOAT32_PTR     iBeta;
    FLOAT32_PTR     n0;
    FLOAT32_PTR     phi0;
    BOOL_PTR        Enable;
    float32         ud;
    float32         i_eps;
    float32         n;
    float32         phi;
    float32         uInjAmp;
    int8            sampleCnt;
    FLOAT32_PTR     iyArr;
    bool            enable_old;
    float32         i_old_torque;
    float32         i_old_speed;
    float32         i_old_angle;
    float32         vGain;
    float32         b0_torque;
    float32         b1_torque;
    float32         b0_speed;
    float32         b1_speed;
    float32         b0_angle;
    float32         b1_angle;
    bool            rawSpeed;
} HFINJECTIONSQUARE_FLOAT32;
#endif

#define HFINJECTIONSQUARE_FLOAT32_FUNCTIONS { \
    HFINJECTIONSQUARE_FLOAT32_ID, \
    (void (*)(void*))HFInjectionSquare_Float32_Update, \
    (void (*)(void*))HFInjectionSquare_Float32_Init, \
    (tLoadImplementationParameter)HFInjectionSquare_Float32_Load, \
    (tSaveImplementationParameter)HFInjectionSquare_Float32_Save, \
    (void* (*)(const void*, uint16))HFInjectionSquare_Float32_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void HFInjectionSquare_Float32_Update(HFINJECTIONSQUARE_FLOAT32 *pTHFInjectionSquare_Float32);
void HFInjectionSquare_Float32_Init(HFINJECTIONSQUARE_FLOAT32 *pTHFInjectionSquare_Float32);
uint8 HFInjectionSquare_Float32_Load(const HFINJECTIONSQUARE_FLOAT32 *pTHFInjectionSquare_Float32, uint8 data[], uint16 *dataLength, uint16 maxSize);
uint8 HFInjectionSquare_Float32_Save(HFINJECTIONSQUARE_FLOAT32 *pTHFInjectionSquare_Float32, const uint8 data[], uint16 dataLength);
void* HFInjectionSquare_Float32_GetAddress(const HFINJECTIONSQUARE_FLOAT32 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
