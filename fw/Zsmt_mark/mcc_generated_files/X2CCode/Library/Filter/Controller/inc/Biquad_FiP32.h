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
#ifndef BIQUAD_FIP32_H
#define BIQUAD_FIP32_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(BIQUAD_FIP32_ISLINKED)
#define BIQUAD_FIP32_ID ((uint16)8082)

#if !defined(X2C_USE_UNION_FOR_POINTER)
typedef struct {
    uint16          ID;
    int32           *In;
    int32           Out;
    int32           b0;
    int32           b1;
    int32           b2;
    int32           a1;
    int32           a2;
    int8            sfrb0;
    int8            sfrb1;
    int8            sfrb2;
    int8            sfra1;
    int8            sfra2;
    int32           in_old;
    int32           in_veryold;
    int32           out_old;
    int32           out_veryold;
} BIQUAD_FIP32;
#else
typedef struct {
    uint16          ID;
    INT32_PTR       In;
    int32           Out;
    int32           b0;
    int32           b1;
    int32           b2;
    int32           a1;
    int32           a2;
    int8            sfrb0;
    int8            sfrb1;
    int8            sfrb2;
    int8            sfra1;
    int8            sfra2;
    int32           in_old;
    int32           in_veryold;
    int32           out_old;
    int32           out_veryold;
} BIQUAD_FIP32;
#endif

#define BIQUAD_FIP32_FUNCTIONS { \
    BIQUAD_FIP32_ID, \
    (void (*)(void*))Biquad_FiP32_Update, \
    (void (*)(void*))Biquad_FiP32_Init, \
    (tLoadImplementationParameter)Biquad_FiP32_Load, \
    (tSaveImplementationParameter)Biquad_FiP32_Save, \
    (void* (*)(const void*, uint16))Biquad_FiP32_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void Biquad_FiP32_Update(BIQUAD_FIP32 *pTBiquad_FiP32);
void Biquad_FiP32_Init(BIQUAD_FIP32 *pTBiquad_FiP32);
uint8 Biquad_FiP32_Load(const BIQUAD_FIP32 *pTBiquad_FiP32, uint8 data[], uint16 *dataLength, uint16 maxSize);
uint8 Biquad_FiP32_Save(BIQUAD_FIP32 *pTBiquad_FiP32, const uint8 data[], uint16 dataLength);
void* Biquad_FiP32_GetAddress(const BIQUAD_FIP32 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
