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
#ifndef INITPOSDETECT_FIP16_H
#define INITPOSDETECT_FIP16_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(INITPOSDETECT_FIP16_ISLINKED)
#define INITPOSDETECT_FIP16_ID ((uint16)9649)

#if !defined(X2C_USE_UNION_FOR_POINTER)
typedef struct {
    uint16          ID;
    int16           *I_A;
    int16           *I_B;
    int16           *I_C;
    bool            *Enable;
    int16           U_A;
    int16           U_B;
    int16           U_C;
    bool            Ready;
    int16           phi0;
    int16           u_pulse;
    int16           t_pulse;
    int16           t_period;
    int16           timer;
    int8            dir;
    int16           phi;
    int16           max_ia_pos;
    int16           max_ia_neg;
    int16           max_ib_pos;
    int16           max_ib_neg;
    int16           max_ic_pos;
    int16           max_ic_neg;
} INITPOSDETECT_FIP16;
#else
typedef struct {
    uint16          ID;
    INT16_PTR       I_A;
    INT16_PTR       I_B;
    INT16_PTR       I_C;
    BOOL_PTR        Enable;
    int16           U_A;
    int16           U_B;
    int16           U_C;
    bool            Ready;
    int16           phi0;
    int16           u_pulse;
    int16           t_pulse;
    int16           t_period;
    int16           timer;
    int8            dir;
    int16           phi;
    int16           max_ia_pos;
    int16           max_ia_neg;
    int16           max_ib_pos;
    int16           max_ib_neg;
    int16           max_ic_pos;
    int16           max_ic_neg;
} INITPOSDETECT_FIP16;
#endif

#define INITPOSDETECT_FIP16_FUNCTIONS { \
    INITPOSDETECT_FIP16_ID, \
    (void (*)(void*))InitPosDetect_FiP16_Update, \
    (void (*)(void*))InitPosDetect_FiP16_Init, \
    (tLoadImplementationParameter)InitPosDetect_FiP16_Load, \
    (tSaveImplementationParameter)InitPosDetect_FiP16_Save, \
    (void* (*)(const void*, uint16))InitPosDetect_FiP16_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void InitPosDetect_FiP16_Update(INITPOSDETECT_FIP16 *pTInitPosDetect_FiP16);
void InitPosDetect_FiP16_Init(INITPOSDETECT_FIP16 *pTInitPosDetect_FiP16);
uint8 InitPosDetect_FiP16_Load(const INITPOSDETECT_FIP16 *pTInitPosDetect_FiP16, uint8 data[], uint16 *dataLength, uint16 maxSize);
uint8 InitPosDetect_FiP16_Save(INITPOSDETECT_FIP16 *pTInitPosDetect_FiP16, const uint8 data[], uint16 dataLength);
void* InitPosDetect_FiP16_GetAddress(const INITPOSDETECT_FIP16 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
