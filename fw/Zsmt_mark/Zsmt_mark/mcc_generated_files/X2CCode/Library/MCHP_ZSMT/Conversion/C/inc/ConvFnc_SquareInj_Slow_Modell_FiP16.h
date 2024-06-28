/**
 * @file
 * @brief Load, save and conversion function for mask parameter.
 * 
 * Loading of mask parameter from target, saving of mask parameter on target and conversion of mask parameter to implementation parameter.
 */
/*
 * This file is part of X2C. http://www.mechatronic-simulation.org/
 * $LastChangedRevision$
 */
/* USERCODE-BEGIN:Description                                                                                         */
/* Description: */
/* USERCODE-END:Description                                                                                           */
#ifndef CONVFNC_SQUAREINJ_SLOW_MODELL_FIP16_H
#define CONVFNC_SQUAREINJ_SLOW_MODELL_FIP16_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"
#include "SquareInj_Slow_Modell_FiP16.h"

/** Mask parameter data structure */
typedef struct {
    float64 n_max;
    float64 p;
    float64 ts_fact;
    float64 I_max;
    float64 Jp;
    float64 Keps;
    float64 rho;
    uint8 method;
    uint8 selSpeedProp;
} SQUAREINJ_SLOW_MODELL_FIP16_MASK_PARAM;

/* public prototypes */
uint8 SquareInj_Slow_Modell_FiP16_LoadMP(const SQUAREINJ_SLOW_MODELL_FIP16_MASK_PARAM *maskParam, uint8 data[], uint16* dataLen, uint16 maxSize);
uint8 SquareInj_Slow_Modell_FiP16_SaveMP(SQUAREINJ_SLOW_MODELL_FIP16 *block, SQUAREINJ_SLOW_MODELL_FIP16_MASK_PARAM *maskParam, const uint8 data[], uint16 dataLen);
uint8 SquareInj_Slow_Modell_FiP16_InitMP(SQUAREINJ_SLOW_MODELL_FIP16 *block, const SQUAREINJ_SLOW_MODELL_FIP16_MASK_PARAM *maskParam);
uint8 SquareInj_Slow_Modell_FiP16_ConvertMP(SQUAREINJ_SLOW_MODELL_FIP16 *block, SQUAREINJ_SLOW_MODELL_FIP16_MASK_PARAM *maskParam);
void SquareInj_Slow_Modell_FiP16_BackupMP(SQUAREINJ_SLOW_MODELL_FIP16_MASK_PARAM *maskParam);
void SquareInj_Slow_Modell_FiP16_RestoreMP(SQUAREINJ_SLOW_MODELL_FIP16_MASK_PARAM *maskParam);

#ifdef __cplusplus
}
#endif

#endif
