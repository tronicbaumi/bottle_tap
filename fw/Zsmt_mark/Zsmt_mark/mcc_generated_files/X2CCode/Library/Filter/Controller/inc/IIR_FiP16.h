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
#ifndef IIR_FIP16_H
#define IIR_FIP16_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(IIR_FIP16_ISLINKED)
#define IIR_FIP16_ID ((uint16)8097)

#if !defined(X2C_USE_UNION_FOR_POINTER)
typedef struct {
    uint16          ID;
    int16           *In;
    int16           Out;
    int16           *coeffB;
    int16           *coeffA;
    int8            sfrB;
    int8            sfrA;
    int16           *inputBuffer;
    int16           *outputBuffer;
    int8            indexIn;
    int8            indexOut;
    int8            orderN;
    int8            orderD;
} IIR_FIP16;
#else
typedef struct {
    uint16          ID;
    INT16_PTR       In;
    int16           Out;
    INT16_PTR       coeffB;
    INT16_PTR       coeffA;
    int8            sfrB;
    int8            sfrA;
    INT16_PTR       inputBuffer;
    INT16_PTR       outputBuffer;
    int8            indexIn;
    int8            indexOut;
    int8            orderN;
    int8            orderD;
} IIR_FIP16;
#endif

#define IIR_FIP16_FUNCTIONS { \
    IIR_FIP16_ID, \
    (void (*)(void*))IIR_FiP16_Update, \
    (void (*)(void*))IIR_FiP16_Init, \
    (tLoadImplementationParameter)IIR_FiP16_Load, \
    (tSaveImplementationParameter)IIR_FiP16_Save, \
    (void* (*)(const void*, uint16))IIR_FiP16_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void IIR_FiP16_Update(IIR_FIP16 *pTIIR_FiP16);
void IIR_FiP16_Init(IIR_FIP16 *pTIIR_FiP16);
uint8 IIR_FiP16_Load(const IIR_FIP16 *pTIIR_FiP16, uint8 data[], uint16 *dataLength, uint16 maxSize);
uint8 IIR_FiP16_Save(IIR_FIP16 *pTIIR_FiP16, const uint8 data[], uint16 dataLength);
void* IIR_FiP16_GetAddress(const IIR_FIP16 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
