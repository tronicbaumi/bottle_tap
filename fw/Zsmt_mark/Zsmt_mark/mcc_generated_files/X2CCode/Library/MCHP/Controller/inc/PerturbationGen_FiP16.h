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
#ifndef PERTURBATIONGEN_FIP16_H
#define PERTURBATIONGEN_FIP16_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(PERTURBATIONGEN_FIP16_ISLINKED)
#define PERTURBATIONGEN_FIP16_ID ((uint16)21024)

typedef struct {
    uint16          ID;
    int16           *f;
    int16           *dc;
    int16           *S_in;
    int16           u;
    int16           S_out;
    uint16          delta_phi;
    int16           phi;
    int16           level_low;
    int16           level_high;
    int32           RateUp;
    int32           RateDown;
    int32           out_old;
    int32           out_ramp;
} PERTURBATIONGEN_FIP16;

#define PERTURBATIONGEN_FIP16_FUNCTIONS { \
    PERTURBATIONGEN_FIP16_ID, \
    (void (*)(void*))PerturbationGen_FiP16_Update, \
    (void (*)(void*))PerturbationGen_FiP16_Init, \
    (tLoadImplementationParameter)PerturbationGen_FiP16_Load, \
    (tSaveImplementationParameter)PerturbationGen_FiP16_Save, \
    (void* (*)(const void*, uint16))PerturbationGen_FiP16_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void PerturbationGen_FiP16_Update(PERTURBATIONGEN_FIP16 *pTPerturbationGen_FiP16);
void PerturbationGen_FiP16_Init(PERTURBATIONGEN_FIP16 *pTPerturbationGen_FiP16);
uint8 PerturbationGen_FiP16_Load(const PERTURBATIONGEN_FIP16 *pTPerturbationGen_FiP16, uint8 data[], uint16 *dataLength, uint16 maxSize);
uint8 PerturbationGen_FiP16_Save(PERTURBATIONGEN_FIP16 *pTPerturbationGen_FiP16, const uint8 data[], uint16 dataLength);
void* PerturbationGen_FiP16_GetAddress(const PERTURBATIONGEN_FIP16 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
