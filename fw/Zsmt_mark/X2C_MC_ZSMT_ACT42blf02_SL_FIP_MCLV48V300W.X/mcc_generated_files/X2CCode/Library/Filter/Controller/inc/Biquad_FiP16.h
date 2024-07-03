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
#ifndef BIQUAD_FIP16_H
#define BIQUAD_FIP16_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(BIQUAD_FIP16_ISLINKED)
#define BIQUAD_FIP16_ID ((uint16)8081)

#if !defined(X2C_USE_UNION_FOR_POINTER)
typedef struct {
    uint16          ID;
    int16           *In;
    int16           Out;
    int16           b0;
    int16           b1;
    int16           b2;
    int16           a1;
    int16           a2;
    int8            sfrb0;
    int8            sfrb1;
    int8            sfrb2;
    int8            sfra1;
    int8            sfra2;
    int16           in_old;
    int16           in_veryold;
    int16           out_old;
    int16           out_veryold;
} BIQUAD_FIP16;
#else
typedef struct {
    uint16          ID;
    INT16_PTR       In;
    int16           Out;
    int16           b0;
    int16           b1;
    int16           b2;
    int16           a1;
    int16           a2;
    int8            sfrb0;
    int8            sfrb1;
    int8            sfrb2;
    int8            sfra1;
    int8            sfra2;
    int16           in_old;
    int16           in_veryold;
    int16           out_old;
    int16           out_veryold;
} BIQUAD_FIP16;
#endif

#define BIQUAD_FIP16_FUNCTIONS { \
    BIQUAD_FIP16_ID, \
    (void (*)(void*))Biquad_FiP16_Update, \
    (void (*)(void*))Biquad_FiP16_Init, \
    (tLoadImplementationParameter)Biquad_FiP16_Load, \
    (tSaveImplementationParameter)Biquad_FiP16_Save, \
    (void* (*)(const void*, uint16))Biquad_FiP16_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void Biquad_FiP16_Update(BIQUAD_FIP16 *pTBiquad_FiP16);
void Biquad_FiP16_Init(BIQUAD_FIP16 *pTBiquad_FiP16);
uint8 Biquad_FiP16_Load(const BIQUAD_FIP16 *pTBiquad_FiP16, uint8 data[], uint16 *dataLength, uint16 maxSize);
uint8 Biquad_FiP16_Save(BIQUAD_FIP16 *pTBiquad_FiP16, const uint8 data[], uint16 dataLength);
void* Biquad_FiP16_GetAddress(const BIQUAD_FIP16 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
