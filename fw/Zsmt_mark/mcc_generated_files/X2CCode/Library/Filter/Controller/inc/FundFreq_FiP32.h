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
#ifndef FUNDFREQ_FIP32_H
#define FUNDFREQ_FIP32_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(FUNDFREQ_FIP32_ISLINKED)
#define FUNDFREQ_FIP32_ID ((uint16)8018)

#if !defined(X2C_USE_UNION_FOR_POINTER)
typedef struct {
    uint16          ID;
    int32           *In;
    int32           *phi;
    int32           Out;
    uint32          cnt;
    int32           phi_old;
    int64           sum_a;
    int64           sum_b;
    int32           a;
    int32           b;
} FUNDFREQ_FIP32;
#else
typedef struct {
    uint16          ID;
    INT32_PTR       In;
    INT32_PTR       phi;
    int32           Out;
    uint32          cnt;
    int32           phi_old;
    int64           sum_a;
    int64           sum_b;
    int32           a;
    int32           b;
} FUNDFREQ_FIP32;
#endif

#define FUNDFREQ_FIP32_FUNCTIONS { \
    FUNDFREQ_FIP32_ID, \
    (void (*)(void*))FundFreq_FiP32_Update, \
    (void (*)(void*))FundFreq_FiP32_Init, \
    (tLoadImplementationParameter)Common_Load, \
    (tSaveImplementationParameter)Common_Save, \
    (void* (*)(const void*, uint16))FundFreq_FiP32_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void FundFreq_FiP32_Update(FUNDFREQ_FIP32 *pTFundFreq_FiP32);
void FundFreq_FiP32_Init(FUNDFREQ_FIP32 *pTFundFreq_FiP32);
void* FundFreq_FiP32_GetAddress(const FUNDFREQ_FIP32 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
