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
/*     Description:    I Controller with
 *                         - Enable Input
 *                         - Anti Wind-up
 *                         - Initial Condition Input
 *                         - Output Limitation
 *                     Calculation ZOH:
 *                                        1
 *                         y = ( Ki*Ts* -----  ) * u
 *                                      z - 1
 *
 *                     -> y(k) = b1.u(k) + b0.u(k-1) + y(k-1)
 */
/* USERCODE-END:Description                                                                                           */
#ifndef ILIMIT_FLOAT32_H
#define ILIMIT_FLOAT32_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(ILIMIT_FLOAT32_ISLINKED)
#define ILIMIT_FLOAT32_ID ((uint16)3395)

#if !defined(X2C_USE_UNION_FOR_POINTER)
typedef struct {
    uint16          ID;
    float32         *In;
    float32         *I0;
    float32         *max;
    float32         *min;
    bool            *Enable;
    float32         Out;
    float32         b0;
    float32         i_old;
    bool            enable_old;
} ILIMIT_FLOAT32;
#else
typedef struct {
    uint16          ID;
    FLOAT32_PTR     In;
    FLOAT32_PTR     I0;
    FLOAT32_PTR     max;
    FLOAT32_PTR     min;
    BOOL_PTR        Enable;
    float32         Out;
    float32         b0;
    float32         i_old;
    bool            enable_old;
} ILIMIT_FLOAT32;
#endif

#define ILIMIT_FLOAT32_FUNCTIONS { \
    ILIMIT_FLOAT32_ID, \
    (void (*)(void*))ILimit_Float32_Update, \
    (void (*)(void*))ILimit_Float32_Init, \
    (tLoadImplementationParameter)ILimit_Float32_Load, \
    (tSaveImplementationParameter)ILimit_Float32_Save, \
    (void* (*)(const void*, uint16))ILimit_Float32_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void ILimit_Float32_Update(ILIMIT_FLOAT32 *pTILimit_Float32);
void ILimit_Float32_Init(ILIMIT_FLOAT32 *pTILimit_Float32);
uint8 ILimit_Float32_Load(const ILIMIT_FLOAT32 *pTILimit_Float32, uint8 data[], uint16 *dataLength, uint16 maxSize);
uint8 ILimit_Float32_Save(ILIMIT_FLOAT32 *pTILimit_Float32, const uint8 data[], uint16 dataLength);
void* ILimit_Float32_GetAddress(const ILIMIT_FLOAT32 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
