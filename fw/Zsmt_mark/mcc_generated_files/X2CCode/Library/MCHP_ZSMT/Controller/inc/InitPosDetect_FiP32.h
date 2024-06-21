/*
 * Copyright (c) 2018, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
/*
 * This file is part of X2C. http://x2c.lcm.at/
 * $LastChangedRevision: 2108 $
 * $LastChangedDate:: 2020-12-07 19:09:57 +0100#$
 */
/* USERCODE-BEGIN:Description                                                                                         */
/* Description: 
    Calculation of initial rotor angle. */
/* USERCODE-END:Description                                                                                           */
#ifndef INITPOSDETECT_FIP32_H
#define INITPOSDETECT_FIP32_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(INITPOSDETECT_FIP32_ISLINKED)
#define INITPOSDETECT_FIP32_ID ((uint16)9650)

#if !defined(X2C_USE_UNION_FOR_POINTER)
typedef struct {
    uint16          ID;
    int32           *I_A;
    int32           *I_B;
    int32           *I_C;
    bool            *Enable;
    int32           U_A;
    int32           U_B;
    int32           U_C;
    bool            Ready;
    int32           phi0;
    int32           u_pulse;
    int16           t_pulse;
    int16           t_period;
    int16           timer;
    int8            dir;
    int32           phi;
    int32           max_ia_pos;
    int32           max_ia_neg;
    int32           max_ib_pos;
    int32           max_ib_neg;
    int32           max_ic_pos;
    int32           max_ic_neg;
} INITPOSDETECT_FIP32;
#else
typedef struct {
    uint16          ID;
    INT32_PTR       I_A;
    INT32_PTR       I_B;
    INT32_PTR       I_C;
    BOOL_PTR        Enable;
    int32           U_A;
    int32           U_B;
    int32           U_C;
    bool            Ready;
    int32           phi0;
    int32           u_pulse;
    int16           t_pulse;
    int16           t_period;
    int16           timer;
    int8            dir;
    int32           phi;
    int32           max_ia_pos;
    int32           max_ia_neg;
    int32           max_ib_pos;
    int32           max_ib_neg;
    int32           max_ic_pos;
    int32           max_ic_neg;
} INITPOSDETECT_FIP32;
#endif

#define INITPOSDETECT_FIP32_FUNCTIONS { \
    INITPOSDETECT_FIP32_ID, \
    (void (*)(void*))InitPosDetect_FiP32_Update, \
    (void (*)(void*))InitPosDetect_FiP32_Init, \
    (tLoadImplementationParameter)InitPosDetect_FiP32_Load, \
    (tSaveImplementationParameter)InitPosDetect_FiP32_Save, \
    (void* (*)(const void*, uint16))InitPosDetect_FiP32_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void InitPosDetect_FiP32_Update(INITPOSDETECT_FIP32 *pTInitPosDetect_FiP32);
void InitPosDetect_FiP32_Init(INITPOSDETECT_FIP32 *pTInitPosDetect_FiP32);
uint8 InitPosDetect_FiP32_Load(const INITPOSDETECT_FIP32 *pTInitPosDetect_FiP32, uint8 data[], uint16 *dataLength, uint16 maxSize);
uint8 InitPosDetect_FiP32_Save(INITPOSDETECT_FIP32 *pTInitPosDetect_FiP32, const uint8 data[], uint16 dataLength);
void* InitPosDetect_FiP32_GetAddress(const INITPOSDETECT_FIP32 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
