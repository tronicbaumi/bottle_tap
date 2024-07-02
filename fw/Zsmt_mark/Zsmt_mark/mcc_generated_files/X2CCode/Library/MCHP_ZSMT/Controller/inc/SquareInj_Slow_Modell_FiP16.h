/*
 * This file is part of X2C. http://www.mechatronic-simulation.org/
 * $LastChangedRevision$
 */
/* USERCODE-BEGIN:Description                                                                                         */
/* Description: */
/* USERCODE-END:Description                                                                                           */
#ifndef SQUAREINJ_SLOW_MODELL_FIP16_H
#define SQUAREINJ_SLOW_MODELL_FIP16_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(SQUAREINJ_SLOW_MODELL_FIP16_ISLINKED)
#define SQUAREINJ_SLOW_MODELL_FIP16_ID ((uint16)64129)

#if !defined(X2C_USE_UNION_FOR_POINTER)
typedef struct {
    uint16          ID;
    int16           *dphi;
    int16           *phi0;
    int16           *n0;
    bool            *Enable;
    int16           phi;
    int16           Sync;
    int16           speed;
    int32           b0;
    int32           b1;
    int8            sfrb0;
    int8            sfrb1;
    int64           i_old;
    bool            enable_old;
    int16           a0_PT1;
    int16           b0_PT1;
    int16           b1_PT1;
    int16           sfra_PT1;
    int16           sfrb_PT1;
    int16           dphiOld;
    int32           filtDphi;
    int16           b0_uI;
    int16           sfr_uI;
    int32           i_old_uI;
    int16           toggleState;
    int16           b0_I;
    int16           sfr_I;
    int32           i_old_I;
    int8            rawSpeed;
    int16           vGain;
    int16           sfrGain;
    int16           b1_I;
    int16           b1_uI;
    int16           sfrb1_I;
    int16           sfrb1_uI;
} SQUAREINJ_SLOW_MODELL_FIP16;
#else
typedef struct {
    uint16          ID;
    INT16_PTR       dphi;
    INT16_PTR       phi0;
    INT16_PTR       n0;
    BOOL_PTR        Enable;
    int16           phi;
    int16           Sync;
    int16           speed;
    int32           b0;
    int32           b1;
    int8            sfrb0;
    int8            sfrb1;
    int64           i_old;
    bool            enable_old;
    int16           a0_PT1;
    int16           b0_PT1;
    int16           b1_PT1;
    int16           sfra_PT1;
    int16           sfrb_PT1;
    int16           dphiOld;
    int32           filtDphi;
    int16           b0_uI;
    int16           sfr_uI;
    int32           i_old_uI;
    int16           toggleState;
    int16           b0_I;
    int16           sfr_I;
    int32           i_old_I;
    int8            rawSpeed;
    int16           vGain;
    int16           sfrGain;
    int16           b1_I;
    int16           b1_uI;
    int16           sfrb1_I;
    int16           sfrb1_uI;
} SQUAREINJ_SLOW_MODELL_FIP16;
#endif

#define SQUAREINJ_SLOW_MODELL_FIP16_FUNCTIONS { \
    SQUAREINJ_SLOW_MODELL_FIP16_ID, \
    (void (*)(void*))SquareInj_Slow_Modell_FiP16_Update, \
    (void (*)(void*))SquareInj_Slow_Modell_FiP16_Init, \
    (tLoadImplementationParameter)SquareInj_Slow_Modell_FiP16_Load, \
    (tSaveImplementationParameter)SquareInj_Slow_Modell_FiP16_Save, \
    (void* (*)(const void*, uint16))SquareInj_Slow_Modell_FiP16_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void SquareInj_Slow_Modell_FiP16_Update(SQUAREINJ_SLOW_MODELL_FIP16 *pTSquareInj_Slow_Modell_FiP16);
void SquareInj_Slow_Modell_FiP16_Init(SQUAREINJ_SLOW_MODELL_FIP16 *pTSquareInj_Slow_Modell_FiP16);
uint8 SquareInj_Slow_Modell_FiP16_Load(const SQUAREINJ_SLOW_MODELL_FIP16 *pTSquareInj_Slow_Modell_FiP16, uint8 data[], uint16 *dataLength, uint16 maxSize);
uint8 SquareInj_Slow_Modell_FiP16_Save(SQUAREINJ_SLOW_MODELL_FIP16 *pTSquareInj_Slow_Modell_FiP16, const uint8 data[], uint16 dataLength);
void* SquareInj_Slow_Modell_FiP16_GetAddress(const SQUAREINJ_SLOW_MODELL_FIP16 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
