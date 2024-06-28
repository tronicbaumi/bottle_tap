/*
 * ===== CONFIDENTIAL =====
 * The content of this file is confidential according to the X2C Licence Terms and Conditions.
 *  
 * Copyright (c) 2014, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
/*
 * This file is part of X2C. http://x2c.lcm.at/
 * $LastChangedRevision: 2584 $
 * $LastChangedDate:: 2022-05-03 15:06:23 +0200#$
 */
/* USERCODE-BEGIN:Description                                                                                         */
/* Description: Calculation of fundamental wave.                              */
/* USERCODE-END:Description                                                                                           */
#ifndef FUNDFREQ_FLOAT64_H
#define FUNDFREQ_FLOAT64_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(FUNDFREQ_FLOAT64_ISLINKED)
#define FUNDFREQ_FLOAT64_ID ((uint16)8020)

#if !defined(X2C_USE_UNION_FOR_POINTER)
typedef struct {
    uint16          ID;
    float64         *In;
    float64         *phi;
    float64         Out;
    uint64          cnt;
    float64         phi_old;
    float64         sum_a;
    float64         sum_b;
    float64         a;
    float64         b;
} FUNDFREQ_FLOAT64;
#else
typedef struct {
    uint16          ID;
    FLOAT64_PTR     In;
    FLOAT64_PTR     phi;
    float64         Out;
    uint64          cnt;
    float64         phi_old;
    float64         sum_a;
    float64         sum_b;
    float64         a;
    float64         b;
} FUNDFREQ_FLOAT64;
#endif

#define FUNDFREQ_FLOAT64_FUNCTIONS { \
    FUNDFREQ_FLOAT64_ID, \
    (void (*)(void*))FundFreq_Float64_Update, \
    (void (*)(void*))FundFreq_Float64_Init, \
    (tLoadImplementationParameter)Common_Load, \
    (tSaveImplementationParameter)Common_Save, \
    (void* (*)(const void*, uint16))FundFreq_Float64_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void FundFreq_Float64_Update(FUNDFREQ_FLOAT64 *pTFundFreq_Float64);
void FundFreq_Float64_Init(FUNDFREQ_FLOAT64 *pTFundFreq_Float64);
void* FundFreq_Float64_GetAddress(const FUNDFREQ_FLOAT64 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
