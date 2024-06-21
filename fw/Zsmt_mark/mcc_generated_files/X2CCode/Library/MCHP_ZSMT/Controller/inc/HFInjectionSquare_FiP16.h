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
#ifndef HFINJECTIONSQUARE_FIP16_H
#define HFINJECTIONSQUARE_FIP16_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(HFINJECTIONSQUARE_FIP16_ISLINKED)
#define HFINJECTIONSQUARE_FIP16_ID ((uint16)9681)

#if !defined(X2C_USE_UNION_FOR_POINTER)
typedef struct {
    uint16          ID;
    int16           *iAlpha;
    int16           *iBeta;
    int16           *n0;
    int16           *phi0;
    bool            *Enable;
    int16           ud;
    int16           i_eps;
    int16           n;
    int16           phi;
    int16           uInjAmp;
    int8            sampleCnt;
    int32           *iyArr;
    bool            enable_old;
    int64           i_old_torque;
    int32           i_old_speed;
    int32           i_old_angle;
    int16           vGain;
    int8            sfrGain;
    int32           b0_torque;
    int32           b1_torque;
    int8            sfrb0_torque;
    int8            sfrb1_torque;
    int16           b0_speed;
    int16           b1_speed;
    int8            sfrb0_speed;
    int8            sfrb1_speed;
    int16           b0_angle;
    int16           b1_angle;
    int8            sfrb0_angle;
    int8            sfrb1_angle;
    bool            rawSpeed;
} HFINJECTIONSQUARE_FIP16;
#else
typedef struct {
    uint16          ID;
    INT16_PTR       iAlpha;
    INT16_PTR       iBeta;
    INT16_PTR       n0;
    INT16_PTR       phi0;
    BOOL_PTR        Enable;
    int16           ud;
    int16           i_eps;
    int16           n;
    int16           phi;
    int16           uInjAmp;
    int8            sampleCnt;
    INT32_PTR       iyArr;
    bool            enable_old;
    int64           i_old_torque;
    int32           i_old_speed;
    int32           i_old_angle;
    int16           vGain;
    int8            sfrGain;
    int32           b0_torque;
    int32           b1_torque;
    int8            sfrb0_torque;
    int8            sfrb1_torque;
    int16           b0_speed;
    int16           b1_speed;
    int8            sfrb0_speed;
    int8            sfrb1_speed;
    int16           b0_angle;
    int16           b1_angle;
    int8            sfrb0_angle;
    int8            sfrb1_angle;
    bool            rawSpeed;
} HFINJECTIONSQUARE_FIP16;
#endif

#define HFINJECTIONSQUARE_FIP16_FUNCTIONS { \
    HFINJECTIONSQUARE_FIP16_ID, \
    (void (*)(void*))HFInjectionSquare_FiP16_Update, \
    (void (*)(void*))HFInjectionSquare_FiP16_Init, \
    (tLoadImplementationParameter)HFInjectionSquare_FiP16_Load, \
    (tSaveImplementationParameter)HFInjectionSquare_FiP16_Save, \
    (void* (*)(const void*, uint16))HFInjectionSquare_FiP16_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void HFInjectionSquare_FiP16_Update(HFINJECTIONSQUARE_FIP16 *pTHFInjectionSquare_FiP16);
void HFInjectionSquare_FiP16_Init(HFINJECTIONSQUARE_FIP16 *pTHFInjectionSquare_FiP16);
uint8 HFInjectionSquare_FiP16_Load(const HFINJECTIONSQUARE_FIP16 *pTHFInjectionSquare_FiP16, uint8 data[], uint16 *dataLength, uint16 maxSize);
uint8 HFInjectionSquare_FiP16_Save(HFINJECTIONSQUARE_FIP16 *pTHFInjectionSquare_FiP16, const uint8 data[], uint16 dataLength);
void* HFInjectionSquare_FiP16_GetAddress(const HFINJECTIONSQUARE_FIP16 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
