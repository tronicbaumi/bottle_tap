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
#ifndef HFINJECTIONSQUARE_FIP32_H
#define HFINJECTIONSQUARE_FIP32_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(HFINJECTIONSQUARE_FIP32_ISLINKED)
#define HFINJECTIONSQUARE_FIP32_ID ((uint16)9682)

#if !defined(X2C_USE_UNION_FOR_POINTER)
typedef struct {
    uint16          ID;
    int32           *iAlpha;
    int32           *iBeta;
    int32           *n0;
    int32           *phi0;
    bool            *Enable;
    int32           ud;
    int32           i_eps;
    int32           n;
    int32           phi;
    int32           uInjAmp;
    int8            sampleCnt;
    int32           *iyArr;
    bool            enable_old;
    int64           i_old_torque;
    int32           i_old_speed;
    int32           i_old_angle;
    int32           vGain;
    int8            sfrGain;
    int32           b0_torque;
    int32           b1_torque;
    int8            sfrb0_torque;
    int8            sfrb1_torque;
    int32           b0_speed;
    int32           b1_speed;
    int8            sfrb0_speed;
    int8            sfrb1_speed;
    int32           b0_angle;
    int32           b1_angle;
    int8            sfrb0_angle;
    int8            sfrb1_angle;
    bool            rawSpeed;
} HFINJECTIONSQUARE_FIP32;
#else
typedef struct {
    uint16          ID;
    INT32_PTR       iAlpha;
    INT32_PTR       iBeta;
    INT32_PTR       n0;
    INT32_PTR       phi0;
    BOOL_PTR        Enable;
    int32           ud;
    int32           i_eps;
    int32           n;
    int32           phi;
    int32           uInjAmp;
    int8            sampleCnt;
    INT32_PTR       iyArr;
    bool            enable_old;
    int64           i_old_torque;
    int32           i_old_speed;
    int32           i_old_angle;
    int32           vGain;
    int8            sfrGain;
    int32           b0_torque;
    int32           b1_torque;
    int8            sfrb0_torque;
    int8            sfrb1_torque;
    int32           b0_speed;
    int32           b1_speed;
    int8            sfrb0_speed;
    int8            sfrb1_speed;
    int32           b0_angle;
    int32           b1_angle;
    int8            sfrb0_angle;
    int8            sfrb1_angle;
    bool            rawSpeed;
} HFINJECTIONSQUARE_FIP32;
#endif

#define HFINJECTIONSQUARE_FIP32_FUNCTIONS { \
    HFINJECTIONSQUARE_FIP32_ID, \
    (void (*)(void*))HFInjectionSquare_FiP32_Update, \
    (void (*)(void*))HFInjectionSquare_FiP32_Init, \
    (tLoadImplementationParameter)HFInjectionSquare_FiP32_Load, \
    (tSaveImplementationParameter)HFInjectionSquare_FiP32_Save, \
    (void* (*)(const void*, uint16))HFInjectionSquare_FiP32_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void HFInjectionSquare_FiP32_Update(HFINJECTIONSQUARE_FIP32 *pTHFInjectionSquare_FiP32);
void HFInjectionSquare_FiP32_Init(HFINJECTIONSQUARE_FIP32 *pTHFInjectionSquare_FiP32);
uint8 HFInjectionSquare_FiP32_Load(const HFINJECTIONSQUARE_FIP32 *pTHFInjectionSquare_FiP32, uint8 data[], uint16 *dataLength, uint16 maxSize);
uint8 HFInjectionSquare_FiP32_Save(HFINJECTIONSQUARE_FIP32 *pTHFInjectionSquare_FiP32, const uint8 data[], uint16 dataLength);
void* HFInjectionSquare_FiP32_GetAddress(const HFINJECTIONSQUARE_FIP32 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
