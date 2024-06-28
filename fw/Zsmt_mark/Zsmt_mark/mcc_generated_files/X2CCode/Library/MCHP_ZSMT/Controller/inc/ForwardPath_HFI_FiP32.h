/*
 * Copyright (c) {YEAR}, {ORGANIZATION_NAME}, {ORGANIZATION_WEB}
 * All rights reserved.
 */
/*
 * This file is licensed according to the BSD 3-clause license as follows:
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of the "{ORGANIZATION_NAME}" nor
 *     the names of its contributors may be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL "{ORGANIZATION_NAME}" BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*
 * This file is part of X2C. http://www.mechatronic-simulation.org/
 * $LastChangedRevision: 1996 $
 */
/* USERCODE-BEGIN:Description                                                                                         */
/* Description: */
/* USERCODE-END:Description                                                                                           */
#ifndef FORWARDPATH_HFI_FIP32_H
#define FORWARDPATH_HFI_FIP32_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(FORWARDPATH_HFI_FIP32_ISLINKED)
#define FORWARDPATH_HFI_FIP32_ID ((uint16)64177)

#if !defined(X2C_USE_UNION_FOR_POINTER)
typedef struct {
    uint16          ID;
    int32           *Ud;
    int32           *Uq;
    int32           *UdHF;
    int32           *theta;
    int32           Va;
    int32           Vb;
    int32           Vc;
    int32           Valpha;
    int32           Vbeta;
    bool            HF_InjectionPolarity;
} FORWARDPATH_HFI_FIP32;
#else
typedef struct {
    uint16          ID;
    INT32_PTR       Ud;
    INT32_PTR       Uq;
    INT32_PTR       UdHF;
    INT32_PTR       theta;
    int32           Va;
    int32           Vb;
    int32           Vc;
    int32           Valpha;
    int32           Vbeta;
    bool            HF_InjectionPolarity;
} FORWARDPATH_HFI_FIP32;
#endif

#define FORWARDPATH_HFI_FIP32_FUNCTIONS { \
    FORWARDPATH_HFI_FIP32_ID, \
    (void (*)(void*))ForwardPath_HFI_FiP32_Update, \
    (void (*)(void*))ForwardPath_HFI_FiP32_Init, \
    (tLoadImplementationParameter)ForwardPath_HFI_FiP32_Load, \
    (tSaveImplementationParameter)ForwardPath_HFI_FiP32_Save, \
    (void* (*)(const void*, uint16))ForwardPath_HFI_FiP32_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void ForwardPath_HFI_FiP32_Update(FORWARDPATH_HFI_FIP32 *pTForwardPath_HFI_FiP32);
void ForwardPath_HFI_FiP32_Init(FORWARDPATH_HFI_FIP32 *pTForwardPath_HFI_FiP32);
uint8 ForwardPath_HFI_FiP32_Load(const FORWARDPATH_HFI_FIP32 *pTForwardPath_HFI_FiP32, uint8 data[], uint16 *dataLength, uint16 maxSize);
uint8 ForwardPath_HFI_FiP32_Save(FORWARDPATH_HFI_FIP32 *pTForwardPath_HFI_FiP32, const uint8 data[], uint16 dataLength);
void* ForwardPath_HFI_FiP32_GetAddress(const FORWARDPATH_HFI_FIP32 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
