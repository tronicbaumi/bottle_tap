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
#ifndef ACDC_FIP32_H
#define ACDC_FIP32_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(ACDC_FIP32_ISLINKED)
#define ACDC_FIP32_ID ((uint16)8002)

#if !defined(X2C_USE_UNION_FOR_POINTER)
typedef struct {
    uint16          ID;
    int32           *In;
    int32           *phi;
    int32           AC;
    int32           DC;
    uint32          cnt;
    int32           phi_old;
    int64           sum;
} ACDC_FIP32;
#else
typedef struct {
    uint16          ID;
    INT32_PTR       In;
    INT32_PTR       phi;
    int32           AC;
    int32           DC;
    uint32          cnt;
    int32           phi_old;
    int64           sum;
} ACDC_FIP32;
#endif

#define ACDC_FIP32_FUNCTIONS { \
    ACDC_FIP32_ID, \
    (void (*)(void*))ACDC_FiP32_Update, \
    (void (*)(void*))ACDC_FiP32_Init, \
    (tLoadImplementationParameter)Common_Load, \
    (tSaveImplementationParameter)Common_Save, \
    (void* (*)(const void*, uint16))ACDC_FiP32_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void ACDC_FiP32_Update(ACDC_FIP32 *pTACDC_FiP32);
void ACDC_FiP32_Init(ACDC_FIP32 *pTACDC_FiP32);
void* ACDC_FiP32_GetAddress(const ACDC_FIP32 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
