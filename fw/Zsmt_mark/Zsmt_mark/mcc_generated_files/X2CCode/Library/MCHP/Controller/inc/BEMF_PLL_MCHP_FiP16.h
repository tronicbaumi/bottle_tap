/*
 * This file is part of X2C. http://x2c.lcm.at/
 * $LastChangedRevision: 2830 $
 * $LastChangedDate:: 2023-05-08 16:06:26 +0200#$
 */
/* USERCODE-BEGIN:Description                                                                                         */
/* Description: */
/* USERCODE-END:Description                                                                                           */
#ifndef BEMF_PLL_MCHP_FIP16_H
#define BEMF_PLL_MCHP_FIP16_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(BEMF_PLL_MCHP_FIP16_ISLINKED)
#define BEMF_PLL_MCHP_FIP16_ID ((uint16)21008)

#if !defined(X2C_USE_UNION_FOR_POINTER)
typedef struct {
    uint16          ID;
    int16           *Ialpha;
    int16           *Ibeta;
    int16           *Valpha;
    int16           *Vbeta;
    int16           *theta0;
    bool            *Enable;
    int16           theta;
    int16           speed;
    int16           Ls;
    int16           Rs;
    int8            sfrLs;
    int8            sfrRs;
    int16           Ib_old;
    int16           Ia_old;
    uint8           CurrentSampleFactor;
    int16           V_Ls_alpha;
    int16           V_Ls_beta;
    uint8           FactCounter;
    int16           old_theta;
    int16           *avg_d;
    int16           *avg_q;
    int32           sum_d;
    int32           sum_q;
    uint16          n;
    uint8           sfrn;
    uint16          count;
    int16           V_gain;
    int8            sfr_gain;
    int16           b0;
    int8            sfr_b0;
    int32           i_old;
    bool            enable_old;
} BEMF_PLL_MCHP_FIP16;
#else
typedef struct {
    uint16          ID;
    INT16_PTR       Ialpha;
    INT16_PTR       Ibeta;
    INT16_PTR       Valpha;
    INT16_PTR       Vbeta;
    INT16_PTR       theta0;
    BOOL_PTR        Enable;
    int16           theta;
    int16           speed;
    int16           Ls;
    int16           Rs;
    int8            sfrLs;
    int8            sfrRs;
    int16           Ib_old;
    int16           Ia_old;
    uint8           CurrentSampleFactor;
    int16           V_Ls_alpha;
    int16           V_Ls_beta;
    uint8           FactCounter;
    int16           old_theta;
    INT16_PTR       avg_d;
    INT16_PTR       avg_q;
    int32           sum_d;
    int32           sum_q;
    uint16          n;
    uint8           sfrn;
    uint16          count;
    int16           V_gain;
    int8            sfr_gain;
    int16           b0;
    int8            sfr_b0;
    int32           i_old;
    bool            enable_old;
} BEMF_PLL_MCHP_FIP16;
#endif

#define BEMF_PLL_MCHP_FIP16_FUNCTIONS { \
    BEMF_PLL_MCHP_FIP16_ID, \
    (void (*)(void*))BEMF_PLL_MCHP_FiP16_Update, \
    (void (*)(void*))BEMF_PLL_MCHP_FiP16_Init, \
    (tLoadImplementationParameter)BEMF_PLL_MCHP_FiP16_Load, \
    (tSaveImplementationParameter)BEMF_PLL_MCHP_FiP16_Save, \
    (void* (*)(const void*, uint16))BEMF_PLL_MCHP_FiP16_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void BEMF_PLL_MCHP_FiP16_Update(BEMF_PLL_MCHP_FIP16 *pTBEMF_PLL_MCHP_FiP16);
void BEMF_PLL_MCHP_FiP16_Init(BEMF_PLL_MCHP_FIP16 *pTBEMF_PLL_MCHP_FiP16);
uint8 BEMF_PLL_MCHP_FiP16_Load(const BEMF_PLL_MCHP_FIP16 *pTBEMF_PLL_MCHP_FiP16, uint8 data[], uint16 *dataLength, uint16 maxSize);
uint8 BEMF_PLL_MCHP_FiP16_Save(BEMF_PLL_MCHP_FIP16 *pTBEMF_PLL_MCHP_FiP16, const uint8 data[], uint16 dataLength);
void* BEMF_PLL_MCHP_FiP16_GetAddress(const BEMF_PLL_MCHP_FIP16 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
