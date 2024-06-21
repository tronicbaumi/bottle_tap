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
#ifndef INITPOSDETECT_FLOAT64_H
#define INITPOSDETECT_FLOAT64_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(INITPOSDETECT_FLOAT64_ISLINKED)
#define INITPOSDETECT_FLOAT64_ID ((uint16)9652)

#if !defined(X2C_USE_UNION_FOR_POINTER)
typedef struct {
    uint16          ID;
    float64         *I_A;
    float64         *I_B;
    float64         *I_C;
    bool            *Enable;
    float64         U_A;
    float64         U_B;
    float64         U_C;
    float64         Ready;
    float64         phi0;
    float64         u_pulse;
    int16           t_pulse;
    int16           t_period;
    int16           timer;
    int8            dir;
    float64         phi;
    float64         max_ia_pos;
    float64         max_ia_neg;
    float64         max_ib_pos;
    float64         max_ib_neg;
    float64         max_ic_pos;
    float64         max_ic_neg;
} INITPOSDETECT_FLOAT64;
#else
typedef struct {
    uint16          ID;
    FLOAT64_PTR     I_A;
    FLOAT64_PTR     I_B;
    FLOAT64_PTR     I_C;
    BOOL_PTR        Enable;
    float64         U_A;
    float64         U_B;
    float64         U_C;
    float64         Ready;
    float64         phi0;
    float64         u_pulse;
    int16           t_pulse;
    int16           t_period;
    int16           timer;
    int8            dir;
    float64         phi;
    float64         max_ia_pos;
    float64         max_ia_neg;
    float64         max_ib_pos;
    float64         max_ib_neg;
    float64         max_ic_pos;
    float64         max_ic_neg;
} INITPOSDETECT_FLOAT64;
#endif

#define INITPOSDETECT_FLOAT64_FUNCTIONS { \
    INITPOSDETECT_FLOAT64_ID, \
    (void (*)(void*))InitPosDetect_Float64_Update, \
    (void (*)(void*))InitPosDetect_Float64_Init, \
    (tLoadImplementationParameter)InitPosDetect_Float64_Load, \
    (tSaveImplementationParameter)InitPosDetect_Float64_Save, \
    (void* (*)(const void*, uint16))InitPosDetect_Float64_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void InitPosDetect_Float64_Update(INITPOSDETECT_FLOAT64 *pTInitPosDetect_Float64);
void InitPosDetect_Float64_Init(INITPOSDETECT_FLOAT64 *pTInitPosDetect_Float64);
uint8 InitPosDetect_Float64_Load(const INITPOSDETECT_FLOAT64 *pTInitPosDetect_Float64, uint8 data[], uint16 *dataLength, uint16 maxSize);
uint8 InitPosDetect_Float64_Save(INITPOSDETECT_FLOAT64 *pTInitPosDetect_Float64, const uint8 data[], uint16 dataLength);
void* InitPosDetect_Float64_GetAddress(const INITPOSDETECT_FLOAT64 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
