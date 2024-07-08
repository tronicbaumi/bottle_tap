/*
 * This file is part of X2C. http://x2c.lcm.at/
 * $LastChangedRevision: 2830 $
 * $LastChangedDate:: 2023-05-08 16:06:26 +0200#$
 */
/* USERCODE-BEGIN:Description                                                                                         */
/* Description: */
/* USERCODE-END:Description                                                                                           */
#ifndef BEMF_PLL_MCHP_FLOAT32_H
#define BEMF_PLL_MCHP_FLOAT32_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(BEMF_PLL_MCHP_FLOAT32_ISLINKED)
#define BEMF_PLL_MCHP_FLOAT32_ID ((uint16)21010)

#if !defined(X2C_USE_UNION_FOR_POINTER)
typedef struct {
    uint16          ID;
    float32         *Ialpha;
    float32         *Ibeta;
    float32         *Valpha;
    float32         *Vbeta;
    float32         *theta0;
    bool            *Enable;
    float32         theta;
    float32         speed;
    float32         Ls;
    float32         Rs;
    float32         Ia_old;
    float32         Ib_old;
    uint8           CurrentSampleFactor;
    float32         V_Ls_alpha;
    float32         V_Ls_beta;
    uint8           FactCounter;
    float32         old_theta;
    uint16          n;
    float32         sum_d;
    float32         sum_q;
    uint16          count;
    float32         *avg_d;
    float32         *avg_q;
    float32         V_gain;
    float32         b0;
    float32         i_old;
    bool            enable_old;
} BEMF_PLL_MCHP_FLOAT32;
#else
typedef struct {
    uint16          ID;
    FLOAT32_PTR     Ialpha;
    FLOAT32_PTR     Ibeta;
    FLOAT32_PTR     Valpha;
    FLOAT32_PTR     Vbeta;
    FLOAT32_PTR     theta0;
    BOOL_PTR        Enable;
    float32         theta;
    float32         speed;
    float32         Ls;
    float32         Rs;
    float32         Ia_old;
    float32         Ib_old;
    uint8           CurrentSampleFactor;
    float32         V_Ls_alpha;
    float32         V_Ls_beta;
    uint8           FactCounter;
    float32         old_theta;
    uint16          n;
    float32         sum_d;
    float32         sum_q;
    uint16          count;
    FLOAT32_PTR     avg_d;
    FLOAT32_PTR     avg_q;
    float32         V_gain;
    float32         b0;
    float32         i_old;
    bool            enable_old;
} BEMF_PLL_MCHP_FLOAT32;
#endif

#define BEMF_PLL_MCHP_FLOAT32_FUNCTIONS { \
    BEMF_PLL_MCHP_FLOAT32_ID, \
    (void (*)(void*))BEMF_PLL_MCHP_Float32_Update, \
    (void (*)(void*))BEMF_PLL_MCHP_Float32_Init, \
    (tLoadImplementationParameter)BEMF_PLL_MCHP_Float32_Load, \
    (tSaveImplementationParameter)BEMF_PLL_MCHP_Float32_Save, \
    (void* (*)(const void*, uint16))BEMF_PLL_MCHP_Float32_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void BEMF_PLL_MCHP_Float32_Update(BEMF_PLL_MCHP_FLOAT32 *pTBEMF_PLL_MCHP_Float32);
void BEMF_PLL_MCHP_Float32_Init(BEMF_PLL_MCHP_FLOAT32 *pTBEMF_PLL_MCHP_Float32);
uint8 BEMF_PLL_MCHP_Float32_Load(const BEMF_PLL_MCHP_FLOAT32 *pTBEMF_PLL_MCHP_Float32, uint8 data[], uint16 *dataLength, uint16 maxSize);
uint8 BEMF_PLL_MCHP_Float32_Save(BEMF_PLL_MCHP_FLOAT32 *pTBEMF_PLL_MCHP_Float32, const uint8 data[], uint16 dataLength);
void* BEMF_PLL_MCHP_Float32_GetAddress(const BEMF_PLL_MCHP_FLOAT32 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
