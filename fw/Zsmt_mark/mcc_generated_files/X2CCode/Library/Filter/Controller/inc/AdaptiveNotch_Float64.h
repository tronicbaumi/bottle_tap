/*
 * ===== CONFIDENTIAL =====
 * The content of this file is confidential according to the X2C Licence Terms and Conditions.
 *  
 * Copyright (c) 2019, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
/*
 * This file is part of X2C. http://x2c.lcm.at/
 * $LastChangedRevision: 2584 $
 */
/* USERCODE-BEGIN:Description                                                                                         */
/* Description: */
/* USERCODE-END:Description                                                                                           */
#ifndef ADAPTIVENOTCH_FLOAT64_H
#define ADAPTIVENOTCH_FLOAT64_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(ADAPTIVENOTCH_FLOAT64_ISLINKED)
#define ADAPTIVENOTCH_FLOAT64_ID ((uint16)8052)

#if !defined(X2C_USE_UNION_FOR_POINTER)
typedef struct {
    uint16          ID;
    float64         *In;
    float64         *n;
    float64         Out;
    float64         a_fact;
    float64         b_fact;
    float64         c_fact;
    float64         a1;
    float64         a2;
    float64         b1;
    float64         k;
    float64         in_old;
    float64         in_very_old;
    float64         out_old;
    float64         out_very_old;
    float64         n_old;
    float64         n_thresh;
} ADAPTIVENOTCH_FLOAT64;
#else
typedef struct {
    uint16          ID;
    FLOAT64_PTR     In;
    FLOAT64_PTR     n;
    float64         Out;
    float64         a_fact;
    float64         b_fact;
    float64         c_fact;
    float64         a1;
    float64         a2;
    float64         b1;
    float64         k;
    float64         in_old;
    float64         in_very_old;
    float64         out_old;
    float64         out_very_old;
    float64         n_old;
    float64         n_thresh;
} ADAPTIVENOTCH_FLOAT64;
#endif

#define ADAPTIVENOTCH_FLOAT64_FUNCTIONS { \
    ADAPTIVENOTCH_FLOAT64_ID, \
    (void (*)(void*))AdaptiveNotch_Float64_Update, \
    (void (*)(void*))AdaptiveNotch_Float64_Init, \
    (tLoadImplementationParameter)AdaptiveNotch_Float64_Load, \
    (tSaveImplementationParameter)AdaptiveNotch_Float64_Save, \
    (void* (*)(const void*, uint16))AdaptiveNotch_Float64_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void AdaptiveNotch_Float64_Update(ADAPTIVENOTCH_FLOAT64 *pTAdaptiveNotch_Float64);
void AdaptiveNotch_Float64_Init(ADAPTIVENOTCH_FLOAT64 *pTAdaptiveNotch_Float64);
uint8 AdaptiveNotch_Float64_Load(const ADAPTIVENOTCH_FLOAT64 *pTAdaptiveNotch_Float64, uint8 data[], uint16 *dataLength, uint16 maxSize);
uint8 AdaptiveNotch_Float64_Save(ADAPTIVENOTCH_FLOAT64 *pTAdaptiveNotch_Float64, const uint8 data[], uint16 dataLength);
void* AdaptiveNotch_Float64_GetAddress(const ADAPTIVENOTCH_FLOAT64 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
