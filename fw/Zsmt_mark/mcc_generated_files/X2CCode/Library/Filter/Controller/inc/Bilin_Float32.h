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
#ifndef BILIN_FLOAT32_H
#define BILIN_FLOAT32_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(BILIN_FLOAT32_ISLINKED)
#define BILIN_FLOAT32_ID ((uint16)8067)

#if !defined(X2C_USE_UNION_FOR_POINTER)
typedef struct {
    uint16          ID;
    float32         *In;
    float32         Out;
    float32         b0;
    float32         b1;
    float32         a1;
    float32         in_old;
} BILIN_FLOAT32;
#else
typedef struct {
    uint16          ID;
    FLOAT32_PTR     In;
    float32         Out;
    float32         b0;
    float32         b1;
    float32         a1;
    float32         in_old;
} BILIN_FLOAT32;
#endif

#define BILIN_FLOAT32_FUNCTIONS { \
    BILIN_FLOAT32_ID, \
    (void (*)(void*))Bilin_Float32_Update, \
    (void (*)(void*))Bilin_Float32_Init, \
    (tLoadImplementationParameter)Bilin_Float32_Load, \
    (tSaveImplementationParameter)Bilin_Float32_Save, \
    (void* (*)(const void*, uint16))Bilin_Float32_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void Bilin_Float32_Update(BILIN_FLOAT32 *pTBilin_Float32);
void Bilin_Float32_Init(BILIN_FLOAT32 *pTBilin_Float32);
uint8 Bilin_Float32_Load(const BILIN_FLOAT32 *pTBilin_Float32, uint8 data[], uint16 *dataLength, uint16 maxSize);
uint8 Bilin_Float32_Save(BILIN_FLOAT32 *pTBilin_Float32, const uint8 data[], uint16 dataLength);
void* Bilin_Float32_GetAddress(const BILIN_FLOAT32 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
