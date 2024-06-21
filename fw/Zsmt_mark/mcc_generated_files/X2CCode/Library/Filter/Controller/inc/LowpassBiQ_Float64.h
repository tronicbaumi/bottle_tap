/*
 * Copyright (c) 2018, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
/*
 * This file is part of X2C. http://x2c.lcm.at/
 * $LastChangedRevision: 2584 $
 * $LastChangedDate:: 2022-05-03 15:06:23 +0200#$
 */
/* USERCODE-BEGIN:Description                                                                                         */
/* Description: */
/* USERCODE-END:Description                                                                                           */
#ifndef LOWPASSBIQ_FLOAT64_H
#define LOWPASSBIQ_FLOAT64_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(LOWPASSBIQ_FLOAT64_ISLINKED)
#define LOWPASSBIQ_FLOAT64_ID ((uint16)8132)

#if !defined(X2C_USE_UNION_FOR_POINTER)
typedef struct {
    uint16          ID;
    float64         *In;
    float64         Out;
    float64         b0;
    float64         b1;
    float64         b2;
    float64         a1;
    float64         a2;
    float64         in_old;
    float64         in_veryold;
    float64         out_old;
    float64         out_veryold;
} LOWPASSBIQ_FLOAT64;
#else
typedef struct {
    uint16          ID;
    FLOAT64_PTR     In;
    float64         Out;
    float64         b0;
    float64         b1;
    float64         b2;
    float64         a1;
    float64         a2;
    float64         in_old;
    float64         in_veryold;
    float64         out_old;
    float64         out_veryold;
} LOWPASSBIQ_FLOAT64;
#endif

#define LOWPASSBIQ_FLOAT64_FUNCTIONS { \
    LOWPASSBIQ_FLOAT64_ID, \
    (void (*)(void*))LowpassBiQ_Float64_Update, \
    (void (*)(void*))LowpassBiQ_Float64_Init, \
    (tLoadImplementationParameter)LowpassBiQ_Float64_Load, \
    (tSaveImplementationParameter)LowpassBiQ_Float64_Save, \
    (void* (*)(const void*, uint16))LowpassBiQ_Float64_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void LowpassBiQ_Float64_Update(LOWPASSBIQ_FLOAT64 *pTLowpassBiQ_Float64);
void LowpassBiQ_Float64_Init(LOWPASSBIQ_FLOAT64 *pTLowpassBiQ_Float64);
uint8 LowpassBiQ_Float64_Load(const LOWPASSBIQ_FLOAT64 *pTLowpassBiQ_Float64, uint8 data[], uint16 *dataLength, uint16 maxSize);
uint8 LowpassBiQ_Float64_Save(LOWPASSBIQ_FLOAT64 *pTLowpassBiQ_Float64, const uint8 data[], uint16 dataLength);
void* LowpassBiQ_Float64_GetAddress(const LOWPASSBIQ_FLOAT64 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
