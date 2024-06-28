/*
 * Copyright (c) 2018, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
/*
 * This file is part of X2C. http://x2c.lcm.at/
 * $LastChangedRevision: 2108 $
 * $LastChangedDate:: 2020-12-07 19:09:57 +0100#$
 */
/* USERCODE-BEGIN:Description                                                                                         */
/* Description: 
    Calculation of initial rotor angle. */
/* USERCODE-END:Description                                                                                           */
#ifndef INITPOSDETECT_FLOAT32_H
#define INITPOSDETECT_FLOAT32_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(INITPOSDETECT_FLOAT32_ISLINKED)
#define INITPOSDETECT_FLOAT32_ID ((uint16)9651)

#if !defined(X2C_USE_UNION_FOR_POINTER)
typedef struct {
    uint16          ID;
    float32         *I_A;
    float32         *I_B;
    float32         *I_C;
    bool            *Enable;
    float32         U_A;
    float32         U_B;
    float32         U_C;
    bool            Ready;
    float32         phi0;
    float32         u_pulse;
    int16           t_pulse;
    int16           t_period;
    int16           timer;
    int8            dir;
    float32         phi;
    float32         max_ia_pos;
    float32         max_ia_neg;
    float32         max_ib_pos;
    float32         max_ib_neg;
    float32         max_ic_pos;
    float32         max_ic_neg;
} INITPOSDETECT_FLOAT32;
#else
typedef struct {
    uint16          ID;
    FLOAT32_PTR     I_A;
    FLOAT32_PTR     I_B;
    FLOAT32_PTR     I_C;
    BOOL_PTR        Enable;
    float32         U_A;
    float32         U_B;
    float32         U_C;
    bool            Ready;
    float32         phi0;
    float32         u_pulse;
    int16           t_pulse;
    int16           t_period;
    int16           timer;
    int8            dir;
    float32         phi;
    float32         max_ia_pos;
    float32         max_ia_neg;
    float32         max_ib_pos;
    float32         max_ib_neg;
    float32         max_ic_pos;
    float32         max_ic_neg;
} INITPOSDETECT_FLOAT32;
#endif

#define INITPOSDETECT_FLOAT32_FUNCTIONS { \
    INITPOSDETECT_FLOAT32_ID, \
    (void (*)(void*))InitPosDetect_Float32_Update, \
    (void (*)(void*))InitPosDetect_Float32_Init, \
    (tLoadImplementationParameter)InitPosDetect_Float32_Load, \
    (tSaveImplementationParameter)InitPosDetect_Float32_Save, \
    (void* (*)(const void*, uint16))InitPosDetect_Float32_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void InitPosDetect_Float32_Update(INITPOSDETECT_FLOAT32 *pTInitPosDetect_Float32);
void InitPosDetect_Float32_Init(INITPOSDETECT_FLOAT32 *pTInitPosDetect_Float32);
uint8 InitPosDetect_Float32_Load(const INITPOSDETECT_FLOAT32 *pTInitPosDetect_Float32, uint8 data[], uint16 *dataLength, uint16 maxSize);
uint8 InitPosDetect_Float32_Save(INITPOSDETECT_FLOAT32 *pTInitPosDetect_Float32, const uint8 data[], uint16 dataLength);
void* InitPosDetect_Float32_GetAddress(const INITPOSDETECT_FLOAT32 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
