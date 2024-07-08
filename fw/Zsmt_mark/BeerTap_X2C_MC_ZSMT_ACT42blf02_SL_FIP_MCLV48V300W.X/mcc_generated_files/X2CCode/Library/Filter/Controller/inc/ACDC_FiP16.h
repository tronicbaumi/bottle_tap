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
#ifndef ACDC_FIP16_H
#define ACDC_FIP16_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(ACDC_FIP16_ISLINKED)
#define ACDC_FIP16_ID ((uint16)8001)

#if !defined(X2C_USE_UNION_FOR_POINTER)
typedef struct {
    uint16          ID;
    int16           *In;
    int16           *phi;
    int16           AC;
    int16           DC;
    uint16          cnt;
    int16           phi_old;
    int32           sum;
} ACDC_FIP16;
#else
typedef struct {
    uint16          ID;
    INT16_PTR       In;
    INT16_PTR       phi;
    int16           AC;
    int16           DC;
    uint16          cnt;
    int16           phi_old;
    int32           sum;
} ACDC_FIP16;
#endif

#define ACDC_FIP16_FUNCTIONS { \
    ACDC_FIP16_ID, \
    (void (*)(void*))ACDC_FiP16_Update, \
    (void (*)(void*))ACDC_FiP16_Init, \
    (tLoadImplementationParameter)Common_Load, \
    (tSaveImplementationParameter)Common_Save, \
    (void* (*)(const void*, uint16))ACDC_FiP16_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void ACDC_FiP16_Update(ACDC_FIP16 *pTACDC_FiP16);
void ACDC_FiP16_Init(ACDC_FIP16 *pTACDC_FiP16);
void* ACDC_FiP16_GetAddress(const ACDC_FIP16 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
