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
#ifndef BIQUAD_FLOAT64_H
#define BIQUAD_FLOAT64_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(BIQUAD_FLOAT64_ISLINKED)
#define BIQUAD_FLOAT64_ID ((uint16)8084)

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
} BIQUAD_FLOAT64;
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
} BIQUAD_FLOAT64;
#endif

#define BIQUAD_FLOAT64_FUNCTIONS { \
    BIQUAD_FLOAT64_ID, \
    (void (*)(void*))Biquad_Float64_Update, \
    (void (*)(void*))Biquad_Float64_Init, \
    (tLoadImplementationParameter)Biquad_Float64_Load, \
    (tSaveImplementationParameter)Biquad_Float64_Save, \
    (void* (*)(const void*, uint16))Biquad_Float64_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void Biquad_Float64_Update(BIQUAD_FLOAT64 *pTBiquad_Float64);
void Biquad_Float64_Init(BIQUAD_FLOAT64 *pTBiquad_Float64);
uint8 Biquad_Float64_Load(const BIQUAD_FLOAT64 *pTBiquad_Float64, uint8 data[], uint16 *dataLength, uint16 maxSize);
uint8 Biquad_Float64_Save(BIQUAD_FLOAT64 *pTBiquad_Float64, const uint8 data[], uint16 dataLength);
void* Biquad_Float64_GetAddress(const BIQUAD_FLOAT64 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
