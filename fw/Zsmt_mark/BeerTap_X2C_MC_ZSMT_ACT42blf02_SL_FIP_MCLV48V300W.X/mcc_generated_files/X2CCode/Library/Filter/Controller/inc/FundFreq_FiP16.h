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
#ifndef FUNDFREQ_FIP16_H
#define FUNDFREQ_FIP16_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(FUNDFREQ_FIP16_ISLINKED)
#define FUNDFREQ_FIP16_ID ((uint16)8017)

#if !defined(X2C_USE_UNION_FOR_POINTER)
typedef struct {
    uint16          ID;
    int16           *In;
    int16           *phi;
    int16           Out;
    uint16          cnt;
    int16           phi_old;
    int32           sum_a;
    int32           sum_b;
    int16           a;
    int16           b;
} FUNDFREQ_FIP16;
#else
typedef struct {
    uint16          ID;
    INT16_PTR       In;
    INT16_PTR       phi;
    int16           Out;
    uint16          cnt;
    int16           phi_old;
    int32           sum_a;
    int32           sum_b;
    int16           a;
    int16           b;
} FUNDFREQ_FIP16;
#endif

#define FUNDFREQ_FIP16_FUNCTIONS { \
    FUNDFREQ_FIP16_ID, \
    (void (*)(void*))FundFreq_FiP16_Update, \
    (void (*)(void*))FundFreq_FiP16_Init, \
    (tLoadImplementationParameter)Common_Load, \
    (tSaveImplementationParameter)Common_Save, \
    (void* (*)(const void*, uint16))FundFreq_FiP16_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void FundFreq_FiP16_Update(FUNDFREQ_FIP16 *pTFundFreq_FiP16);
void FundFreq_FiP16_Init(FUNDFREQ_FIP16 *pTFundFreq_FiP16);
void* FundFreq_FiP16_GetAddress(const FUNDFREQ_FIP16 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
