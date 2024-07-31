/*
 * ===== CONFIDENTIAL =====
 * The content of this file is confidential according to the X2C Licence Terms and Conditions.
 *  
 * Copyright (c) 2019, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
/*
 * This file is part of X2C. http://x2c.lcm.at/
 * $LastChangedRevision: 2584 $
 */
/* USERCODE-BEGIN:Description                                                                                         */
/* Description: */
/* USERCODE-END:Description                                                                                           */
#ifndef BILIN_FLOAT64_H
#define BILIN_FLOAT64_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(BILIN_FLOAT64_ISLINKED)
#define BILIN_FLOAT64_ID ((uint16)8068)

#if !defined(X2C_USE_UNION_FOR_POINTER)
typedef struct {
    uint16          ID;
    float64         *In;
    float64         Out;
    float64         b0;
    float64         b1;
    float64         a1;
    float64         in_old;
} BILIN_FLOAT64;
#else
typedef struct {
    uint16          ID;
    FLOAT64_PTR     In;
    float64         Out;
    float64         b0;
    float64         b1;
    float64         a1;
    float64         in_old;
} BILIN_FLOAT64;
#endif

#define BILIN_FLOAT64_FUNCTIONS { \
    BILIN_FLOAT64_ID, \
    (void (*)(void*))Bilin_Float64_Update, \
    (void (*)(void*))Bilin_Float64_Init, \
    (tLoadImplementationParameter)Bilin_Float64_Load, \
    (tSaveImplementationParameter)Bilin_Float64_Save, \
    (void* (*)(const void*, uint16))Bilin_Float64_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void Bilin_Float64_Update(BILIN_FLOAT64 *pTBilin_Float64);
void Bilin_Float64_Init(BILIN_FLOAT64 *pTBilin_Float64);
uint8 Bilin_Float64_Load(const BILIN_FLOAT64 *pTBilin_Float64, uint8 data[], uint16 *dataLength, uint16 maxSize);
uint8 Bilin_Float64_Save(BILIN_FLOAT64 *pTBilin_Float64, const uint8 data[], uint16 dataLength);
void* Bilin_Float64_GetAddress(const BILIN_FLOAT64 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
