/* USERCODE-BEGIN:Description                                                                                         */
/* Description: */
/* USERCODE-END:Description                                                                                           */
#ifndef SQUAREINJECTION_FAST_FIP16_H
#define SQUAREINJECTION_FAST_FIP16_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(SQUAREINJECTION_FAST_FIP16_ISLINKED)
#define SQUAREINJECTION_FAST_FIP16_ID ((uint16)64144)

#if !defined(X2C_USE_UNION_FOR_POINTER)
typedef struct {
    uint16          ID;
    int16           *Ix;
    int16           *Iy;
    int16           *Sync;
    bool            *EnableInj;
    bool            *Enable;
    int16           Ud;
    int16           PhiInit;
    bool            EnablePLL;
    bool            EnableCtrl;
    int16           dPhi;
    int16           iUsAmp;
    int16           tmp1;
    int16           tmp3;
    int16           tmp5;
    int16           tmp6;
    int16           tmp7;
    int16           tmp2;
    int16           tmp4;
    int16           t_pulse;
    int16           t1;
    int16           deltaT;
    uint16          delayPLL;
    uint16          delayCtrl;
    int16           foundPhiInit;
    int16           toggleStatus;
    int16           uInjAmp;
    int32           iy0;
    int16           actInj;
    int32           iy1;
    int32           iy2;
    int32           iy3;
    int32           iy4;
} SQUAREINJECTION_FAST_FIP16;
#else
typedef struct {
    uint16          ID;
    INT16_PTR       Ix;
    INT16_PTR       Iy;
    INT16_PTR       Sync;
    BOOL_PTR        EnableInj;
    BOOL_PTR        Enable;
    int16           Ud;
    int16           PhiInit;
    bool            EnablePLL;
    bool            EnableCtrl;
    int16           dPhi;
    int16           iUsAmp;
    int16           tmp1;
    int16           tmp3;
    int16           tmp5;
    int16           tmp6;
    int16           tmp7;
    int16           tmp2;
    int16           tmp4;
    int16           t_pulse;
    int16           t1;
    int16           deltaT;
    uint16          delayPLL;
    uint16          delayCtrl;
    int16           foundPhiInit;
    int16           toggleStatus;
    int16           uInjAmp;
    int32           iy0;
    int16           actInj;
    int32           iy1;
    int32           iy2;
    int32           iy3;
    int32           iy4;
} SQUAREINJECTION_FAST_FIP16;
#endif

#define SQUAREINJECTION_FAST_FIP16_FUNCTIONS { \
    SQUAREINJECTION_FAST_FIP16_ID, \
    (void (*)(void*))SquareInjection_Fast_FiP16_Update, \
    (void (*)(void*))SquareInjection_Fast_FiP16_Init, \
    (tLoadImplementationParameter)SquareInjection_Fast_FiP16_Load, \
    (tSaveImplementationParameter)SquareInjection_Fast_FiP16_Save, \
    (void* (*)(const void*, uint16))SquareInjection_Fast_FiP16_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void SquareInjection_Fast_FiP16_Update(SQUAREINJECTION_FAST_FIP16 *pTSquareInjection_Fast_FiP16);
void SquareInjection_Fast_FiP16_Init(SQUAREINJECTION_FAST_FIP16 *pTSquareInjection_Fast_FiP16);
uint8 SquareInjection_Fast_FiP16_Load(const SQUAREINJECTION_FAST_FIP16 *pTSquareInjection_Fast_FiP16, uint8 data[], uint16 *dataLength, uint16 maxSize);
uint8 SquareInjection_Fast_FiP16_Save(SQUAREINJECTION_FAST_FIP16 *pTSquareInjection_Fast_FiP16, const uint8 data[], uint16 dataLength);
void* SquareInjection_Fast_FiP16_GetAddress(const SQUAREINJECTION_FAST_FIP16 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
