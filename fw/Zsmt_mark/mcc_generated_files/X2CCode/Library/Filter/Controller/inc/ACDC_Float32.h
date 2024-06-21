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
#ifndef ACDC_FLOAT32_H
#define ACDC_FLOAT32_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(ACDC_FLOAT32_ISLINKED)
#define ACDC_FLOAT32_ID ((uint16)8003)

#if !defined(X2C_USE_UNION_FOR_POINTER)
typedef struct {
    uint16          ID;
    float32         *In;
    float32         *phi;
    float32         AC;
    float32         DC;
    uint32          cnt;
    float32         phi_old;
    float32         sum;
} ACDC_FLOAT32;
#else
typedef struct {
    uint16          ID;
    FLOAT32_PTR     In;
    FLOAT32_PTR     phi;
    float32         AC;
    float32         DC;
    uint32          cnt;
    float32         phi_old;
    float32         sum;
} ACDC_FLOAT32;
#endif

#define ACDC_FLOAT32_FUNCTIONS { \
    ACDC_FLOAT32_ID, \
    (void (*)(void*))ACDC_Float32_Update, \
    (void (*)(void*))ACDC_Float32_Init, \
    (tLoadImplementationParameter)Common_Load, \
    (tSaveImplementationParameter)Common_Save, \
    (void* (*)(const void*, uint16))ACDC_Float32_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void ACDC_Float32_Update(ACDC_FLOAT32 *pTACDC_Float32);
void ACDC_Float32_Init(ACDC_FLOAT32 *pTACDC_Float32);
void* ACDC_Float32_GetAddress(const ACDC_FLOAT32 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
