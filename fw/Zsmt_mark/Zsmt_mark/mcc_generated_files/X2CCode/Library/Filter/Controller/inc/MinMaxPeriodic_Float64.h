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
#ifndef MINMAXPERIODIC_FLOAT64_H
#define MINMAXPERIODIC_FLOAT64_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(MINMAXPERIODIC_FLOAT64_ISLINKED)
#define MINMAXPERIODIC_FLOAT64_ID ((uint16)8036)

#if !defined(X2C_USE_UNION_FOR_POINTER)
typedef struct {
    uint16          ID;
    float64         *In;
    float64         *phi;
    float64         max;
    float64         min;
    float64         min_act;
    float64         max_act;
    float64         phi_old;
} MINMAXPERIODIC_FLOAT64;
#else
typedef struct {
    uint16          ID;
    FLOAT64_PTR     In;
    FLOAT64_PTR     phi;
    float64         max;
    float64         min;
    float64         min_act;
    float64         max_act;
    float64         phi_old;
} MINMAXPERIODIC_FLOAT64;
#endif

#define MINMAXPERIODIC_FLOAT64_FUNCTIONS { \
    MINMAXPERIODIC_FLOAT64_ID, \
    (void (*)(void*))MinMaxPeriodic_Float64_Update, \
    (void (*)(void*))MinMaxPeriodic_Float64_Init, \
    (tLoadImplementationParameter)Common_Load, \
    (tSaveImplementationParameter)Common_Save, \
    (void* (*)(const void*, uint16))MinMaxPeriodic_Float64_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void MinMaxPeriodic_Float64_Update(MINMAXPERIODIC_FLOAT64 *pTMinMaxPeriodic_Float64);
void MinMaxPeriodic_Float64_Init(MINMAXPERIODIC_FLOAT64 *pTMinMaxPeriodic_Float64);
void* MinMaxPeriodic_Float64_GetAddress(const MINMAXPERIODIC_FLOAT64 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
