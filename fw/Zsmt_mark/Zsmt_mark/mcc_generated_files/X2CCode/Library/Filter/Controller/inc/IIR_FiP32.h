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
#ifndef IIR_FIP32_H
#define IIR_FIP32_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(IIR_FIP32_ISLINKED)
#define IIR_FIP32_ID ((uint16)8098)

#if !defined(X2C_USE_UNION_FOR_POINTER)
typedef struct {
    uint16          ID;
    int32           *In;
    int32           Out;
    int32           *coeffB;
    int32           *coeffA;
    int8            sfrB;
    int8            sfrA;
    int32           *inputBuffer;
    int32           *outputBuffer;
    int8            indexIn;
    int8            indexOut;
    int8            orderN;
    int8            orderD;
} IIR_FIP32;
#else
typedef struct {
    uint16          ID;
    INT32_PTR       In;
    int32           Out;
    INT32_PTR       coeffB;
    INT32_PTR       coeffA;
    int8            sfrB;
    int8            sfrA;
    INT32_PTR       inputBuffer;
    INT32_PTR       outputBuffer;
    int8            indexIn;
    int8            indexOut;
    int8            orderN;
    int8            orderD;
} IIR_FIP32;
#endif

#define IIR_FIP32_FUNCTIONS { \
    IIR_FIP32_ID, \
    (void (*)(void*))IIR_FiP32_Update, \
    (void (*)(void*))IIR_FiP32_Init, \
    (tLoadImplementationParameter)IIR_FiP32_Load, \
    (tSaveImplementationParameter)IIR_FiP32_Save, \
    (void* (*)(const void*, uint16))IIR_FiP32_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void IIR_FiP32_Update(IIR_FIP32 *pTIIR_FiP32);
void IIR_FiP32_Init(IIR_FIP32 *pTIIR_FiP32);
uint8 IIR_FiP32_Load(const IIR_FIP32 *pTIIR_FiP32, uint8 data[], uint16 *dataLength, uint16 maxSize);
uint8 IIR_FiP32_Save(IIR_FIP32 *pTIIR_FiP32, const uint8 data[], uint16 dataLength);
void* IIR_FiP32_GetAddress(const IIR_FIP32 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
