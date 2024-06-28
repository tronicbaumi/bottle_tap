/*
 * This file is part of X2C. http://x2c.lcm.at/
 * $LastChangedRevision: 2830 $
 * $LastChangedDate:: 2023-05-08 16:06:26 +0200#$
 */
/* USERCODE-BEGIN:Description                                                                                         */
/* Description: */
/* USERCODE-END:Description                                                                                           */
#ifndef BEMF_PLL_MCHP_FIP32_H
#define BEMF_PLL_MCHP_FIP32_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(BEMF_PLL_MCHP_FIP32_ISLINKED)
#define BEMF_PLL_MCHP_FIP32_ID ((uint16)21009)

#if !defined(X2C_USE_UNION_FOR_POINTER)
typedef struct {
    uint16          ID;
    int32           *Ialpha;
    int32           *Ibeta;
    int32           *Valpha;
    int32           *Vbeta;
    int32           *theta0;
    bool            *Enable;
    int32           theta;
    int32           speed;
    int32           Ls;
    int32           Rs;
    int8            sfrLs;
    int8            sfrRs;
    int32           Ia_old;
    int32           Ib_old;
    uint8           CurrentSampleFactor;
    int32           V_Ls_alpha;
    int32           V_Ls_beta;
    uint8           FactCounter;
    int32           old_theta;
    uint16          n;
    uint8           sfrn;
    int64           sum_d;
    int64           sum_q;
    uint16          count;
    int32           *avg_d;
    int32           *avg_q;
    int32           V_gain;
    int8            sfr_gain;
    int32           b0;
    int8            sfr_b0;
    int64           i_old;
    bool            enable_old;
} BEMF_PLL_MCHP_FIP32;
#else
typedef struct {
    uint16          ID;
    INT32_PTR       Ialpha;
    INT32_PTR       Ibeta;
    INT32_PTR       Valpha;
    INT32_PTR       Vbeta;
    INT32_PTR       theta0;
    BOOL_PTR        Enable;
    int32           theta;
    int32           speed;
    int32           Ls;
    int32           Rs;
    int8            sfrLs;
    int8            sfrRs;
    int32           Ia_old;
    int32           Ib_old;
    uint8           CurrentSampleFactor;
    int32           V_Ls_alpha;
    int32           V_Ls_beta;
    uint8           FactCounter;
    int32           old_theta;
    uint16          n;
    uint8           sfrn;
    int64           sum_d;
    int64           sum_q;
    uint16          count;
    INT32_PTR       avg_d;
    INT32_PTR       avg_q;
    int32           V_gain;
    int8            sfr_gain;
    int32           b0;
    int8            sfr_b0;
    int64           i_old;
    bool            enable_old;
} BEMF_PLL_MCHP_FIP32;
#endif

#define BEMF_PLL_MCHP_FIP32_FUNCTIONS { \
    BEMF_PLL_MCHP_FIP32_ID, \
    (void (*)(void*))BEMF_PLL_MCHP_FiP32_Update, \
    (void (*)(void*))BEMF_PLL_MCHP_FiP32_Init, \
    (tLoadImplementationParameter)BEMF_PLL_MCHP_FiP32_Load, \
    (tSaveImplementationParameter)BEMF_PLL_MCHP_FiP32_Save, \
    (void* (*)(const void*, uint16))BEMF_PLL_MCHP_FiP32_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void BEMF_PLL_MCHP_FiP32_Update(BEMF_PLL_MCHP_FIP32 *pTBEMF_PLL_MCHP_FiP32);
void BEMF_PLL_MCHP_FiP32_Init(BEMF_PLL_MCHP_FIP32 *pTBEMF_PLL_MCHP_FiP32);
uint8 BEMF_PLL_MCHP_FiP32_Load(const BEMF_PLL_MCHP_FIP32 *pTBEMF_PLL_MCHP_FiP32, uint8 data[], uint16 *dataLength, uint16 maxSize);
uint8 BEMF_PLL_MCHP_FiP32_Save(BEMF_PLL_MCHP_FIP32 *pTBEMF_PLL_MCHP_FiP32, const uint8 data[], uint16 dataLength);
void* BEMF_PLL_MCHP_FiP32_GetAddress(const BEMF_PLL_MCHP_FIP32 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
