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
#ifndef IIR_FLOAT64_H
#define IIR_FLOAT64_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(IIR_FLOAT64_ISLINKED)
#define IIR_FLOAT64_ID ((uint16)8100)

#if !defined(X2C_USE_UNION_FOR_POINTER)
typedef struct {
    uint16          ID;
    float64         *In;
    float64         Out;
    float64         *coeffB;
    float64         *coeffA;
    float64         *inputBuffer;
    float64         *outputBuffer;
    int8            indexIn;
    int8            indexOut;
    int8            orderN;
    int8            orderD;
} IIR_FLOAT64;
#else
typedef struct {
    uint16          ID;
    FLOAT64_PTR     In;
    float64         Out;
    FLOAT64_PTR     coeffB;
    FLOAT64_PTR     coeffA;
    FLOAT64_PTR     inputBuffer;
    FLOAT64_PTR     outputBuffer;
    int8            indexIn;
    int8            indexOut;
    int8            orderN;
    int8            orderD;
} IIR_FLOAT64;
#endif

#define IIR_FLOAT64_FUNCTIONS { \
    IIR_FLOAT64_ID, \
    (void (*)(void*))IIR_Float64_Update, \
    (void (*)(void*))IIR_Float64_Init, \
    (tLoadImplementationParameter)IIR_Float64_Load, \
    (tSaveImplementationParameter)IIR_Float64_Save, \
    (void* (*)(const void*, uint16))IIR_Float64_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void IIR_Float64_Update(IIR_FLOAT64 *pTIIR_Float64);
void IIR_Float64_Init(IIR_FLOAT64 *pTIIR_Float64);
uint8 IIR_Float64_Load(const IIR_FLOAT64 *pTIIR_Float64, uint8 data[], uint16 *dataLength, uint16 maxSize);
uint8 IIR_Float64_Save(IIR_FLOAT64 *pTIIR_Float64, const uint8 data[], uint16 dataLength);
void* IIR_Float64_GetAddress(const IIR_FLOAT64 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
