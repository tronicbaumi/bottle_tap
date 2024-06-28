/**
 * @file
 * @brief Load, save and conversion function for mask parameter.
 * 
 * Loading of mask parameter from target, saving of mask parameter on target and conversion of mask parameter to implementation parameter.
 */
/*
 * This file is part of X2C. http://x2c.lcm.at/
 * $LastChangedRevision: 1603 $
 * $LastChangedDate:: 2019-01-21 19:02:13 +0100#$
 */
/* USERCODE-BEGIN:Description                                                                                         */
/* Description: */
/* USERCODE-END:Description                                                                                           */
#ifndef CONVFNC_TRACKINGLOOP_FIP16_H
#define CONVFNC_TRACKINGLOOP_FIP16_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"
#include "TrackingLoop_FiP16.h"

/** Mask parameter data structure */
typedef struct {
    float64 Jp;
    float64 fo;
    float64 p;
    uint8 estimation;
    uint8 method;
    float64 n_max;
    float64 ts_fact;
} TRACKINGLOOP_FIP16_MASK_PARAM;

/* public prototypes */
uint8 TrackingLoop_FiP16_LoadMP(const TRACKINGLOOP_FIP16_MASK_PARAM *maskParam, uint8 data[], uint16* dataLen, uint16 maxSize);
uint8 TrackingLoop_FiP16_SaveMP(TRACKINGLOOP_FIP16 *block, TRACKINGLOOP_FIP16_MASK_PARAM *maskParam, const uint8 data[], uint16 dataLen);
uint8 TrackingLoop_FiP16_InitMP(TRACKINGLOOP_FIP16 *block, const TRACKINGLOOP_FIP16_MASK_PARAM *maskParam);
uint8 TrackingLoop_FiP16_ConvertMP(TRACKINGLOOP_FIP16 *block, TRACKINGLOOP_FIP16_MASK_PARAM *maskParam);
void TrackingLoop_FiP16_BackupMP(TRACKINGLOOP_FIP16_MASK_PARAM *maskParam);
void TrackingLoop_FiP16_RestoreMP(TRACKINGLOOP_FIP16_MASK_PARAM *maskParam);

#ifdef __cplusplus
}
#endif

#endif
