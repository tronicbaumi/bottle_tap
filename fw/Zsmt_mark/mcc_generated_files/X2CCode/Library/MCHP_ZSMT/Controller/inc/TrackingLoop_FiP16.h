/*
 * This file is part of X2C. http://x2c.lcm.at/
 * $LastChangedRevision: 1603 $
 * $LastChangedDate:: 2019-01-21 19:02:13 +0100#$
 */
/* USERCODE-BEGIN:Description                                                                                         */
/* Description: */
/* USERCODE-END:Description                                                                                           */
#ifndef TRACKINGLOOP_FIP16_H
#define TRACKINGLOOP_FIP16_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(TRACKINGLOOP_FIP16_ISLINKED)
#define TRACKINGLOOP_FIP16_ID ((uint16)64337)

#if !defined(X2C_USE_UNION_FOR_POINTER)
typedef struct {
    uint16          ID;
    int16           *phi_eps;
    int16           *n0;
    int16           *phi0;
    bool            *Enable;
    int16           n;
    int16           phi;
    bool            enable_old;
    int64           i_old_torque;
    int64           i_old_speed;
    int32           i_old_angle;
    int16           vGain;
    int8            sfrGain;
    int32           b0_torque;
    int32           b1_torque;
    int8            sfrb0_torque;
    int8            sfrb1_torque;
    int32           b0_speed;
    int32           b1_speed;
    int8            sfrb0_speed;
    int8            sfrb1_speed;
    int16           b0_angle;
    int16           b1_angle;
    int8            sfrb0_angle;
    int8            sfrb1_angle;
    bool            rawSpeed;
} TRACKINGLOOP_FIP16;
#else
typedef struct {
    uint16          ID;
    INT16_PTR       phi_eps;
    INT16_PTR       n0;
    INT16_PTR       phi0;
    BOOL_PTR        Enable;
    int16           n;
    int16           phi;
    bool            enable_old;
    int64           i_old_torque;
    int64           i_old_speed;
    int32           i_old_angle;
    int16           vGain;
    int8            sfrGain;
    int32           b0_torque;
    int32           b1_torque;
    int8            sfrb0_torque;
    int8            sfrb1_torque;
    int32           b0_speed;
    int32           b1_speed;
    int8            sfrb0_speed;
    int8            sfrb1_speed;
    int16           b0_angle;
    int16           b1_angle;
    int8            sfrb0_angle;
    int8            sfrb1_angle;
    bool            rawSpeed;
} TRACKINGLOOP_FIP16;
#endif

#define TRACKINGLOOP_FIP16_FUNCTIONS { \
    TRACKINGLOOP_FIP16_ID, \
    (void (*)(void*))TrackingLoop_FiP16_Update, \
    (void (*)(void*))TrackingLoop_FiP16_Init, \
    (tLoadImplementationParameter)TrackingLoop_FiP16_Load, \
    (tSaveImplementationParameter)TrackingLoop_FiP16_Save, \
    (void* (*)(const void*, uint16))TrackingLoop_FiP16_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void TrackingLoop_FiP16_Update(TRACKINGLOOP_FIP16 *pTTrackingLoop_FiP16);
void TrackingLoop_FiP16_Init(TRACKINGLOOP_FIP16 *pTTrackingLoop_FiP16);
uint8 TrackingLoop_FiP16_Load(const TRACKINGLOOP_FIP16 *pTTrackingLoop_FiP16, uint8 data[], uint16 *dataLength, uint16 maxSize);
uint8 TrackingLoop_FiP16_Save(TRACKINGLOOP_FIP16 *pTTrackingLoop_FiP16, const uint8 data[], uint16 dataLength);
void* TrackingLoop_FiP16_GetAddress(const TRACKINGLOOP_FIP16 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
