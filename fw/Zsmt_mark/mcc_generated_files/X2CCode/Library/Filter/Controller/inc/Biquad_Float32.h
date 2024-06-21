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
#ifndef BIQUAD_FLOAT32_H
#define BIQUAD_FLOAT32_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(BIQUAD_FLOAT32_ISLINKED)
#define BIQUAD_FLOAT32_ID ((uint16)8083)

#if !defined(X2C_USE_UNION_FOR_POINTER)
typedef struct {
    uint16          ID;
    float32         *In;
    float32         Out;
    float32         b0;
    float32         b1;
    float32         b2;
    float32         a1;
    float32         a2;
    float32         in_old;
    float32         in_veryold;
    float32         out_old;
    float32         out_veryold;
} BIQUAD_FLOAT32;
#else
typedef struct {
    uint16          ID;
    FLOAT32_PTR     In;
    float32         Out;
    float32         b0;
    float32         b1;
    float32         b2;
    float32         a1;
    float32         a2;
    float32         in_old;
    float32         in_veryold;
    float32         out_old;
    float32         out_veryold;
} BIQUAD_FLOAT32;
#endif

#define BIQUAD_FLOAT32_FUNCTIONS { \
    BIQUAD_FLOAT32_ID, \
    (void (*)(void*))Biquad_Float32_Update, \
    (void (*)(void*))Biquad_Float32_Init, \
    (tLoadImplementationParameter)Biquad_Float32_Load, \
    (tSaveImplementationParameter)Biquad_Float32_Save, \
    (void* (*)(const void*, uint16))Biquad_Float32_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void Biquad_Float32_Update(BIQUAD_FLOAT32 *pTBiquad_Float32);
void Biquad_Float32_Init(BIQUAD_FLOAT32 *pTBiquad_Float32);
uint8 Biquad_Float32_Load(const BIQUAD_FLOAT32 *pTBiquad_Float32, uint8 data[], uint16 *dataLength, uint16 maxSize);
uint8 Biquad_Float32_Save(BIQUAD_FLOAT32 *pTBiquad_Float32, const uint8 data[], uint16 dataLength);
void* Biquad_Float32_GetAddress(const BIQUAD_FLOAT32 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
