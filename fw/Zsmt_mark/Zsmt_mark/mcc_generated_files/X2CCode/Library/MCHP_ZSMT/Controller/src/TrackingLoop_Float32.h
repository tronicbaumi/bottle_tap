/*
 * This file is part of X2C. http://x2c.lcm.at/
 * $LastChangedRevision: 1603 $
 * $LastChangedDate:: 2019-01-21 19:02:13 +0100#$
 */
/* USERCODE-BEGIN:Description                                                                                         */
/* Description: */
/* USERCODE-END:Description                                                                                           */
#ifndef TRACKINGLOOP_FLOAT32_H
#define TRACKINGLOOP_FLOAT32_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(TRACKINGLOOP_FLOAT32_ISLINKED)
#define TRACKINGLOOP_FLOAT32_ID ((uint16)64339)

typedef struct {
    uint16          ID;
    float32         *phi_eps;
    float32         *n0;
    float32         *phi0;
    bool            *Enable;
    float32         n;
    float32         phi;
    bool            enable_old;
    float32         i_old_torque;
    float32         i_old_speed;
    float32         i_old_angle;
    float32         vGain;
    float32         b0_torque;
    float32         b1_torque;
    float32         b0_speed;
    float32         b1_speed;
    float32         b0_angle;
    float32         b1_angle;
    bool            rawSpeed;
} TRACKINGLOOP_FLOAT32;

#define TRACKINGLOOP_FLOAT32_FUNCTIONS { \
    TRACKINGLOOP_FLOAT32_ID, \
    (void (*)(void*))TrackingLoop_Float32_Update, \
    (void (*)(void*))TrackingLoop_Float32_Init, \
    (tLoadImplementationParameter)TrackingLoop_Float32_Load, \
    (tSaveImplementationParameter)TrackingLoop_Float32_Save, \
    (void* (*)(const void*, uint16))TrackingLoop_Float32_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void TrackingLoop_Float32_Update(TRACKINGLOOP_FLOAT32 *pTTrackingLoop_Float32);
void TrackingLoop_Float32_Init(TRACKINGLOOP_FLOAT32 *pTTrackingLoop_Float32);
uint8 TrackingLoop_Float32_Load(const TRACKINGLOOP_FLOAT32 *pTTrackingLoop_Float32, uint8 data[], uint16 *dataLength, uint16 maxSize);
uint8 TrackingLoop_Float32_Save(TRACKINGLOOP_FLOAT32 *pTTrackingLoop_Float32, const uint8 data[], uint16 dataLength);
void* TrackingLoop_Float32_GetAddress(const TRACKINGLOOP_FLOAT32 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
