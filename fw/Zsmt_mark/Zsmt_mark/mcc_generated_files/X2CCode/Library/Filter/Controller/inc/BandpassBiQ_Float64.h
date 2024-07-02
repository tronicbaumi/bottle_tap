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
#ifndef BANDPASSBIQ_FLOAT64_H
#define BANDPASSBIQ_FLOAT64_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(BANDPASSBIQ_FLOAT64_ISLINKED)
#define BANDPASSBIQ_FLOAT64_ID ((uint16)8164)

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
} BANDPASSBIQ_FLOAT64;
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
} BANDPASSBIQ_FLOAT64;
#endif

#define BANDPASSBIQ_FLOAT64_FUNCTIONS { \
    BANDPASSBIQ_FLOAT64_ID, \
    (void (*)(void*))BandpassBiQ_Float64_Update, \
    (void (*)(void*))BandpassBiQ_Float64_Init, \
    (tLoadImplementationParameter)BandpassBiQ_Float64_Load, \
    (tSaveImplementationParameter)BandpassBiQ_Float64_Save, \
    (void* (*)(const void*, uint16))BandpassBiQ_Float64_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void BandpassBiQ_Float64_Update(BANDPASSBIQ_FLOAT64 *pTBandpassBiQ_Float64);
void BandpassBiQ_Float64_Init(BANDPASSBIQ_FLOAT64 *pTBandpassBiQ_Float64);
uint8 BandpassBiQ_Float64_Load(const BANDPASSBIQ_FLOAT64 *pTBandpassBiQ_Float64, uint8 data[], uint16 *dataLength, uint16 maxSize);
uint8 BandpassBiQ_Float64_Save(BANDPASSBIQ_FLOAT64 *pTBandpassBiQ_Float64, const uint8 data[], uint16 dataLength);
void* BandpassBiQ_Float64_GetAddress(const BANDPASSBIQ_FLOAT64 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
