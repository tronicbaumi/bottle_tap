/*
 * ===== CONFIDENTIAL =====
 * The content of this file is confidential according to the X2C Licence Terms and Conditions.
 *  
 * Copyright (c) 2013, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
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
#ifndef MINMAXPERIODIC_FLOAT32_H
#define MINMAXPERIODIC_FLOAT32_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(MINMAXPERIODIC_FLOAT32_ISLINKED)
#define MINMAXPERIODIC_FLOAT32_ID ((uint16)8035)

#if !defined(X2C_USE_UNION_FOR_POINTER)
typedef struct {
    uint16          ID;
    float32         *In;
    float32         *phi;
    float32         max;
    float32         min;
    float32         min_act;
    float32         max_act;
    float32         phi_old;
} MINMAXPERIODIC_FLOAT32;
#else
typedef struct {
    uint16          ID;
    FLOAT32_PTR     In;
    FLOAT32_PTR     phi;
    float32         max;
    float32         min;
    float32         min_act;
    float32         max_act;
    float32         phi_old;
} MINMAXPERIODIC_FLOAT32;
#endif

#define MINMAXPERIODIC_FLOAT32_FUNCTIONS { \
    MINMAXPERIODIC_FLOAT32_ID, \
    (void (*)(void*))MinMaxPeriodic_Float32_Update, \
    (void (*)(void*))MinMaxPeriodic_Float32_Init, \
    (tLoadImplementationParameter)Common_Load, \
    (tSaveImplementationParameter)Common_Save, \
    (void* (*)(const void*, uint16))MinMaxPeriodic_Float32_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void MinMaxPeriodic_Float32_Update(MINMAXPERIODIC_FLOAT32 *pTMinMaxPeriodic_Float32);
void MinMaxPeriodic_Float32_Init(MINMAXPERIODIC_FLOAT32 *pTMinMaxPeriodic_Float32);
void* MinMaxPeriodic_Float32_GetAddress(const MINMAXPERIODIC_FLOAT32 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
