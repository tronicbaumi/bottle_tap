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
#ifndef BILIN_FIP32_H
#define BILIN_FIP32_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(BILIN_FIP32_ISLINKED)
#define BILIN_FIP32_ID ((uint16)8066)

#if !defined(X2C_USE_UNION_FOR_POINTER)
typedef struct {
    uint16          ID;
    int32           *In;
    int32           Out;
    int32           b0;
    int32           b1;
    int32           a1;
    int8            sfrb0;
    int8            sfrb1;
    int8            sfra1;
    int32           in_old;
} BILIN_FIP32;
#else
typedef struct {
    uint16          ID;
    INT32_PTR       In;
    int32           Out;
    int32           b0;
    int32           b1;
    int32           a1;
    int8            sfrb0;
    int8            sfrb1;
    int8            sfra1;
    int32           in_old;
} BILIN_FIP32;
#endif

#define BILIN_FIP32_FUNCTIONS { \
    BILIN_FIP32_ID, \
    (void (*)(void*))Bilin_FiP32_Update, \
    (void (*)(void*))Bilin_FiP32_Init, \
    (tLoadImplementationParameter)Bilin_FiP32_Load, \
    (tSaveImplementationParameter)Bilin_FiP32_Save, \
    (void* (*)(const void*, uint16))Bilin_FiP32_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void Bilin_FiP32_Update(BILIN_FIP32 *pTBilin_FiP32);
void Bilin_FiP32_Init(BILIN_FIP32 *pTBilin_FiP32);
uint8 Bilin_FiP32_Load(const BILIN_FIP32 *pTBilin_FiP32, uint8 data[], uint16 *dataLength, uint16 maxSize);
uint8 Bilin_FiP32_Save(BILIN_FIP32 *pTBilin_FiP32, const uint8 data[], uint16 dataLength);
void* Bilin_FiP32_GetAddress(const BILIN_FIP32 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
