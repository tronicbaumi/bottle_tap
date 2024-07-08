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
#ifndef IIR_FLOAT32_H
#define IIR_FLOAT32_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(IIR_FLOAT32_ISLINKED)
#define IIR_FLOAT32_ID ((uint16)8099)

#if !defined(X2C_USE_UNION_FOR_POINTER)
typedef struct {
    uint16          ID;
    float32         *In;
    float32         Out;
    float32         *coeffB;
    float32         *coeffA;
    float32         *inputBuffer;
    float32         *outputBuffer;
    int8            indexIn;
    int8            indexOut;
    int8            orderN;
    int8            orderD;
} IIR_FLOAT32;
#else
typedef struct {
    uint16          ID;
    FLOAT32_PTR     In;
    float32         Out;
    FLOAT32_PTR     coeffB;
    FLOAT32_PTR     coeffA;
    FLOAT32_PTR     inputBuffer;
    FLOAT32_PTR     outputBuffer;
    int8            indexIn;
    int8            indexOut;
    int8            orderN;
    int8            orderD;
} IIR_FLOAT32;
#endif

#define IIR_FLOAT32_FUNCTIONS { \
    IIR_FLOAT32_ID, \
    (void (*)(void*))IIR_Float32_Update, \
    (void (*)(void*))IIR_Float32_Init, \
    (tLoadImplementationParameter)IIR_Float32_Load, \
    (tSaveImplementationParameter)IIR_Float32_Save, \
    (void* (*)(const void*, uint16))IIR_Float32_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void IIR_Float32_Update(IIR_FLOAT32 *pTIIR_Float32);
void IIR_Float32_Init(IIR_FLOAT32 *pTIIR_Float32);
uint8 IIR_Float32_Load(const IIR_FLOAT32 *pTIIR_Float32, uint8 data[], uint16 *dataLength, uint16 maxSize);
uint8 IIR_Float32_Save(IIR_FLOAT32 *pTIIR_Float32, const uint8 data[], uint16 dataLength);
void* IIR_Float32_GetAddress(const IIR_FLOAT32 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
