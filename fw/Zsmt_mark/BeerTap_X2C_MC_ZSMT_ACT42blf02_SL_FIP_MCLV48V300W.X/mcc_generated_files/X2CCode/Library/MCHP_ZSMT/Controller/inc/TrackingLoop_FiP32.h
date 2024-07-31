/*
 * This file is part of X2C. http://x2c.lcm.at/
 * $LastChangedRevision: 1603 $
 * $LastChangedDate:: 2019-01-21 19:02:13 +0100#$
 */
/* USERCODE-BEGIN:Description                                                                                         */
/* Description: */
/* USERCODE-END:Description                                                                                           */
#ifndef TRACKINGLOOP_FIP32_H
#define TRACKINGLOOP_FIP32_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(TRACKINGLOOP_FIP32_ISLINKED)
#define TRACKINGLOOP_FIP32_ID ((uint16)64338)

#if !defined(X2C_USE_UNION_FOR_POINTER)
typedef struct {
    uint16          ID;
    int32           *phi_eps;
    int32           *n0;
    int32           *phi0;
    bool            *Enable;
    int32           n;
    int32           phi;
    bool            enable_old;
    int64           i_old_torque;
    int64           i_old_speed;
    int64           i_old_angle;
    int32           vGain;
    int8            sfrGain;
    int32           b0_torque;
    int32           b1_torque;
    int8            sfrb0_torque;
    int8            sfrb1_torque;
    int32           b0_speed;
    int32           b1_speed;
    int8            sfrb0_speed;
    int8            sfrb1_speed;
    int32           b0_angle;
    int32           b1_angle;
    int8            sfrb0_angle;
    int8            sfrb1_angle;
    bool            rawSpeed;
} TRACKINGLOOP_FIP32;
#else
typedef struct {
    uint16          ID;
    INT32_PTR       phi_eps;
    INT32_PTR       n0;
    INT32_PTR       phi0;
    BOOL_PTR        Enable;
    int32           n;
    int32           phi;
    bool            enable_old;
    int64           i_old_torque;
    int64           i_old_speed;
    int64           i_old_angle;
    int32           vGain;
    int8            sfrGain;
    int32           b0_torque;
    int32           b1_torque;
    int8            sfrb0_torque;
    int8            sfrb1_torque;
    int32           b0_speed;
    int32           b1_speed;
    int8            sfrb0_speed;
    int8            sfrb1_speed;
    int32           b0_angle;
    int32           b1_angle;
    int8            sfrb0_angle;
    int8            sfrb1_angle;
    bool            rawSpeed;
} TRACKINGLOOP_FIP32;
#endif

#define TRACKINGLOOP_FIP32_FUNCTIONS { \
    TRACKINGLOOP_FIP32_ID, \
    (void (*)(void*))TrackingLoop_FiP32_Update, \
    (void (*)(void*))TrackingLoop_FiP32_Init, \
    (tLoadImplementationParameter)TrackingLoop_FiP32_Load, \
    (tSaveImplementationParameter)TrackingLoop_FiP32_Save, \
    (void* (*)(const void*, uint16))TrackingLoop_FiP32_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void TrackingLoop_FiP32_Update(TRACKINGLOOP_FIP32 *pTTrackingLoop_FiP32);
void TrackingLoop_FiP32_Init(TRACKINGLOOP_FIP32 *pTTrackingLoop_FiP32);
uint8 TrackingLoop_FiP32_Load(const TRACKINGLOOP_FIP32 *pTTrackingLoop_FiP32, uint8 data[], uint16 *dataLength, uint16 maxSize);
uint8 TrackingLoop_FiP32_Save(TRACKINGLOOP_FIP32 *pTTrackingLoop_FiP32, const uint8 data[], uint16 dataLength);
void* TrackingLoop_FiP32_GetAddress(const TRACKINGLOOP_FIP32 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
