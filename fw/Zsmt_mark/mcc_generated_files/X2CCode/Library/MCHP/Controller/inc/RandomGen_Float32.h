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
 * This file is part of X2C. http://x2c.lcm.at/
 * $LastChangedRevision: 2457 $
 * $LastChangedDate:: 2022-02-11 12:58:55 +0100#$
 */
/* USERCODE-BEGIN:Description                                                                                         */
/* Description: */
/* USERCODE-END:Description                                                                                           */
#ifndef RANDOMGEN_FLOAT32_H
#define RANDOMGEN_FLOAT32_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(RANDOMGEN_FLOAT32_ISLINKED)
#define RANDOMGEN_FLOAT32_ID ((uint16)21042)

typedef struct {
    uint16          ID;
    float32         *S_in;
    float32         u;
    float32         S_out;
    uint32          noise_amplitude;
    uint32          noise_amplitude_half;
    uint32          sample_time_divisor;
    uint32          sample_counter;
    int32           random_num;
} RANDOMGEN_FLOAT32;

#define RANDOMGEN_FLOAT32_FUNCTIONS { \
    RANDOMGEN_FLOAT32_ID, \
    (void (*)(void*))RandomGen_Float32_Update, \
    (void (*)(void*))RandomGen_Float32_Init, \
    (tLoadImplementationParameter)RandomGen_Float32_Load, \
    (tSaveImplementationParameter)RandomGen_Float32_Save, \
    (void* (*)(const void*, uint16))RandomGen_Float32_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void RandomGen_Float32_Update(RANDOMGEN_FLOAT32 *pTRandomGen_Float32);
void RandomGen_Float32_Init(RANDOMGEN_FLOAT32 *pTRandomGen_Float32);
uint8 RandomGen_Float32_Load(const RANDOMGEN_FLOAT32 *pTRandomGen_Float32, uint8 data[], uint16 *dataLength, uint16 maxSize);
uint8 RandomGen_Float32_Save(RANDOMGEN_FLOAT32 *pTRandomGen_Float32, const uint8 data[], uint16 dataLength);
void* RandomGen_Float32_GetAddress(const RANDOMGEN_FLOAT32 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
