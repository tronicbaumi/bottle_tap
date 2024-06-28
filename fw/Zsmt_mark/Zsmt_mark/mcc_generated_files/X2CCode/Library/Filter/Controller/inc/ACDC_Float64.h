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
/* Description: Calculation of AC and DC component.                           */
/* USERCODE-END:Description                                                                                           */
#ifndef ACDC_FLOAT64_H
#define ACDC_FLOAT64_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(ACDC_FLOAT64_ISLINKED)
#define ACDC_FLOAT64_ID ((uint16)8004)

#if !defined(X2C_USE_UNION_FOR_POINTER)
typedef struct {
    uint16          ID;
    float64         *In;
    float64         *phi;
    float64         AC;
    float64         DC;
    uint64          cnt;
    float64         phi_old;
    float64         sum;
} ACDC_FLOAT64;
#else
typedef struct {
    uint16          ID;
    FLOAT64_PTR     In;
    FLOAT64_PTR     phi;
    float64         AC;
    float64         DC;
    uint64          cnt;
    float64         phi_old;
    float64         sum;
} ACDC_FLOAT64;
#endif

#define ACDC_FLOAT64_FUNCTIONS { \
    ACDC_FLOAT64_ID, \
    (void (*)(void*))ACDC_Float64_Update, \
    (void (*)(void*))ACDC_Float64_Init, \
    (tLoadImplementationParameter)Common_Load, \
    (tSaveImplementationParameter)Common_Save, \
    (void* (*)(const void*, uint16))ACDC_Float64_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void ACDC_Float64_Update(ACDC_FLOAT64 *pTACDC_Float64);
void ACDC_Float64_Init(ACDC_FLOAT64 *pTACDC_Float64);
void* ACDC_Float64_GetAddress(const ACDC_FLOAT64 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
