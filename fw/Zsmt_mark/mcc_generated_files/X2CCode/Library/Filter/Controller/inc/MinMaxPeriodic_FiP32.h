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
#ifndef MINMAXPERIODIC_FIP32_H
#define MINMAXPERIODIC_FIP32_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(MINMAXPERIODIC_FIP32_ISLINKED)
#define MINMAXPERIODIC_FIP32_ID ((uint16)8034)

#if !defined(X2C_USE_UNION_FOR_POINTER)
typedef struct {
    uint16          ID;
    int32           *In;
    int32           *phi;
    int32           max;
    int32           min;
    int32           min_act;
    int32           max_act;
    int32           phi_old;
} MINMAXPERIODIC_FIP32;
#else
typedef struct {
    uint16          ID;
    INT32_PTR       In;
    INT32_PTR       phi;
    int32           max;
    int32           min;
    int32           min_act;
    int32           max_act;
    int32           phi_old;
} MINMAXPERIODIC_FIP32;
#endif

#define MINMAXPERIODIC_FIP32_FUNCTIONS { \
    MINMAXPERIODIC_FIP32_ID, \
    (void (*)(void*))MinMaxPeriodic_FiP32_Update, \
    (void (*)(void*))MinMaxPeriodic_FiP32_Init, \
    (tLoadImplementationParameter)Common_Load, \
    (tSaveImplementationParameter)Common_Save, \
    (void* (*)(const void*, uint16))MinMaxPeriodic_FiP32_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void MinMaxPeriodic_FiP32_Update(MINMAXPERIODIC_FIP32 *pTMinMaxPeriodic_FiP32);
void MinMaxPeriodic_FiP32_Init(MINMAXPERIODIC_FIP32 *pTMinMaxPeriodic_FiP32);
void* MinMaxPeriodic_FiP32_GetAddress(const MINMAXPERIODIC_FIP32 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
