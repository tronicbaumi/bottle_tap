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
#ifndef SQUAREGEN_FIP16_H
#define SQUAREGEN_FIP16_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(SQUAREGEN_FIP16_ISLINKED)
#define SQUAREGEN_FIP16_ID ((uint16)21008)

typedef struct {
    uint16          ID;
    int16           *f;
    int16           *dc;
    int16           u;
    uint16          delta_phi;
    int16           phi;
    float32         level_low;
    float32         level_high;
} SQUAREGEN_FIP16;

#define SQUAREGEN_FIP16_FUNCTIONS { \
    SQUAREGEN_FIP16_ID, \
    (void (*)(void*))SquareGen_FiP16_Update, \
    (void (*)(void*))SquareGen_FiP16_Init, \
    (tLoadImplementationParameter)SquareGen_FiP16_Load, \
    (tSaveImplementationParameter)SquareGen_FiP16_Save, \
    (void* (*)(const void*, uint16))SquareGen_FiP16_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void SquareGen_FiP16_Update(SQUAREGEN_FIP16 *pTSquareGen_FiP16);
void SquareGen_FiP16_Init(SQUAREGEN_FIP16 *pTSquareGen_FiP16);
uint8 SquareGen_FiP16_Load(const SQUAREGEN_FIP16 *pTSquareGen_FiP16, uint8 data[], uint16 *dataLength, uint16 maxSize);
uint8 SquareGen_FiP16_Save(SQUAREGEN_FIP16 *pTSquareGen_FiP16, const uint8 data[], uint16 dataLength);
void* SquareGen_FiP16_GetAddress(const SQUAREGEN_FIP16 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
