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
#ifndef ADAPTIVENOTCH_FLOAT32_H
#define ADAPTIVENOTCH_FLOAT32_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(ADAPTIVENOTCH_FLOAT32_ISLINKED)
#define ADAPTIVENOTCH_FLOAT32_ID ((uint16)8051)

#if !defined(X2C_USE_UNION_FOR_POINTER)
typedef struct {
    uint16          ID;
    float32         *In;
    float32         *n;
    float32         Out;
    float32         a_fact;
    float32         b_fact;
    float32         c_fact;
    float32         a1;
    float32         a2;
    float32         b1;
    float32         in_old;
    float32         in_very_old;
    float32         out_old;
    float32         out_very_old;
    float32         n_old;
    float32         k;
    float32         n_thresh;
} ADAPTIVENOTCH_FLOAT32;
#else
typedef struct {
    uint16          ID;
    FLOAT32_PTR     In;
    FLOAT32_PTR     n;
    float32         Out;
    float32         a_fact;
    float32         b_fact;
    float32         c_fact;
    float32         a1;
    float32         a2;
    float32         b1;
    float32         in_old;
    float32         in_very_old;
    float32         out_old;
    float32         out_very_old;
    float32         n_old;
    float32         k;
    float32         n_thresh;
} ADAPTIVENOTCH_FLOAT32;
#endif

#define ADAPTIVENOTCH_FLOAT32_FUNCTIONS { \
    ADAPTIVENOTCH_FLOAT32_ID, \
    (void (*)(void*))AdaptiveNotch_Float32_Update, \
    (void (*)(void*))AdaptiveNotch_Float32_Init, \
    (tLoadImplementationParameter)AdaptiveNotch_Float32_Load, \
    (tSaveImplementationParameter)AdaptiveNotch_Float32_Save, \
    (void* (*)(const void*, uint16))AdaptiveNotch_Float32_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void AdaptiveNotch_Float32_Update(ADAPTIVENOTCH_FLOAT32 *pTAdaptiveNotch_Float32);
void AdaptiveNotch_Float32_Init(ADAPTIVENOTCH_FLOAT32 *pTAdaptiveNotch_Float32);
uint8 AdaptiveNotch_Float32_Load(const ADAPTIVENOTCH_FLOAT32 *pTAdaptiveNotch_Float32, uint8 data[], uint16 *dataLength, uint16 maxSize);
uint8 AdaptiveNotch_Float32_Save(ADAPTIVENOTCH_FLOAT32 *pTAdaptiveNotch_Float32, const uint8 data[], uint16 dataLength);
void* AdaptiveNotch_Float32_GetAddress(const ADAPTIVENOTCH_FLOAT32 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
