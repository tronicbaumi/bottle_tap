/**
 * @file
 * @brief Load, save and conversion function for mask parameter.
 * 
 * Loading of mask parameter from target, saving of mask parameter on target and conversion of mask parameter to implementation parameter.
 */
/* USERCODE-BEGIN:Description                                                                                         */
/* Description: */
/* USERCODE-END:Description                                                                                           */
#ifndef CONVFNC_SQUAREINJECTION_FAST_FIP16_H
#define CONVFNC_SQUAREINJECTION_FAST_FIP16_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"
#include "SquareInjection_Fast_FiP16.h"

/** Mask parameter data structure */
typedef struct {
    float64 VoltPhasor;
    float64 T1;
    float64 deltaT;
    float64 Tpulse;
    float64 DelayPLL;
    float64 DelayCtrl;
    float64 uInj;
    float64 uDCmax;
    float64 ts_fact;
} SQUAREINJECTION_FAST_FIP16_MASK_PARAM;

/* public prototypes */
uint8 SquareInjection_Fast_FiP16_LoadMP(const SQUAREINJECTION_FAST_FIP16_MASK_PARAM *maskParam, uint8 data[], uint16* dataLen, uint16 maxSize);
uint8 SquareInjection_Fast_FiP16_SaveMP(SQUAREINJECTION_FAST_FIP16 *block, SQUAREINJECTION_FAST_FIP16_MASK_PARAM *maskParam, const uint8 data[], uint16 dataLen);
uint8 SquareInjection_Fast_FiP16_InitMP(SQUAREINJECTION_FAST_FIP16 *block, const SQUAREINJECTION_FAST_FIP16_MASK_PARAM *maskParam);
uint8 SquareInjection_Fast_FiP16_ConvertMP(SQUAREINJECTION_FAST_FIP16 *block, SQUAREINJECTION_FAST_FIP16_MASK_PARAM *maskParam);
void SquareInjection_Fast_FiP16_BackupMP(SQUAREINJECTION_FAST_FIP16_MASK_PARAM *maskParam);
void SquareInjection_Fast_FiP16_RestoreMP(SQUAREINJECTION_FAST_FIP16_MASK_PARAM *maskParam);

#ifdef __cplusplus
}
#endif

#endif
