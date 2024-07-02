/*
 * Copyright (c) 2013, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
/*
 * This file is licensed according to the BSD 3-clause license as follows:
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the "Linz Center of Mechatronics GmbH" and "LCM" nor
 *       the names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL "Linz Center of Mechatronics GmbH" BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*
 * This file is part of X2C. http://x2c.lcm.at/
 * $LastChangedRevision: 2800 $
 */
/* USERCODE-BEGIN:Description                                                                                         */
/*     Description:    P Controller with
 *                         - Enable Input
 *                     Calculation ZOH:
 *
 *                         y = Kp * u
 *
 *                     -> y(k) = b1.u(k)
 *
 *     Note: PLimit source code is used!
 */
/* USERCODE-END:Description                                                                                           */
#ifndef P_FLOAT64_H
#define P_FLOAT64_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(P_FLOAT64_ISLINKED)
#define P_FLOAT64_ID ((uint16)3444)

#if !defined(X2C_USE_UNION_FOR_POINTER)
typedef struct {
    uint16          ID;
    float64         *In;
    bool            *Enable;
    float64         Out;
    float64         b1;
} P_FLOAT64;
#else
typedef struct {
    uint16          ID;
    FLOAT64_PTR     In;
    BOOL_PTR        Enable;
    float64         Out;
    float64         b1;
} P_FLOAT64;
#endif

#define P_FLOAT64_FUNCTIONS { \
    P_FLOAT64_ID, \
    (void (*)(void*))P_Float64_Update, \
    (void (*)(void*))P_Float64_Init, \
    (tLoadImplementationParameter)P_Float64_Load, \
    (tSaveImplementationParameter)P_Float64_Save, \
    (void* (*)(const void*, uint16))P_Float64_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void P_Float64_Update(P_FLOAT64 *pTP_Float64);
void P_Float64_Init(P_FLOAT64 *pTP_Float64);
uint8 P_Float64_Load(const P_FLOAT64 *pTP_Float64, uint8 data[], uint16 *dataLength, uint16 maxSize);
uint8 P_Float64_Save(P_FLOAT64 *pTP_Float64, const uint8 data[], uint16 dataLength);
void* P_Float64_GetAddress(const P_FLOAT64 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
