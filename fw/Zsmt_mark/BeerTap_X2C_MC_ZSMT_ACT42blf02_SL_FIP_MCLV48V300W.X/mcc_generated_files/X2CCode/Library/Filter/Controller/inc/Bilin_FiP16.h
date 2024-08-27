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
#ifndef BILIN_FIP16_H
#define BILIN_FIP16_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(BILIN_FIP16_ISLINKED)
#define BILIN_FIP16_ID ((uint16)8065)

#if !defined(X2C_USE_UNION_FOR_POINTER)
typedef struct {
    uint16          ID;
    int16           *In;
    int16           Out;
    int16           b0;
    int16           b1;
    int16           a1;
    int8            sfrb0;
    int8            sfrb1;
    int8            sfra1;
    int16           in_old;
} BILIN_FIP16;
#else
typedef struct {
    uint16          ID;
    INT16_PTR       In;
    int16           Out;
    int16           b0;
    int16           b1;
    int16           a1;
    int8            sfrb0;
    int8            sfrb1;
    int8            sfra1;
    int16           in_old;
} BILIN_FIP16;
#endif

#define BILIN_FIP16_FUNCTIONS { \
    BILIN_FIP16_ID, \
    (void (*)(void*))Bilin_FiP16_Update, \
    (void (*)(void*))Bilin_FiP16_Init, \
    (tLoadImplementationParameter)Bilin_FiP16_Load, \
    (tSaveImplementationParameter)Bilin_FiP16_Save, \
    (void* (*)(const void*, uint16))Bilin_FiP16_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void Bilin_FiP16_Update(BILIN_FIP16 *pTBilin_FiP16);
void Bilin_FiP16_Init(BILIN_FIP16 *pTBilin_FiP16);
uint8 Bilin_FiP16_Load(const BILIN_FIP16 *pTBilin_FiP16, uint8 data[], uint16 *dataLength, uint16 maxSize);
uint8 Bilin_FiP16_Save(BILIN_FIP16 *pTBilin_FiP16, const uint8 data[], uint16 dataLength);
void* Bilin_FiP16_GetAddress(const BILIN_FIP16 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
