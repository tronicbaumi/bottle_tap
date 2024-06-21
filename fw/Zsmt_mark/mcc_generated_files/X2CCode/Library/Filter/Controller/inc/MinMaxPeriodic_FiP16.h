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
#ifndef MINMAXPERIODIC_FIP16_H
#define MINMAXPERIODIC_FIP16_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(MINMAXPERIODIC_FIP16_ISLINKED)
#define MINMAXPERIODIC_FIP16_ID ((uint16)8033)

#if !defined(X2C_USE_UNION_FOR_POINTER)
typedef struct {
    uint16          ID;
    int16           *In;
    int16           *phi;
    int16           max;
    int16           min;
    int16           min_act;
    int16           max_act;
    int16           phi_old;
} MINMAXPERIODIC_FIP16;
#else
typedef struct {
    uint16          ID;
    INT16_PTR       In;
    INT16_PTR       phi;
    int16           max;
    int16           min;
    int16           min_act;
    int16           max_act;
    int16           phi_old;
} MINMAXPERIODIC_FIP16;
#endif

#define MINMAXPERIODIC_FIP16_FUNCTIONS { \
    MINMAXPERIODIC_FIP16_ID, \
    (void (*)(void*))MinMaxPeriodic_FiP16_Update, \
    (void (*)(void*))MinMaxPeriodic_FiP16_Init, \
    (tLoadImplementationParameter)Common_Load, \
    (tSaveImplementationParameter)Common_Save, \
    (void* (*)(const void*, uint16))MinMaxPeriodic_FiP16_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void MinMaxPeriodic_FiP16_Update(MINMAXPERIODIC_FIP16 *pTMinMaxPeriodic_FiP16);
void MinMaxPeriodic_FiP16_Init(MINMAXPERIODIC_FIP16 *pTMinMaxPeriodic_FiP16);
void* MinMaxPeriodic_FiP16_GetAddress(const MINMAXPERIODIC_FIP16 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
